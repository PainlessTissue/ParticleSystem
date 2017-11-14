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
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;

	this->m12 = TRANS.x;
	this->m13 = TRANS.y;
	this->m14 = TRANS.z;
	this->m15 = 1.0f;

}

Matrix::Matrix(float const &ROTZ) 
{
	*this = Matrix(
		cosf(ROTZ), -sinf(ROTZ), 0, 0,
		sinf(ROTZ), cosf(ROTZ), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

}

Matrix::Matrix(const Vect4D * const SCALE)
{
	*this = Matrix(
		SCALE->x, 0, 0, 0,
		0, SCALE->y, 0, 0,
		0, 0, SCALE->z, 0,
		0, 0, 0, 1.0);
}

Matrix::Matrix(float const &m0, float const &m1, float const &m2, float const &m3,
			   float const &m4, float const &m5, float const &m6, float const &m7,
			   float const &m8, float const &m9, float const &m10, float const &m11,
			   float const &m12, float const &m13, float const &m14, float const &m15)

	:m0(m0), m1(m1), m2(m2), m3(m3),
	m4(m4), m5(m5), m6(m6), m7(m7),
	m8(m8), m9(m9), m10(m10), m11(m11),
	m12(m12), m13(m13), m14(m14), m15(m15) {}

Matrix::Matrix(Vect4D const & v0, const Vect4D & v1, const Vect4D & v2, const Vect4D & v3)
{
	this->v0._m = v0._m;
	this->v1._m = v1._m;
	this->v2._m = v2._m;
	this->v3._m = v3._m;
}


Matrix::~Matrix()
{
	// nothign to delete
}

void Matrix::setIdentMatrix()
{ // initialize to the identity matrix
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;
		
	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 1.0f;
}

void Matrix::setTransMatrix(const Vect4D &t)
{ // set the translation matrix (note: we are row major)
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;
	
	this->m12 = t.x;
	this->m13 = t.y;
	this->m14 = t.z;
	this->m15 = 1.0f;
}

void Matrix::set(char const &row, const Vect4D * const t )
{
	// initialize the rows of the matrix
	switch( row )
	{
	case 0:
		this->m0 = t->x;
		this->m1 = t->y;
		this->m2 = t->z;
		this->m3 = t->w;
		break;

	case 1:
		this->m4 = t->x;
		this->m5 = t->y;
		this->m6 = t->z;
		this->m7 = t->w;
		break;

	case 2:
		this->m8 = t->x;
		this->m9 = t->y;
		this->m10 = t->z;
		this->m11 = t->w;
		break;

	case 3:
		this->m12 = t->x;
		this->m13 = t->y;
		this->m14 = t->z;
		this->m15 = t->w;
		break;

	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}

float &Matrix::operator[](const short &e)
{
	// get the individual elements
	switch(e)
	{
	case 0:
		return m0;
		break;
	case 1:
		return m1;
		break;
	case 2:
		return m2;
		break;
	case 3:
		return m3;
		break;
	case 4:
		return m4;
		break;
	case 5:
		return m5;
		break;
	case 6:
		return m6;
		break;
	case 7:
		return m7;
		break;
	case 8:
		return m8;
		break;
	case 9:
		return m9;
		break;	
	case 10:
		return m10;
		break;
	case 11:
		return m11;
		break;	
	case 12:
		return m12;
		break;	
	case 13:
		return m13;
		break;	
	case 14:
		return m14;
		break;
	case 15:
		return m15;
		break;
	default:
		assert(0);
		return m0;
		break;
	}
}

void Matrix::get(const char &row, Vect4D * const t ) const
{ // get a row of the matrix
	switch( row )
	{
	case 0:
		t->x = this->m0;
		t->y = this->m1;
		t->z = this->m2;
		t->w = this->m3;
		break;

	case 1:
		t->x = this->m4;
		t->y = this->m5;
		t->z = this->m6;
		t->w = this->m7;
		break;

	case 2:
		t->x = this->m8;
		t->y = this->m9;
		t->z = this->m10;
		t->w = this->m11;
		break;

	case 3:
		t->x = this->m12;
		t->y = this->m13;
		t->z = this->m14;
		t->w = this->m15;
		break;

	default:
		assert(0);
	}
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

#if 1
void Matrix::Inverse(Matrix &out)
{
	out = GetAdjugate();
}

#elif 1

#define MakeShuffleMask(x,y,z,w)           (x | (y<<2) | (z<<4) | (w<<6))

// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
#define VecSwizzle(vec, x,y,z,w)           _mm_shuffle_ps(vec, vec, MakeShuffleMask(x,y,z,w))
#define VecSwizzle1(vec, x)                _mm_shuffle_ps(vec, vec, MakeShuffleMask(x,x,x,x))
// special swizzle
#define VecSwizzle_0101(vec)               _mm_movelh_ps(vec, vec)
#define VecSwizzle_2323(vec)               _mm_movehl_ps(vec, vec)
#define VecSwizzle_0022(vec)               _mm_moveldup_ps(vec)
#define VecSwizzle_1133(vec)               _mm_movehdup_ps(vec)

// return (vec1[x], vec1[y], vec2[z], vec2[w])
#define VecShuffle(vec1, vec2, x,y,z,w)    _mm_shuffle_ps(vec1, vec2, MakeShuffleMask(x,y,z,w))
// special shuffle
#define VecShuffle_0101(vec1, vec2)        _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2)        _mm_movehl_ps(vec2, vec1)

void Matrix::Inverse(Matrix &out)
{
	Matrix r;

	// transpose 3x3, we know m03 = m13 = m23 = 0
	__m128 t0 = VecShuffle_0101(this->v0._m, this->v1._m); // 00, 01, 10, 11
	__m128 t1 = VecShuffle_2323(this->v0._m, this->v1._m); // 02, 03, 12, 13
	r.v0._m = VecShuffle(t0, this->m2._m, v0.x, v1.x, v2.x, 0); // 00, 10, 20, 23(=0)
	r.v1._m = VecShuffle(t0, this->m2._m, 1, 3, 1, 3); // 01, 11, 21, 23(=0)
	r.v2._m = VecShuffle(t1, this->m2._m, 0, 2, 2, 3); // 02, 12, 22, 23(=0)

														 // last line
	r.v3 = _mm_mul_ps(r.v0._m, VecSwizzle1(this->v3._m, 0));
	r.v3 = _mm_add_ps(r.v3._m, _mm_mul_ps(r.v1._m, VecSwizzle1(this->v3._m, 1)));
	r.v3 = _mm_add_ps(r.v3._m, _mm_mul_ps(r.v2._m, VecSwizzle1(this->v3._m, 2)));
	r.v3 = _mm_sub_ps(_mm_setr_ps(0.f, 0.f, 0.f, 1.f), r.v3._m);

	out = r;
}
#endif
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

void Matrix::setScaleMatrix(const Vect4D * const scale)
{
	//	{	sx		0		0		0	}
	//	{	0		sy		0		0	}
	//	{	0		0		sz		0	}
	//	{	0		0		0		1	}
	
	*this = Matrix(
		scale->x, 0, 0, 0,
		0, scale->y, 0, 0,
		0, 0, scale->z, 0,
		0, 0, 0, 1.0);
}

void Matrix::setRotZMatrix(const float &az)
{
	//	{	cos		-sin	0		0	}
	//	{	sin		cos		0		0	}
	//	{	0		0		1		0	}
	//	{	0		0		0		1	}
	
	*this = Matrix(
		cosf(az), -sinf(az), 0, 0,
		sinf(az), cosf(az), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

// End of file