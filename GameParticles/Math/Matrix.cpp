#include <Math.h>
#include <assert.h>
#include "Vect4d.h"
#include "Matrix.h"



Matrix::Matrix()
{
};

Matrix::Matrix(const Matrix& m)
{
	this->v0._m = _mm_set_ps(m.v0.w, m.v0.z, m.v0.y, m.v0.x);
	this->v1._m = _mm_set_ps(m.v1.w, m.v1.z, m.v1.y, m.v1.x);
	this->v2._m = _mm_set_ps(m.v2.w, m.v2.z, m.v2.y, m.v2.x);
	this->v3._m = _mm_set_ps(m.v3.w, m.v3.z, m.v3.y, m.v3.x);
}

Matrix::Matrix(Vect4D const & TRANS)
{
	this->v0._m = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
	this->v1._m = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
	this->v2._m = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
	this->v3._m = _mm_set_ps(1.f, TRANS.z, TRANS.y, TRANS.x);

}

Matrix::Matrix(float const &ROTZ) 
{
	this->v0._m = _mm_set_ps(0.f, 0.f, -sinf(ROTZ), cosf(ROTZ));
	this->v1._m = _mm_set_ps(0.f, 0.f, cosf(ROTZ), sinf(ROTZ));
	this->v2._m = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
	this->v3._m = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
}

Matrix::Matrix(const Vect4D * const SCALE)
{
	this->v0._m = _mm_set_ps(0.f, 0.f, 0.f, SCALE->x);
	this->v1._m = _mm_set_ps(0.f, 0.f, SCALE->y, 0.f);
	this->v2._m = _mm_set_ps(0.f, SCALE->z, 0.f, 0.f);
	this->v3._m = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
}

Matrix::Matrix(Vect4D const & v0, const Vect4D & v1, const Vect4D & v2, const Vect4D & v3)
{
	this->v0._m = v0._m;
	this->v1._m = v1._m;
	this->v2._m = v2._m;
	this->v3._m = v3._m;
}


Matrix & Matrix::operator=(const Matrix &m)
{
	this->v0._m = m.v0._m;
	this->v1._m = m.v1._m;
	this->v2._m = m.v2._m;
	this->v3._m = m.v3._m;

	return *this;
}

Matrix::~Matrix()
{
	// nothign to delete
}

void Matrix::setIdentMatrix()
{ // initialize to the identity matrix
	this->v0._m = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
	this->v1._m = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
	this->v2._m = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
	this->v3._m = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
}

#if !PROXY
Matrix Matrix::operator*(const Matrix& m) const 
{ // matrix multiplications
	return Matrix
	(
		_mm_add_ps
		(
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v0.x), m.v0._m),
				_mm_mul_ps(_mm_set_ps1(this->v0.y), m.v1._m)
			),
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v0.z), m.v2._m),
				_mm_mul_ps(_mm_set_ps1(this->v0.w), m.v3._m)
			)
		),

		_mm_add_ps
		(
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v1.x), m.v0._m),
				_mm_mul_ps(_mm_set_ps1(this->v1.y), m.v1._m)
			),
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v1.z), m.v2._m),
				_mm_mul_ps(_mm_set_ps1(this->v1.w), m.v3._m)
			)
		),

		_mm_add_ps
		(
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v2.x), m.v0._m),
				_mm_mul_ps(_mm_set_ps1(this->v2.y), m.v1._m)
			),
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v2.z), m.v2._m),
				_mm_mul_ps(_mm_set_ps1(this->v2.w), m.v3._m)
			)
		),

		_mm_add_ps
		(
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v3.x), m.v0._m),
				_mm_mul_ps(_mm_set_ps1(this->v3.y), m.v1._m)
			),
			_mm_add_ps
			(
				_mm_mul_ps(_mm_set_ps1(this->v3.z), m.v2._m),
				_mm_mul_ps(_mm_set_ps1(this->v3.w), m.v3._m)
			)
		)
	);
}

#endif

