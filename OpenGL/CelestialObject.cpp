#include "CelestialObject.h"
#include "Text.h"
#include <iostream>

CelestialObject::CelestialObject(CelestialType type)
{
	rotation = Vector3(0.0f, 1.0f, 0.0f);
	orbitRotation = Vector3(1.0f, 1.0f, 1.0f);

	//Sets the correct information for the corresponding celestial type
	celestialtype = type;
	switch (type)
	{
		case CelestialType::SUN:
			ApplyMesh("Sun.obj"); //Applies a Mesh to the Object
			ApplyTexture("Sun.tga", 2048, 1024); //Applies a Texture to the Object with a given Width and Height

			SetScale(Vector3(8.0f, 8.0f, 8.0f));

			rotationSpeed = 0.2f;

			textHeight = 45.0f;

			SetTag("Sol");
		break;

		case CelestialType::MERCURY:
			ApplyMesh("Planet.obj");
			ApplyTexture("Mercury.tga", 2048, 1024);

			SetScale(Vector3(0.2f, 0.2f, 0.2f));

			rotationSpeed = 0.1f;
			orbitSpeed = 5.0f;

			textHeight = 3.0f;

			SetTag("Mercury");
		break;

		case CelestialType::VENUS:
			ApplyMesh("Planet.obj");
			ApplyTexture("Venus.tga", 2048, 1024);

			SetScale(Vector3(0.5f, 0.5f, 0.5f));

			rotationSpeed = 0.05f;
			orbitSpeed = 8.0f;

			textHeight = 4.0f;

			SetTag("Venus");
		break;

		case CelestialType::EARTH:
			ApplyMesh("Planet.obj");
			ApplyTexture("Earth.tga", 2048, 1024);

			SetScale(Vector3(0.5f, 0.5f, 0.5f));

			rotationSpeed = 2.0f;
			orbitSpeed = 5.0f;

			textHeight = 4.0f;

			SetTag("Earth");
		break;

		case CelestialType::MOON:
			ApplyMesh("Planet.obj");
			ApplyTexture("Moon.tga", 2048, 1024);
			SetScale(Vector3(0.25f, 0.25f, 0.25f));

			rotationSpeed = 1.0f;
			orbitSpeed = 0.8f;

			textHeight = 2.0f;

			SetTag("Moon");
		break;

		case CelestialType::MARS:
			ApplyMesh("Planet.obj");
			ApplyTexture("Mars.tga", 2048, 1024);

			SetScale(Vector3(0.4f, 0.4f, 0.4f));

			rotationSpeed = 1.9f;
			orbitSpeed = 1.5f;

			textHeight = 4.0f;

			SetTag("Mars");
			break;

		case CelestialType::JUPITER:
			ApplyMesh("Planet.obj");
			ApplyTexture("Jupiter.tga", 2048, 1024);

			SetScale(Vector3(3.0f, 3.0f, 3.0f));

			rotationSpeed = 3.4f;
			orbitSpeed = 0.8f;

			textHeight = 20.0f;

			SetTag("Jupiter");
		break;

		case CelestialType::SATURN:
			ApplyMesh("Saturn.obj");
			ApplyTexture("Saturn.tga", 2048, 1024);

			SetScale(Vector3(2.5f, 2.5f, 2.5f));

			rotationSpeed = 3.3f;
			orbitSpeed = 0.5f;

			textHeight = 15.0f;

			SetTag("Saturn");
		break;

		case CelestialType::URANUS:
			ApplyMesh("Planet.obj");
			ApplyTexture("Uranus.tga", 2048, 1024);

			SetScale(Vector3(1.5f, 1.5f, 1.5f));

			rotationSpeed = 2.6f;
			orbitSpeed = 0.3f;

			textHeight = 15.0f;

			SetTag("Uranus");
		break;

		case CelestialType::NEPTUNE:
			ApplyMesh("Planet.obj");
			ApplyTexture("Neptune.tga", 2048, 1024);

			SetScale(Vector3(1.4f, 1.4f, 1.4f));

			rotationSpeed = 2.7f;
			orbitSpeed = 0.1f;

			textHeight = 15.0f;

			SetTag("Neptune");
		break;
	}

	orbitVelocity = Vector3(1, 1, 1);

	textTag = new Text();
}

void CelestialObject::Update(float deltaTime, int currentSpeed)
{
	SceneObject::Update(deltaTime, currentSpeed);

	//Increases the Rotation and Orbit angles by the current speed of the simulation and a speed so the Planets do rotate
	rotationAngle += rotationSpeed * currentSpeed;
	orbitAngle += orbitSpeed * currentSpeed;

	textTag->SetText(tag);
	textTag->SetScale(Vector3(1, 1, 1));
}

void CelestialObject::Render()
{
	SceneObject::Render();

	textTag->Render3D(Vector3(position.X - 2.5f, textHeight, position.Z)); //Renders the Tag of the Planets
}
