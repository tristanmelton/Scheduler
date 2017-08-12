#include "Schedule.h"
#include <iostream>

using namespace std;

Schedule::Schedule()
{
}

bool Schedule::addToSchedule(int day, int hourslot, Person* p)
{
	if (mScheduleTable[day][hourslot].desker1 == nullptr && mScheduleTable[day][hourslot].desker2 != p)
	{
		mScheduleTable[day][hourslot].desker1 = p;
		return true;
	}
	else if (mScheduleTable[day][hourslot].desker2 == nullptr && mScheduleTable[day][hourslot].desker1 != p)
	{
		mScheduleTable[day][hourslot].desker2 = p;
		return true;
	}
	return false;
}

bool Schedule::removeShifterFromSchedule(int day, int hourslot, Person* p)
{
	if (mScheduleTable[day][hourslot].desker1 == p)
	{
		mScheduleTable[day][hourslot].desker1 = nullptr;
		return true;
	}
	else if (mScheduleTable[day][hourslot].desker2 == p)
	{
		mScheduleTable[day][hourslot].desker2 = nullptr;
		return true;
	}
	return false;
}

Shifters Schedule::getShiftersForTimeslot(int day, int timeslot)
{
	if (day < 0 || timeslot < 0 || day > 6 || timeslot > 6)
	{
		Shifters s;
		s.desker1 = nullptr;
		s.desker2 = nullptr;
		return s;
	}
	return mScheduleTable[day][timeslot];
}

bool Schedule::complete()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mScheduleTable[i][j].desker1 == nullptr || mScheduleTable[i][j].desker2 == nullptr)
				return false;
		}
	}
	return true;
}
void Schedule::printSchedule()
{
	for (int i = 0; i < 5; i++)
		cout << endl;
	cout << "     Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
	cout << "12a ";

	int desker1 = 0;
	int desker2 = 0;

	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][0].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][0].desker1->getPriority();
		if (mScheduleTable[i][0].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][0].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
	cout << endl;
	cout << "6a  ";
	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][1].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][1].desker1->getPriority();
		if (mScheduleTable[i][1].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][1].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
	cout << endl;
	cout << "9a  ";
	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][2].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][2].desker1->getPriority();
		if (mScheduleTable[i][2].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][2].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
	cout << endl;
	cout << "12p ";
	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][3].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][3].desker1->getPriority();
		if (mScheduleTable[i][3].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][3].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
	cout << endl;
	cout << "3p  ";
	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][4].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][4].desker1->getPriority();
		if (mScheduleTable[i][4].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][4].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
	cout << endl;
	cout << "6p  ";
	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][5].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][5].desker1->getPriority();
		if (mScheduleTable[i][5].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][5].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
	cout << endl;
	cout << "9p  ";
	for (int i = 0; i < 7; i++)
	{
		if (mScheduleTable[i][6].desker1 == nullptr)
			desker1 = 0;
		else
			desker1 = mScheduleTable[i][6].desker1->getPriority();
		if (mScheduleTable[i][6].desker2 == nullptr)
			desker2 = 0;
		else
			desker2 = mScheduleTable[i][6].desker2->getPriority();


		cout << desker1 << "," << desker2 << " ";
	}
}