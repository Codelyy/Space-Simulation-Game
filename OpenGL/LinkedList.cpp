#include "LinkedList.h"
 
LinkedList::LinkedList()
{
	head = nullptr;
	size = 0;
}

LinkedList::~LinkedList()
{  
	//Deletes all nodes within the Linked List
	LinkNode* node = head;
	LinkNode* currentNode;
	while (node != nullptr)
	{
		currentNode = node->next;
		delete node;
		node = currentNode;
	}

	delete head;
}

LinkNode* LinkedList::MakeNode(CelestialObject* object)
{
	//Creates a new node from a Celestial Object and returns it
	LinkNode* newNode = new LinkNode();
	newNode->data = object;
	newNode->next = nullptr;

	return newNode;
}

void LinkedList::PushBackNode(CelestialObject* object)
{
	size++;

	//Checks if there is a head, if it isn't then the new node is placed at the start of the Linked List and the head is linked to it
	LinkNode* newNode = MakeNode(object);
	if (head == nullptr)
	{
		head = newNode;
		return;
	}

	LinkNode* node = head;
	do
	{
		//Checks if there is another node within the Linked List after the current, if there isn't then it sets the next pointer of the last node to the new one
		if (node->next == nullptr)
		{
			node->next = newNode;
			return;
		}

		//If there is another node within the Linked List, move to it
		node = node->next;
	} 
	while (node != nullptr);
}

LinkNode* LinkedList::GetHeadNode()
{
	return head;
}

LinkNode * LinkedList::GetNode(int pos)
{
	//Moves through the Linked List and gets the node at the passed in position
	int count = 0;
	LinkNode* node = head;
	while (node != nullptr)
	{
		if (count == pos)
		{
			return node;
		}

		count++;
		node = node->next;
	}

	return nullptr;
}

int LinkedList::GetSize()
{
	return size;
}
