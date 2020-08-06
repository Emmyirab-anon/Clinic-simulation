#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include "Doctor.h"
#include "Patient.h"
#include "Room.h"
using namespace std;

void assignPatient(Room rooms[], Patient pat);

ofstream outFile;

int main()
{
	Room rooms[100];
	outFile.open("trans.out");
	char firstPrompt, secondPrompt, next = 'Y';
	while (next == 'Y' || next == 'y')
	{
		cout << "Type D for Doctor and P for Patient: "; outFile << "Type D for Doctorand P for Patient: ";
		cin >> firstPrompt;
		outFile << firstPrompt << endl;
		cout << "Type I to check-in and O to check-out: "; outFile << "Type I to check-in and O to check-out: ";
		cin >> secondPrompt;
		outFile << secondPrompt << endl;

		//Doctor
		if (firstPrompt == 'D' || firstPrompt == 'd')
		{
			Doctor myDoc;
			//Check-in
			if (secondPrompt == 'I' || secondPrompt == 'i')
			{
				int number;
				cout << "Please enter your name Doctor: "; outFile << "Please enter your name Doctor: " << endl;
				cin.ignore(256, '\n');
				getline(cin, myDoc.name);
				cout << "Please enter your specialty: "; outFile << "Please enter your specialty: "<< endl;
				cin >> myDoc.specCode;
				cout << "Please enter your preferred room number: "; outFile << "Please enter your preferred room number: " << endl;
				cin >> number;

				myDoc.roomNumber = number - 1;
				//check if room is free;
				while (rooms[myDoc.roomNumber].doc.name != "")
				{
					cout << "Room is currently taken, please try again!" << endl;
					outFile << "Room is currently taken, please try again!" << endl;
					cout << "Please enter your preferred room number: "; outFile << "Please enter your preferred room number: " << endl;
					cin >> number;
					myDoc.roomNumber = number - 1;
				}

				//Assign if room is free.
				rooms[myDoc.roomNumber].doc = myDoc;
				cout << "Doctor " << myDoc.name << "(" << myDoc.specCode << ")";
				cout << " has successfully checked into room " << number << endl;
				outFile << "Doctor " << myDoc.name << "(" << myDoc.specCode << ")";
				outFile << " has successfully checked into room " << number << endl;
					
			}
			//Check-out
			else if (secondPrompt == 'O' || secondPrompt == 'o')
			{
				string name;
				int roomNumb;
				cout << "Please enter your name: "; outFile << "Please enter your name: " << endl;
				cin.ignore(256, '\n');
				getline(cin,name);
				cout << "What room were you in?: "; outFile << "What room were you in?: " << endl;
				cin >> roomNumb;

				//check out
				rooms[roomNumb - 1].doc.name = "";
				cout << "Doctor " << name << " has successfully checked out." << endl;
				outFile << "Doctor " << name << " has successfully checked out." << endl;
			}
		}

		//Patient
		if (firstPrompt == 'P' || firstPrompt == 'p')
		{
			Patient myPat;
			//Check-in
			if (secondPrompt == 'I' || secondPrompt == 'i')
			{
				cout << "Please enter your name: "; outFile << "Please enter your name: " << endl;
				cin.ignore(256, '\n');
				getline(cin,myPat.name);
				cout << "How old are you?: "; outFile << "How old are you: " << endl;
				cin >> myPat.age;
				cout << "Emergency? H for high, L for low: "; outFile << "Emergency? H for high, L for low:  " << endl;
				cin >> myPat.emergency;

				//check age
				if (myPat.age >= 16)
				{
					cout << "Which specialty?: "; outFile << "Which specialty?: " << endl;
					cin >> myPat.specCode;
				}
				else if (myPat.age < 16)
					myPat.specCode = "PED";

				//check if there is a doctor with thesame specialty as the spatient
				int seen = 0;
				for (int i = 0; i < 100; i++)
				{
					if (rooms[i].doc.name != "" && rooms[i].doc.specCode == myPat.specCode)
						seen++;
				}
				//if there is no doctor with thesame specialty as the patient assign to a GP
				if (seen == 0)
					myPat.specCode = "GP";

				//Assigning the patient
				assignPatient(rooms, myPat);

			}
			//Check-out
			else if (secondPrompt == 'O' || secondPrompt == 'o')
			{
				string name;
				int roomNumb;
				cout << "Please enter your name: "; outFile << "Please enter your name: " << endl;
				cin.ignore(256, '\n');
				getline(cin,name);
				cout << "What room were you in?: "; outFile << "What room were ypu in?: " << endl;
				cin >> roomNumb;

				Patient x;
				rooms[roomNumb - 1].pat = x;
				//if there is someone in the queue, make the person the patient, then Dequeue the person
				if (rooms[roomNumb - 1].myQueue.getLength() != 0)
				{
					myPat = rooms[roomNumb - 1].myQueue.firstElement();
					rooms[roomNumb - 1].pat = myPat;
					rooms[roomNumb - 1].myQueue.Dequeue(myPat);
				}
				cout << "Patient " << name << " has successfully checked out." << endl;
				outFile << "Patient " << name << " has successfully checked out." << endl;
			}
		}

		cout << endl;
		outFile << endl;
		cout << "Do you want to continue? (Y/N): "; outFile << "Do you want to continue? (Y/N): " << endl;
		cin >> next;
	}

	cout << "GOODBYE!!!" << endl;
	outFile << "GOODBYE!!!" << endl;
	outFile.close();

	return 0;
}

