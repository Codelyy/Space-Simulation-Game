#include "GLUTCallbacks.h"
#include "OpenGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		OpenGL* openGL = nullptr;
	}

	void Init(OpenGL* gl)
	{
		openGL = gl;
	}

	void Display()
	{
		if (openGL != nullptr)
		{
			openGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		//Gets the Delta Time value and passes it to the Update function
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		openGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		openGL->Keyboard(key, x, y);
	}

	void PassiveMouseMovement(int x, int y)
	{
		openGL->MouseMovement(x, y);
	}
};