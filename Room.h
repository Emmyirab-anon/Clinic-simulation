#pragma once
#include <iostream>
#include <string>
#include "Queue.h"
#include "Doctor.h"
#include "Patient.h"
using namespace std;

struct Room
{
	Doctor doc; //current doctor using the room
	Patient pat; //current patient in the room
	Queue myQueue;
};

