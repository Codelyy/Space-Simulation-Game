#pragma once
#include "Structurers.h"

class Camera
{
private:
	Vector3 position;
	Vector3 target; //What the camera is focused on
	Vector3 direction; //Which direction the Camera is facing

	Vector3 cameraFront; //The front vector of the camera
	Vector3 cameraRight; //The right vector of the camera
	Vector3 cameraUp; //The up vector of the Camera

	float cameraSpeed; //The Speed at which the camera moves

	//Varaibles used for Mouse Control
	float lastX;
	float lastY;
	float pitch;
	float yaw;
	bool firstMouse;
	
	bool warpingMouse; //If the camera goes off screen

	float sensitivity = 0.2f; //The Camera's sensitivity 

public:
	Camera();

	void Render();

	void Keyboard(unsigned char key, int x, int y);
	void MouseInput(int x, int y);

	void SetPosition(Vector3 pos);
};

