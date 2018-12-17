#include "Skybox.h"
#include "OBJLoader.h"

Skybox::Skybox()
{
	ApplyMesh("Skybox.obj"); //Applies a Mesh to the Object
	ApplyTexture("Skybox.tga", 2048, 1024); //Applies a Texture to the Object with a given Width and Height

	scale = Vector3(200.0f, 200.0f, 200.0f);

	//Sets the information about the Material used by the Skybox
	material = new Material(); 
	material->ambient.X = 5.0; material->ambient.Y = 5.0; material->ambient.Z = 5.0;
	material->ambient.W = 1.0;
	material->diffuse.X = 5.0; material->diffuse.Y = 5.0; material->diffuse.Z = 5.0;
	material->diffuse.W = 1.0;
}

void Skybox::Render()
{
	if (texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, texture->GetID()); //Applies the Texture
	}

	//Enables Client States and passes in model data if the mesh has texture coords
	if (mesh->hasTexCoords && !mesh->hasNormals)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, mesh->vertices.data());
		glTexCoordPointer(2, GL_FLOAT, 0, mesh->texCoords.data());
	}

	//Enables Client States and passes in model data if the mesh has texture coords and normals
	if (mesh->hasTexCoords && mesh->hasNormals)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, sizeof(Vector3), mesh->vertices.data());
		glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoord), mesh->texCoords.data());
		glNormalPointer(GL_FLOAT, 0, mesh->normals.data());
	}

	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material->diffuse.X)); //Applies the Material

	glPushMatrix();

	glScalef(scale.X, scale.Y, scale.Z);

	glDrawElements(GL_TRIANGLES, mesh->indiceCount, GL_UNSIGNED_SHORT, mesh->indices); //Draws the Skybox

	glPopMatrix();

	//Disables the Client States if the mesh only has texture coords
	if (mesh->hasTexCoords && !mesh->hasNormals)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	//Disables the Client States if the mesh has texture coords and normals
	if (mesh->hasTexCoords && mesh->hasNormals)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);	
	}
}

void Skybox::ApplyMesh(std::string path)
{
	std::string dir = "Assets/Models/" + path;
	mesh = OBJLoader::LoadModel(dir.c_str());
}

void Skybox::ApplyTexture(std::string path, int width, int height)
{
	texture = new Texture2D();
	std::string dir = "Assets/Textures/" + path;
	texture->LoadTGA(dir.c_str());
}
