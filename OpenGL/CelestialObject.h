#pragma once
#include "SceneObject.h"
#include "Text.h"

//each type of Celestial Body
enum CelestialType
{
	SUN,
	MERCURY,
	VENUS,
	EARTH,
	MOON,
	MARS,
	JUPITER,
	SATURN,
	URANUS,
	NEPTUNE
};

class CelestialObject : public SceneObject
{
private:
	CelestialType celestialtype; //The Celestial Bodies type

	float rotationSpeed; //The Rotation Speed of the Celestial Body
	float orbitSpeed; //The Orbit speed of the Celestial Body

	Vector3 orbitVelocity; //The Orbit velocity

	Text* textTag; //Text object used to display text above the Celestial Body
	float textHeight; //The height of the Text 

public:
	CelestialObject(CelestialType type);

	void Update(float deltaTime, int currentSpeed);
	void Render();
};

