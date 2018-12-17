#pragma once
#include "Structurers.h"
#include "Texture2D.h"

class Skybox
{
private:
	Mesh* mesh; //The Objects Mesh
	Texture2D* texture; //The Objects Texture

	Material* material; //The Material used on the Skybox

	Vector3 scale; //The Skybox's Scale

public:
	Skybox();

	void Render();

	void ApplyMesh(std::string path); //Applies a Mesh to the Object, gathered from path
	void ApplyTexture(std::string path, int width, int height); //Applies a Texture to the object, gathered from path with a given Width and Height
};

