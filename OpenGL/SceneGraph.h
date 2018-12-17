#pragma once
#include "LinkedList.h"

class CelestialObject;

class SceneGraph
{
private:
	LinkedList* children; //The Children of the Parent

public:
	SceneGraph();
	~SceneGraph();

	void Update(LinkNode* node, float deltaTime, int& currentSpeed);
	void Render(LinkNode* node);

	void AddChild(CelestialObject* object); //Adds a Celestial Object to the children Linked list
	LinkedList* GetChildren(); //Gets the Children Linked List
	bool HasChildren(); //Checks if the parent has any children
};

