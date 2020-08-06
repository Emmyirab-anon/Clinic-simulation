#pragma once
#include <iostream>
#include "Patient.h"
using namespace std;

struct Node
{
	Patient data;
	Node* next;
};

class EmptyQueue
{};
class FullQueue
{};

class Queue {
public:
	Queue();
	~Queue();
	void MakeEmpty();
	bool IsEmpty()const;
	bool IsFull()const;
	void Enqueue(Patient newitem);
	void Dequeue(Patient& item);

	//Accessors
public:
	Patient& firstElement()const;
	int getLength()const;
private:
	Node* front;
	Node* rear;
	int length; //To get the length of items in the queue
};

