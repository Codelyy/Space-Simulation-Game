#include "OpenGL.h"
#include "GLUTCallbacks.h"
#include "CelestialObject.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include "Skybox.h"

OpenGL::OpenGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	InitGL(argc, argv);
	InitObjects();

	SetCursorPos(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2); //Sets the Mouse Cursor to the middle of the screen

	glutMainLoop();
}

OpenGL::~OpenGL()
{
	delete camera;
	delete skybox;
	delete sun;
	delete currentSpeedText;
}

void OpenGL::InitObjects()
{
	camera = new Camera();
	skybox = new Skybox();

	//Creates all the Planets and Sets their positions relative to the Sun
	sun = new CelestialObject(CelestialType::SUN);
	sun->SetPosition(Vector3(0, 0, 0));

	CelestialObject* mercuryObject = new CelestialObject(CelestialType::MERCURY);
	mercuryObject->SetPosition(Vector3(15, 0, 0));

	CelestialObject* venusObject = new CelestialObject(CelestialType::VENUS);
	venusObject->SetPosition(Vector3(30, 0, 0));

	CelestialObject* earthObject = new CelestialObject(CelestialType::EARTH);
	earthObject->SetPosition(Vector3(45, 0, 0));

	CelestialObject* moonObject = new CelestialObject(CelestialType::MOON);
	moonObject->SetPosition(Vector3(10, 0, 0));

	CelestialObject* marsObject = new CelestialObject(CelestialType::MARS);
	marsObject->SetPosition(Vector3(60, 0, 0));

	CelestialObject* jupiterObject = new CelestialObject(CelestialType::JUPITER);
	jupiterObject->SetPosition(Vector3(110, 0, 0));

	CelestialObject* saturnObject = new CelestialObject(CelestialType::SATURN);
	saturnObject->SetPosition(Vector3(190, 0, 0));

	CelestialObject* uranusObject = new CelestialObject(CelestialType::URANUS);
	uranusObject->SetPosition(Vector3(300, 0, 0));

	CelestialObject* neptuneObject = new CelestialObject(CelestialType::NEPTUNE);
	neptuneObject->SetPosition(Vector3(400, 0, 0));

	//Adds a Scene Graph to the Sun and adds all the Planets to it
	sun->AddSceneGraph();
	sun->GetSceneGraph()->AddChild(mercuryObject);
	sun->GetSceneGraph()->AddChild(venusObject);
	sun->GetSceneGraph()->AddChild(earthObject);
	sun->GetSceneGraph()->AddChild(marsObject);
	sun->GetSceneGraph()->AddChild(jupiterObject);
	sun->GetSceneGraph()->AddChild(saturnObject);
	sun->GetSceneGraph()->AddChild(uranusObject);
	sun->GetSceneGraph()->AddChild(neptuneObject);

	//Adds a Scene Graph to the Earth and adds the moon as a Child to it
	earthObject->AddSceneGraph();
	earthObject->GetSceneGraph()->AddChild(moonObject);

	//Sets the position of the Main Light within the scene as well as it's information (USES DIFFUSE)
	lightPosition = Vector4(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z, 1.0f);
	lightData = Lighting();
	lightData.diffuse.X = 6.0;
	lightData.diffuse.Y = 6.0;
	lightData.diffuse.Z = 6.0;
	lightData.diffuse.W = 0.0;

	//Sets the current speed of the simulation And sets the Text
	currentSpeed = 1;
	currentSpeedText = new Text();
	currentSpeedText->SetText("Current Speed: " + std::to_string(currentSpeed));
}

void OpenGL::InitGL(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("The Solar System");

	//Enables Key features of the Application such as Backface Culling and the Depth Test 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutPassiveMotionFunc(GLUTCallbacks::PassiveMouseMovement);

	//Sets the View port and perspective and then switches to the Model View
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 800, 600);
	gluPerspective(45, 800.0f / 600.0f, 0.1, 6000);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Adds the Main light to the scene, using Diffuse 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData.diffuse.X));
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightPosition.X));

	camera->Render();
	skybox->Render();

	sun->Render();

	currentSpeedText->Render2D(Vector2(10.0f, 30.0f)); //Renders the Simulation Speed text at the top left of the Screen

	glFlush();

	glutSwapBuffers();
}

int oldTime = 0;
void OpenGL::Update()
{
	//Gets Delta Time and passes it to the Update Function of the sun
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTime - oldTime;
	oldTime = newTime;

	glutPostRedisplay();

	sun->Update(deltaTime, currentSpeed);

	Sleep(10);
}

void OpenGL::Keyboard(unsigned char key, int x, int y)
{
	camera->Keyboard(key, x, y);

	//Keyboard controls used to move the sun. Will change sun's position as well as the main lights position
	switch (key)
	{
		case 'j':
			sun->SetPosition(Vector3(sun->GetPosition().X - 5, sun->GetPosition().Y, sun->GetPosition().Z));
			lightPosition = Vector4(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z, 1.0f);
		break;

		case 'l':
			sun->SetPosition(Vector3(sun->GetPosition().X + 5, sun->GetPosition().Y, sun->GetPosition().Z));
			lightPosition = Vector4(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z, 1.0f);
		break;

		case 'i':
			sun->SetPosition(Vector3(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z - 5));
			lightPosition = Vector4(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z, 1.0f);
		break;

		case 'k':
			sun->SetPosition(Vector3(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z + 5));
			lightPosition = Vector4(sun->GetPosition().X, sun->GetPosition().Y, sun->GetPosition().Z, 1.0f);
		break;
	}

	//Keyboard controls used to set the speed of the simulation
	switch (key)
	{
		case '0':
			currentSpeed = 0;
		break;

		case '1':
			currentSpeed = 1;
		break;

		case '2':
			currentSpeed = 2;
		break;

		case '3':
			currentSpeed = 3;
		break;

		case '4':
			currentSpeed = 4;
		break;

		case '5':
			currentSpeed = 5;
		break;

		case '6':
			currentSpeed = 6;
		break;

		case '7':
			currentSpeed = 7;
		break;

		case '8':
			currentSpeed = 8;
		break;

		case '9':
			currentSpeed = 9;
		break;
	}
	currentSpeedText->SetText("Current Speed: " + std::to_string(currentSpeed));
}

void OpenGL::MouseMovement(int x, int y)
{
	camera->MouseInput(x, y);
}
