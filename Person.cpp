//PERSON CLASS FILE

#include "Person.h"

Person::Person(int priority, int reqHours)
{
	mPriority = priority;
	mRequestedHours = reqHours;
}
const int Person::getPriority()
{
	return mPriority;
}
int Person::getCurrentHours()
{
	return mCurrentHours;
}
int Person::getRequestedHours()
{
	return mRequestedHours;
}
Shift* Person::getGraveyard()
{
	return mGraveyard;
}
void Person::setGraveyard(Shift* s)
{
	mGraveyard = s;
}
void Person::addShift(Shift* s, int list)
{
	if (list == 0)
	{
		mReqShifts.push_back(s);
	}
	else
	{
		mAssignedShifts.push_back(s);
	}
}
void Person::incrementCurrentHours(int increment)
{
	mCurrentHours += increment;
}
list<Shift*> Person::getReqShifts()
{
	return mReqShifts;
}
list<Shift*> Person::getAssignedShifts()
{
	return mAssignedShifts;
}
Person::~Person()
{
	for (list<Shift*>::iterator i = mReqShifts.begin(); i != mReqShifts.end(); i++)
	{
		delete (*i);
	}
	/*for (list<Shift*>::iterator it = mAssignedShifts.begin(); it != mAssignedShifts.end(); it++)
	{
		delete (*it);
	}*/
}