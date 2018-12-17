#pragma once

class OpenGL;

namespace GLUTCallbacks
{
	void Init(OpenGL* openGl);
	void Display(); //Runs the Render Function
	void Timer(int preferredRefresh); //Runs the Update Function
	void Keyboard(unsigned char key, int x, int y); //Handles in Keyboard Input
	void PassiveMouseMovement(int x, int y); //Handles Constant Mouse Input
};