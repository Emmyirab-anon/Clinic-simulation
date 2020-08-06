#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Patient
{
	string name;
	int age;
	string specCode;
	char emergency; //H for high, L for low
	int roomNumber;
};

