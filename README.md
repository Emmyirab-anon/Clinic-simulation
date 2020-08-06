# Clinic-simulation

The basic functions that the clinic has in mind are doctor check-in and check-out and patient check-in and checkout.
A doctor checks in by telling the scheduler his or her name, an examination room number,
and a medical specialty code. Each doctor has a favorite room. The scheduler checks to
see whether the room is free. If so, it assigns this doctor to the room; if not, it rejects therequest with a message, and the doctor can try again to check in. When a doctor checksout, the examination room is freed.

A patient checking in gives a name, age, specialist code, and emergency indication. Thescheduler tries to match up the patient with a doctor according to a set of rules that are
described here. If there is a match, the patient is seen by the assigned doctor. If this
doctor is currently seeing a patient, the new patient is queued to see the doctor. If it is the
emergency case, the patient should be moved to the front of the waiting list.

The rules for assigning doctors to patients are as follows:
l. Any patient under age 16 is assigned to see a pediatrician.
2. Patients age 16 and older are assigned a doctor according to the specialty requested. If
there is no doctor in the clinic with the requested specialty, the patient is assigned to a
general practitioner (GP). If there is no GP, the patient can be assigned to any doctor.
3. If there is more than one doctor of the requested specialty, the patient is assigned to the
doctor with the shortest waiting list.
When a patient checks out, the doctor he or she was assigned to is available to see the
next patient if there is anyone in the waiting list.

Input
Because this is an interactive system, the program prompts the users to input the
correct information. The initial prompt is
Type D for Doctor or P for Patient:
The next prompt is
Type I for check-in or O for checkout:

Message telling patient which room to go to and which doctor has been assigned. If no
doctor is available, show apologetic message.
Good-bye message. At a later time we may add billing information at this point.
In addition to printing the messages on the screen, you should also write the requests and
messages to a transaction file (trans.out), to be turned in with your program listing.

<Details and Assumptions
1. There are l 00 examination rooms at the clinic, each with a waiting room attached.
2. Specialty codes are as follows:
Pediatrics PED
General practice GEN (or GP)
Internal medicine INT
Cardiology CAR
Surgeon SUR
Obstetrics OBS
Psychiatry PSY
Neurology NEU
Orthopedics ORT
Dermatology DET
Ophthalmology OPT
Ear, Nose, and Throat ENT
3. You may assume that no patient leaves without checking out. (That is, every doctor
becomes free eventually.)
4. No one leaves before he or she sees the assigned doctor. (That is, no one has to be
taken out of the waiting queue.) The clinic is open 24 hours a day, 7 days a week.
5. If a doctor checks out while there is still a waiting list of patients assigned to him or
her, the patients must be reassigned to other doctors.

Data Structures
The basic data structure is a list of examination rooms with waiting lists attached to each.
Because the number of rooms is fixed, you may use an array of records to represent it. It
is the waiting list attached to each examination room that is of interest to us. We have
seen that patients are seen in the order in which they are added to the list (a simple queue)