//finds every room where there is a doctor in a room with thesame specialty as the patient's case
//when it find one, it chekcs if the room is free. if it is, it assigns the patient to it.
//if the room is occupied by a patient, it finds the room with the shortest waitlist;
//shortestLengthIndex; 
//						initialize shortestLengthIndex to the index of the first room with a doctor for the patient's case
//						compares each room to see if their waitlist is shorter than the current one.
//						by the end of the loop, shortestLengthIndex, stores the index of the room with the shortest waitlist.
//						if there is no Doctor with the patient's specialty and no GP, the patient is assigned to room 1.
void assignPatient(Room rooms[], Patient pat)
{
	int shortestLengthIndex = 0;
	//initialize shortestLengthIndex to the index of the first room with a doctor for the patient's case
	for (int i = 0; i < 100; i++)
	{
		if (rooms[i].doc.name != "" && rooms[i].doc.specCode == pat.specCode)
		{
			shortestLengthIndex = i;
			break;
		}
	}

	bool assigned = false;
	int i = 0;
	while(i < 100 && assigned == false)
	{
		if (rooms[i].doc.name != "" && rooms[i].doc.specCode == pat.specCode)
		{
			//if there is no queue
			if (rooms[i].pat.name == "")
			{
				rooms[i].pat = pat;
				cout << "Please proceed to room " << i + 1 << " Doctor " << rooms[i].doc.name << " is ready to see you." << endl;
				outFile << "Please proceed to room " << i + 1 << " Doctor " << rooms[i].doc.name << " is ready to see you." << endl;
				assigned = true;
			}
			//check for the doctor with the shortest waitlist
			else
			{
				if (rooms[i].myQueue.getLength() < rooms[shortestLengthIndex].myQueue.getLength())
					shortestLengthIndex = i;
			}
		}
		i++;
	}

	if (assigned == false)
	{
		rooms[shortestLengthIndex].myQueue.Enqueue(pat);
		if (shortestLengthIndex == 0)
		{
			cout << "I am sorry, there is no doctor available to see you now." << endl;
			cout << "Please proceed to room " << shortestLengthIndex + 1 << "'s waiting room.";
			cout << "A doctor will see you soon" << endl;
			outFile << "I am sorry, there is no doctor available to see you now." << endl;
			outFile << "Please proceed to room " << shortestLengthIndex + 1 << "'s waiting room.";
			outFile << "A doctor will see you soon" << endl;
		}
		else
		{
			cout << "Please proceed to room " << shortestLengthIndex + 1 << "'s waiting room, Doctor ";
			cout << rooms[shortestLengthIndex].doc.name << " will see you soon" << endl;
			outFile << "Please proceed to room " << shortestLengthIndex + 1 << "'s waiting room, Doctor ";
			outFile << rooms[shortestLengthIndex].doc.name << " will see you soon" << endl;
		}
	}	
}