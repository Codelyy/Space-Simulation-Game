#pragma once

class CelestialObject;

//Node used to hold the data and pointer to the next node within the Linked List
struct LinkNode
{
	CelestialObject* data;
	LinkNode* next;

	~LinkNode()
	{
		delete data;
	}
};

class LinkedList
{
private:
	LinkNode* head; //The starting node of the linked size
	
	int size; //The size of the linked list

public:
	LinkedList();
	~LinkedList();

	void PushBackNode(CelestialObject* object); //Pushes a Node to the back of the linked list

	LinkNode* GetHeadNode();
	LinkNode* GetNode(int pos); //Gets a Node within the Linked List at a passed in position

	int GetSize();

private:
	LinkNode* MakeNode(CelestialObject* object); //Creates a Node from a Celestial Object to be placed within the Linked List
};

