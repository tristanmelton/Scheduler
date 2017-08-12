#ifndef SHIFT_H
#define SHIFT_H

//SHIFT CLASS HEADER

class Person;

class Shift
{
public:
	Shift(Person* assigned = nullptr, int starttime = 0, int endtime = 0, char startc = 'z', char endc = 'z', int day = -1,  int priority = -1);
	int getStart();
	int getEnd();
	int getPriority();
	int getDay();
	void setPriority(int pri);
	char getStartC();
	char getEndC();
private:
	Person* mAssignedPerson;
	int mStart;
	int mEnd;
	int mDay;
	int mShiftPriority;
	char mStartC;
	char mEndC;
};

#endif
