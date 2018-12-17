#include "SceneGraph.h"
#include "CelestialObject.h"
#include <iostream>

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	delete children;
}

void SceneGraph::Update(LinkNode* node, float deltaTime, int& currentSpeed)
{
	//Checks if there is children within the Screne Graph
	if (HasChildren())
	{
		node->data->Update(deltaTime, currentSpeed); //Runs the Childs Update function

		//Checks if there is another node within the Linked List, if there is then run the function again for that node
		if (node->next != nullptr)
		{
			Update(node->next, deltaTime, currentSpeed);
		}
	}
}

void SceneGraph::Render(LinkNode* node)
{
	//Checks if there is children within the Screne Graph
	if (HasChildren())
	{
		node->data->Render(); //Runs the Childs Render function

		//Checks if there is another node within the Linked List, if there is then run the function again for that node
		if (node->next != nullptr)
		{
			Render(node->next);
		}
	}
}

void SceneGraph::AddChild(CelestialObject* object)
{
	//If the linked list of children hasn't been created, create one and then push a Celestial Object to the back of the Linked List
	if (children == nullptr)
	{
		children = new LinkedList();
	}

	children->PushBackNode(object);
}

LinkedList* SceneGraph::GetChildren()
{
	return children;
}

bool SceneGraph::HasChildren()
{
	//Returns if the Linked List has children
	if (children == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}
