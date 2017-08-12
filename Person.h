#ifndef PERSON_H
#define PERSON_H

//PERSON CLASS HEADER
#include <list>
#include "Shift.h"

using namespace std;

class Person
{
public:
	Person(int priority, int reqhours);
	~Person();
	const int getPriority();
	int getCurrentHours();
	int getRequestedHours();
	void incrementCurrentHours(int increment);
	void addShift(Shift* s, int list);
	Shift* getGraveyard();
	void setGraveyard(Shift* s);
	list<Shift*> getReqShifts();
	list<Shift*> getAssignedShifts();
private:
	int mPriority;
	int mCurrentHours = 0;
	int mRequestedHours;
	list<Shift*> mReqShifts;
	list<Shift*> mAssignedShifts;
	Shift* mGraveyard = nullptr;
};
#endif