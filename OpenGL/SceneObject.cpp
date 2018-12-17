#include "SceneObject.h"
#include "Texture2D.h"
#include "OBJLoader.h"
#include <iostream>

SceneObject::SceneObject()
{
	rotationAngle = 0.0f;
	orbitAngle = 0.0f;
}

SceneObject::~SceneObject(void)
{	
	delete mesh;
	delete texture;

	if (sceneGraph != nullptr)
	{
		delete sceneGraph;
	}
}

void SceneObject::Update(float deltaTime, int& currentSpeed)
{
	//If the Rotation Angle Goes above 360 Degrees, drop it back to 0
	if (rotationAngle >= 360.0f)
	{
		rotationAngle = 0.0f;
	}

	if (orbitAngle >= 360.0f)
	{
		orbitAngle = 0.0f;
	}

	if (sceneGraph != nullptr)
	{
		sceneGraph->Update(sceneGraph->GetChildren()->GetHeadNode(), deltaTime, currentSpeed); //Runs the Update function of each Child if there is any
	}
}

void SceneObject::Render()
{
	if (texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, texture->GetID()); //Gets a Texture
	}
	
	//Enables Client States and passes in model data if there is a mesh
	if (mesh != nullptr)
	{
		if (mesh->hasTexCoords && !mesh->hasNormals)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, mesh->vertices.data());
			glTexCoordPointer(2, GL_FLOAT, 0, mesh->texCoords.data());
		}

		if (mesh->hasTexCoords && mesh->hasNormals)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);

			glVertexPointer(3, GL_FLOAT, sizeof(Vector3), mesh->vertices.data());
			glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoord), mesh->texCoords.data());
			glNormalPointer(GL_FLOAT, 0, mesh->normals.data());
		}
	}

	//Disables Lighting if the current rendering object is the Sun
	if (GetTag() == "Sol")
		glDisable(GL_LIGHTING);

	glPushMatrix();

	//Applies the Transformation Matrices 
	glTranslatef(position.X, position.Y, position.Z);
	glRotatef(rotationAngle, rotation.X, rotation.Y, rotation.Z);
	glScalef(scale.X, scale.Y, scale.Z);

	//Draws the Model if there is one using passed in indices
	if (mesh != nullptr)
	{
		glDrawElements(GL_TRIANGLES, mesh->indiceCount, GL_UNSIGNED_SHORT, mesh->indices);
	}

	glEnable(GL_LIGHTING);
	if (sceneGraph != nullptr)
	{
		sceneGraph->Render(sceneGraph->GetChildren()->GetHeadNode()); //Runs the Render function of each Child
	}

	glPopMatrix();

	//Disables the Client States if there is a mesh
	if (mesh != nullptr)
	{
		if (mesh->hasTexCoords && !mesh->hasNormals)
		{
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		if (mesh->hasTexCoords && mesh->hasNormals)
		{
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
	}
}

void SceneObject::AddSceneGraph()
{
	sceneGraph = new SceneGraph();
}

SceneGraph * SceneObject::GetSceneGraph()
{
	return sceneGraph;
}

void SceneObject::ApplyMesh(std::string path)
{
	std::string dir = "Assets/Models/" + path;
	mesh = OBJLoader::LoadModel(dir.c_str());
}

void SceneObject::ApplyTexture(std::string path, int width, int height)
{
	texture = new Texture2D();
	std::string dir = "Assets/Textures/" + path;
	texture->LoadTGA(dir.c_str());
}

void SceneObject::SetPosition(Vector3 pos)
{
	position = pos;
}

Vector3 SceneObject::GetPosition()
{
	return position;
}

void SceneObject::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void SceneObject::SetTag(char* tag)
{
	this->tag = tag;
}

char* SceneObject::GetTag()
{
	return tag;
}
