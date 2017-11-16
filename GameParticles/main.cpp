#include <assert.h>

// Offset to local directory
// REALLY useful trick to insure that you link to your code not some other library
#include "DO_NOT_MODIFY\Timer.h"
#include "DO_NOT_MODIFY\GlobalTimer.h"
#include "DO_NOT_MODIFY\EventHandler.h"
#include "DO_NOT_MODIFY\OpenGLInterface.h"

#include "ParticleEmitter.h"

#define UNUSED_VAR(v) ((void *)v)

// main program
int main()
{
	// initialize timers:------------------------------

	// Initialize timer
	timer::initTimer();

	// Create a global Timer
	globalTimer::create();

	// Create a timer objects
	timer updateTimer;
	timer drawTimer;

	// create a window:---------------------------------
	OpenGLDevice::InitWindow();

	// create an emitter:-------------------------------

	//i made the emitter a pointer because its 4 bytes compared to 64
	ParticleEmitter *emitter = new ParticleEmitter();

	// Get the inverse Camera Matrix:-------------------

	// initialize the camera matrix
	Matrix CameraMatrix;
	CameraMatrix.setIdentMatrix();

	// setup the translation matrix
	Matrix TransMatrix(Vect4D(0.0f, 3.0f, 10.0f));

	// multiply them together
	Matrix tmp(CameraMatrix * TransMatrix);

	// counter for printing (changed from int to char to save a few bytes. probably insignificant)
	char i = 0;

	Matrix inverseCameraMatrix;
	tmp.Inverse(inverseCameraMatrix);

	// main update loop... do this forever or until some breaks 
	while (OpenGLDevice::IsRunning())
	{
		// start update timer ---------------------------------------
		updateTimer.tic();

		// start draw... end draw (the draw updates)
		OpenGLDevice::StartDraw();

		// set matrix to Model View
		// push the inverseCameraMarix to stack
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(reinterpret_cast<float*>(&inverseCameraMatrix));

		// update the emitter
		emitter->update();

		// stop update timer: -----------------------------------------
		updateTimer.toc();

		// start draw timer: ----------------------------------------
		drawTimer.tic();

		// draw particles
		emitter->draw();

		// stop draw timer: -----------------------------------------
		drawTimer.toc();

		// finish draw update
		OpenGLDevice::EndDraw();

		// Love for Windows - allows the windows to behave to external events
		EventHandler::ProcessEvents();

		// update ouput every 50 times
		++i;
		if (i > 25)
		{
			i = 0;
			float updateTime = updateTimer.timeInSeconds();
			float drawTime = drawTimer.timeInSeconds();
			printf("\nLoopTime: update:%f ms  draw:%f ms  tot:%f\n", updateTime * 1000.0f, drawTime * 1000.0f, (updateTime + drawTime) *1000.0f);
		}
	}
	delete emitter;
	return 0;
}


// End of file