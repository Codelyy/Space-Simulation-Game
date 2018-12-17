#pragma once
#include "GL\/freeglut.h"
#include "Structurers.h"

class Text
{
private:
	std::string text; //The actual Text

	Vector3 scale; //The scale of the Text

public:
	Text();

	void Render2D(Vector2 pos); //Renders 2D text on the screen
	void Render3D(Vector3 pos); //Renders the Text within a 3D space

	void SetText(std::string text);
	void SetScale(Vector3 scale);

	//Used for changing the projection type when switching between 2D and 3D text
	void SetOrthographicProjection(); 
	void RestorePerspectiveProjection();
};

