//SHIFT CLASS FILE
#include "Shift.h"

Shift::Shift(Person* assigned, int starttime, int endttime, char startc, char endc, int day, int priority)
{
	mDay = day;
	mShiftPriority = priority;
	mAssignedPerson = assigned;
	mStart = starttime;
	mEnd = endttime;
	mStartC = startc;
	mEndC = endc;
}
int Shift::getDay()
{
	return mDay;
}
int Shift::getStart()
{
	return mStart;
}
char Shift::getStartC()
{
	return mStartC;
}
char Shift::getEndC()
{
	return mEndC;
}
int Shift::getEnd()
{
	return mEnd;
}
int Shift::getPriority()
{
	return mShiftPriority;
}
void Shift::setPriority(int s)
{
	mShiftPriority = s;
}
