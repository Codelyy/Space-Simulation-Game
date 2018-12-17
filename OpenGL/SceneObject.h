#pragma once
#include "Structurers.h"
#include "SceneGraph.h"

class Texture2D;

class SceneObject
{
protected:
	Mesh* mesh; //The Objects Mesh
	Texture2D* texture; //The Objects Texture

	SceneGraph* sceneGraph;

	Vector3 position; //The Position of the Object

	float rotationAngle; //The angle used for rotation
	Vector3 rotation; //Vector3 to say what axis the Object rotates in

	float orbitAngle; //The angle of Orbit
	Vector3 orbitRotation; //The rotation of the Orbit

	Vector3 scale = Vector3(1, 1, 1); //Vector3 used for scaling the Model. Default is 1, 1, 1

	char* tag; //The Tag each Scene Object is assigned

public:
	SceneObject();
	virtual ~SceneObject(void);

	virtual void Update(float deltaTime, int& currentSpeed);
	virtual void Render();

	void AddSceneGraph();
	SceneGraph* GetSceneGraph();

	void ApplyMesh(std::string path); //Applies a Mesh to the Object, gathered from path
	void ApplyTexture(std::string path, int width, int height); //Applies a Texture to the object, gathered from path with a given Width and Height

	void SetPosition(Vector3 pos); //Sets Position of Scene Object
	Vector3 GetPosition(); //Gets the Position of the Scene Object

	void SetScale(Vector3 scale); //Sets Scene Object's Scale

	void SetTag(char* tag);
	char* GetTag();
};