Matrix& Matrix::operator/= (float const &rhs)
{ 
	// divide each element by a value
	// using inverse multiply trick, faster that individual divides
	const float inv_rhs = 1.0f/rhs;

	m0 *= inv_rhs;
	m1 *= inv_rhs;
	m2 *= inv_rhs;
	m3 *= inv_rhs;
	m4 *= inv_rhs;
	m5 *= inv_rhs;
	m6 *= inv_rhs;
	m7 *= inv_rhs;
	m8 *= inv_rhs;
	m9 *= inv_rhs;
	m10 *= inv_rhs;
	m11 *= inv_rhs;
	m12 *= inv_rhs;
	m13 *= inv_rhs;
	m14 *= inv_rhs;
	m15 *= inv_rhs;

	return *this;
}

Matrix Matrix::GetAdjugate() 
{
	// matrix = { a,b,c,d / e,f,g,h / j,k,l,m / n,o,p,q }
	
	// ta = lq - mp
	// tb = kq - mo
	// tc = kp - lo
	// td = gq - hp
	// te = fq - ho
	// tf = fp - go
	// tg = gm - hl
	// th = fm - hk
	// ti = fl - gk
	// tj = jq - mn
	// tk = jp - ln
	// tl = eq - hn
	// tm = ep - gn
	// tn = em - hj
	// to = el - gj
	// tp = jo - kn
	// tq = ek - fj
	// tr = eo - fn
	
	// a = det( { f,g,h / k,l,m / o,p,q } )
	// a = f(lq - mp) - g(kq - mo) + h(kp - lo)
	// a = f(ta) - g(tb) + h(tc)
	
	// b = -det( { b,c,d / k,l,m / o,p,q } )
	// b = -( b(lq - mp) - c(kq - mo) + d(kp - lo))
	// b = -( b(ta) - c(tb) + d(tc))
	
	// c = det( { b,c,d / f,g,h / o,p,q } )
	// c = b(gq - hp) - c(fq - ho) + d(fp - go)
	// c = b(td) - c(te) + d(tf)
	
	// d = -det( { b,c,d / f,g,h / k,l,m } )
	// d = -( b(gm - hl) - c(fm - hk) + d(fl - gk) )
	// d = -( b(tg) - c(th) + d(ti) )

	// e = -det( { e,g,h / j,l,m / n,p,q } )
	// e = - ( e(lq - mp) - g(jq - mn) + h(jp - ln))
	// e = - ( e(ta) - g(tj) + h(tk))
	
	// f = det( { a,c,d / j,l,m / n,p,q } )
	// f = a(lq - mp) - c(jq - mn) + d(jp - ln)
	// f = a(ta) - c(tj) + d(tk)
	
	// g = -det( { a,c,d / e,g,h / n,p,q } )
	// g = - ( a(gq - hp) - c(eq - hn) + d(ep - gn))
	// g = - ( a(td) - c(tl) + d(tm))
	
	// h = det( { a,c,d / e,g,h / j,l,m } )
	// h = a(gm - hl) - c(em - hj) + d(el - gj)
	// h = a(tg) - c(tn) + d(to)
	
	// j = det( { e,f,h / j,k,m / n,o,q } )
	// j = e(kq - mo) - f(jq - mn) + h(jo - kn)
	// j = e(tb) - f(tj) + h(tp)
	
	// k = -det( { a,b,d / j,k,m / n,o,q } )
	// k = - ( a(kq - mo) - b(jq - mn) + d(jo - kn))
	// k = - ( a(tb) - b(tj) + d(tp))
	
	// l = det( { a,b,d / e,f,h / n,o,q } )
	// l = a(fq - ho) - b(eq - hn) + d(eo - fn)
	// l = a(te) - b(tl) + d(tr)
	
	// m = -det( { a,b,d / e,f,h / j,k,m } )
	// m = -( a(fm - hk) - b(em - hj) + d(ek - fj))
	// m = -( a(th) - b(tn) + d(tq))
	
	// n = -det( { e,f,g / j,k,l / n,o,p } )
	// n = -( e(kp - lo) - f(jp - ln) + g(jo - kn))
	// n = -( e(tc) - f(tk) + g(tp))
	
	// o = det( { a,b,c / j,k,l / n,o,p } )
	// o = a(kp - lo) - b(jp - ln) + c(jo - kn)
	// o = a(tc) - b(tk) + c(tp)
	
	// p = -det( { a,b,c / e,f,g / n,o,p } )
	// p = - ( a(fp - go) - b(ep - gn) + c(eo - fn))
	// p = - ( a(tf) - b(tm) + c(tr))
	
	// q = det( { a,b,c / e,f,g / j,k,l } )
	// q = a(fl - gk) - b(el - gj) + c(ek - fj)
	// q = a(ti) - b(to) + c(tq)
	
	Matrix tmp;
	
	// load		ABC		(3)		ABC--
	float t1 = (m10*m15) - (m11*m14);
	float t2 = (m9*m15) - (m11*m13);
	float t3 = (m9*m14) - (m10*m13);
	
	// a = f(ta) - g(tb) + h(tc)
	tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
	// b = -( b(ta) - c(tb) + d(tc))
	tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));
	
	// load		JK		(5)		ABCJK
	float t4 = (m8*m15) - (m11*m12);
	float t5 = (m8*m14) - (m10*m12);
	// e = - ( e(ta) - g(tj) + h(tk))
	tmp.m4 = -( (m4*t1) - (m6*t4) + (m7*t5));
	// f = a(ta) - c(tj) + d(tk)
	tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	AJ		(3)		-BC-K
	// load		P		(4)		PBC-K
	t1 = (m8*m13) - (m9*m12);
	// n = -( e(tc) - f(tk) + g(tp))
	tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
	// o = a(tc) - b(tk) + c(tp)
	tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);
	
	// unload	KC		(2)		PB---
	// load		J		(3)		PBJ--
	t3 = (m8*m15) - (m11*m12);
	
	// j = e(tb) - f(tj) + h(tp)
	tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
	// k = - ( a(tb) - b(tj) + d(tp))
	tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));
	
	// unload	BPJ		(0)		-----
	// load		DLM		(3)		DLM--
	t1 = (m6*m15) - (m7*m14);
	t2 = (m4*m15) - (m7*m12);
	t3 = (m4*m14) - (m6*m12);
	
	// g = - ( a(td) - c(tl) + d(tm))
	tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));
	
	// load		FR		(5)		DLMFR
	t4 = (m5*m14) - (m6*m13);
	t5 = (m4*m13) - (m5*m12);
	
	// p = - ( a(tf) - b(tm) + c(tr))
	tmp.m14 = -( (m0*t4) - (m1*t3) + (m3*t5));
	
	// unload	M		(4)		DL-FR
	// load		E		(5)		DLEFR
	t3 = (m5*m15) - (m7*m13);
	
	// l = a(te) - b(tl) + d(tr)
	tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);
	
	// unload	LR		(3)		D-EF-
	// c = b(td) - c(te) + d(tf)
	tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);
	
	// unload	DEF		(0)		-----
	// load		GHI		(3)		GHI--
	t1 = (m6*m11) - (m7*m10);
	t2 = (m5*m11) - (m7*m9);
	t3 = (m5*m10) - (m6*m9);
	
	// d = -( b(tg) - c(th) + d(ti) )
	tmp.m3 = -( (m1*t1) - (m2*t2) + (m3*t3));
	
	// load		NO		(5)		GHINO
	t4 = (m4*m11) - (m7*m8);
	t5 = (m4*m10) - (m6*m8);
	
	// h = a(tg) - c(tn) + d(to)
	tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	G		(4)		-HINO
	// load		Q		(5)		QHINO
	t1 = (m4*m9) - (m5*m8);
	
	// m = -( a(th) - b(tn) + d(tq))
	tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));
	
	// unload	HN		(3)		Q-I-O
	// q = a(ti) - b(to) + c(tq)
	tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);
	
	return tmp;
}

void Matrix::Inverse(Matrix &out)
{
	out = GetAdjugate();
}

void * Matrix::operator new(const size_t i)
{
	return _aligned_malloc(i, 16);
}

void * Matrix::operator new[](const size_t i)
{
	return _aligned_malloc(i, 16);
}

void Matrix::operator delete(void * p)
{
	_aligned_free(p);
}

void Matrix::operator delete[](void * p)
{	
	_aligned_free(p);
}

// End of file