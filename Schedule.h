#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Person.h"

struct Shifters
{
	Person* desker1 = nullptr;
	Person* desker2 = nullptr;
};

class Schedule
{
public:
	Schedule();
	bool complete();
	bool addToSchedule(int day, int hourslot, Person* p);
	bool removeShifterFromSchedule(int day, int hourslot, Person* p);
	Shifters getShiftersForTimeslot(int day, int hourslot);
	void printSchedule();
private:
	Shifters mScheduleTable[7][7];

};

#endif