#include "Queue.h"

Queue::Queue()
{
	front = NULL;
	rear = NULL;
	length = 0;
}

Queue::~Queue()
{
	MakeEmpty();
}

void Queue::MakeEmpty()
{
	Node* temp;
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
	rear = NULL;
	length = 0;
}

bool Queue::IsEmpty() const
{
	return (rear == front);
}

bool Queue::IsFull()const
{
	Node* location;
	try
	{
		location = new Node;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

void Queue::Enqueue(Patient newitem)
{
	if (IsFull())
		throw FullQueue();
	else
	{
		Node* newNode = new Node;
		newNode->data = newitem;
		newNode->next = NULL;

		if (rear == NULL)
			front = newNode;
		else
		{
			//check for emergency
			if (newitem.emergency == 'H' || newitem.emergency == 'h')
			{
				//push to the front
				newNode->next = front;
				front = newNode;
			}
			else if (newitem.emergency == 'L' || newitem.emergency == 'l')
			{
				rear->next = newNode;
			}
			rear = newNode;
		}
	}
	length++;
}

void Queue::Dequeue(Patient& item)
{
	if (IsEmpty())
		throw EmptyQueue();
	else
	{
		Node* temp = front;
		item = front->data;
		front = front->next;
		if (front == NULL)
			rear = NULL;
		delete temp;
	}
	length--;
}

Patient& Queue::firstElement()const
{
	return front->data;
}

int Queue::getLength()const
{
	return length;
}