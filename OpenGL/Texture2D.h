#pragma once
#include "Structurers.h"

class Texture2D
{
private:
	GLuint ID; //The ID given to each Texture
	int width; //The Width of the Texture
	int height; //The Height of the Texture

public:
	bool LoadTGA(const char* path); //Loads a image of a TGA file format and create a Texture from it

	GLuint GetID();
	int GetWidth();
	int GetHeight();
};

