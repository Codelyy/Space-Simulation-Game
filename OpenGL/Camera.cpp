#include "Camera.h"
#include "Maths.h"
#include "GL\freeglut.h"
#include <iostream>

Camera::Camera()
{
	position = Vector3(0.0f, 0.0f, 500.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
	cameraFront = Vector3(0.0f, 0.0f, -1.0f);

	cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	cameraSpeed = 5.0f;

	yaw = -90.0f;
	pitch = 0.0f;
	firstMouse = true;
}

void Camera::Render()
{
	//Sets the Camera to looked the specified location
	glLoadIdentity();
	gluLookAt(position.X, position.Y, position.Z, position.X + cameraFront.X, position.Y + cameraFront.Y, position.Z + cameraFront.Z, cameraUp.X, cameraUp.Y, cameraUp.Z);
}

void Camera::Keyboard(unsigned char key, int x, int y)
{
	//Move the Camera Left or Right
	if (key == 'a')
	{
		position.X -= Vector3::Normalize(Vector3::Cross(cameraFront, cameraUp)).X * cameraSpeed;
		position.Y -= Vector3::Normalize(Vector3::Cross(cameraFront, cameraUp)).Y * cameraSpeed;
		position.Z -= Vector3::Normalize(Vector3::Cross(cameraFront, cameraUp)).Z * cameraSpeed;
	}
	if (key == 'd')
	{
		position.X += Vector3::Normalize(Vector3::Cross(cameraFront, cameraUp)).X * cameraSpeed;
		position.Y += Vector3::Normalize(Vector3::Cross(cameraFront, cameraUp)).Y * cameraSpeed;
		position.Z += Vector3::Normalize(Vector3::Cross(cameraFront, cameraUp)).Z * cameraSpeed;
	}

	//Move the Camera Forward or Backwards
	if (key == 'w')
	{
		position.X += cameraSpeed * cameraFront.X;
		position.Y += cameraSpeed * cameraFront.Y;
		position.Z += cameraSpeed * cameraFront.Z;
	}
	if (key == 's')
	{
		position.X -= cameraSpeed * cameraFront.X;
		position.Y -= cameraSpeed * cameraFront.Y;
		position.Z -= cameraSpeed * cameraFront.Z;
	}

	//Move the camera Up or Down
	if (key == 'q')
	{
		position.X += cameraSpeed * cameraUp.X;
		position.Y += cameraSpeed * cameraUp.Y;
		position.Z += cameraSpeed * cameraUp.Z;
	}
	if (key == 'e')
	{
		position.X -= cameraSpeed * cameraUp.X;
		position.Y -= cameraSpeed * cameraUp.Y;
		position.Z -= cameraSpeed * cameraUp.Z;
	}
}

void Camera::MouseInput(int x, int y)
{
	//Used to move the Camera with the mouse (ONLY 180 DEGREES)
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;

	//Applies the sensitivity to the mouse speed
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	Vector3 front;
	front.X = cos(Maths::DegreesToRadians(yaw)) * cos(Maths::DegreesToRadians(pitch));
	front.Y = sin(Maths::DegreesToRadians(pitch));
	front.Z = sin(Maths::DegreesToRadians(yaw)) * cos(Maths::DegreesToRadians(pitch));
	cameraFront.X = Vector3::Normalize(front).X;
	cameraFront.Y = Vector3::Normalize(front).Y;
	cameraFront.Z = Vector3::Normalize(front).Z;
}

void Camera::SetPosition(Vector3 pos)
{
	position = pos;
}
