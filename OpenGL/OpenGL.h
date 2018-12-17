#pragma once
#include "GL\/freeglut.h"
#include "Structurers.h"
#include "SceneGraph.h"
#include "Text.h"

#define REFRESHRATE 16

class Camera;
class Skybox;

class OpenGL
{
private:
	Camera* camera;
	Skybox* skybox;

	CelestialObject* sun;

	Vector4 lightPosition; //The Position of the main light within the scene (The Sun)
	Lighting lightData; //Information about the intensity of the light

	int currentSpeed; //The current speed of the Simulation
	Text* currentSpeedText; //The text to display the current speed of the simulation

public:
	OpenGL(int argc, char* argv[]);
	~OpenGL();

	void InitObjects();
	void InitGL(int argc, char* argv[]);

	void Display(); //The Render Function
	void Update(); //The Update function

	void Keyboard(unsigned char key, int x, int y);
	void MouseMovement(int x, int y);
};

