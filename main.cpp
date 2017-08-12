//MAIN FILE

#include <iostream>
#include <list>
#include "Person.h"
#include "Shift.h"
#include "Schedule.h"

using namespace std;

bool compFirst(Person* a, Person* b)
{
	return a->getPriority() < b->getPriority();
}
int convertToTimeslot(int time, char loc)
{
	if (time == 12 && loc == 'a')
		return 0;
	if (time == 6 && loc == 'a')
		return 1;
	if (time == 9 && loc == 'a')
		return 2;
	if (time == 12 && loc == 'p')
		return 3;
	if (time == 3 && loc == 'p')
		return 4;
	if (time == 6 && loc == 'p')
		return 5;
	if (time == 9 && loc == 'p')
		return 6;
}
bool formsLongShift(Person* p, Shift* s, Schedule& schedule)
{
	int day = s->getDay();
	int timeslot = convertToTimeslot(s->getStart(), s->getStartC());

	int timeslotNext3 = timeslot + 1;
	int timeslotNext6 = timeslot + 2;
	int timeslotPrev3 = timeslot- 1;
	int timeslotPrev6 = timeslot - 2;

	int dayNext3 = day, dayNext6 = day, dayPrev3 = day, dayPrev6 = day;

	//Calculate the indices in the schedule for each day (up to 2 prev and 2 next)
	if (timeslotNext3 > 6)
	{
		timeslotNext3 = timeslotNext3 % 7;
		dayNext3++;
		if (dayNext3 > 6)
			dayNext3 = -1;
	}
	if (timeslotNext6 > 6)
	{
		timeslotNext6 = timeslotNext6 % 7;
		dayNext6++;
		if (dayNext6 > 6)
			dayNext6 = -1;
	}
	if (timeslotPrev3 < 0)
	{
		timeslotPrev3 = 6;
		dayPrev3--;
		if (dayPrev3 < 0)
			dayPrev3 = -1;
	}
	if (timeslotPrev6 < 0)
	{
		timeslotPrev6 = 7 + timeslotPrev6;
		dayPrev6--;
		if (dayPrev6 < 0)
			dayPrev6 = -1;
	}

	//Get Shifters for each day (if the day is available on the current schedule)
	Shifters prev6 = schedule.getShiftersForTimeslot(dayPrev6, timeslotPrev6);
	Shifters prev3 = schedule.getShiftersForTimeslot(dayPrev3, timeslotPrev3);
	Shifters next3 = schedule.getShiftersForTimeslot(dayNext3, timeslotNext3);
	Shifters next6 = schedule.getShiftersForTimeslot(dayNext6, timeslotNext6);

	if(p->getGraveyard() != nullptr)
		if (s->getDay() == p->getGraveyard()->getDay() && s->getStart() == 6 && s->getStartC() == 'a')
			return true;

	//Check if we form a long-ass shift
	if ((prev6.desker1 == p || prev6.desker2 == p) && (prev3.desker1 == p || prev3.desker2 == p))
		return true;
	if ((prev3.desker1 == p || prev3.desker2 == p) && (next3.desker1 == p || next3.desker2 == p))
		return true;
	if ((next3.desker1 == p || next3.desker2 == p) && (next6.desker1 == p || next6.desker2 == p))
		return true;
	
	return false;
}
bool outsideProximity(Person* p, Shift* s, Schedule& schedule)
{
	int day = s->getDay();
	int timeslot = convertToTimeslot(s->getStart(), s->getStartC());

	int dayPrev3 = s->getDay(), dayPrev6 = s->getDay(), dayPrev9 = s->getDay(), dayPrev12 = s->getDay(), dayPrev15 = s->getDay();
	int timePrev3 = timeslot - 1, timePrev6 = timeslot - 2, timePrev9 = timeslot - 3, timePrev12 = timeslot - 4, timePrev15 = timeslot - 5;

	//Find all positions in the schedule for the previous 5 working shifts
	if (timePrev3 < 0)
	{
		timePrev3 = 6;
		dayPrev3--;
		if (dayPrev3 < 0)
			dayPrev3 = -1;
	}
	if (timePrev6 < 0)
	{
		timePrev6 = 7 + timePrev6;
		dayPrev6--;
		if (dayPrev6 < 0)
			dayPrev6 = -1;
	}
	if (timePrev9 < 0)
	{
		timePrev9 = 7 + timePrev9;
		dayPrev9--;
		if (dayPrev9 < 0)
			dayPrev9 = -1;
	}
	if (timePrev12 < 0)
	{
		timePrev12 = 7 + timePrev12;
		dayPrev12--;
		if (dayPrev12 < 0)
			dayPrev12 = -1;
	}
	if (timePrev15 < 0)
	{
		timePrev15 = 7 + timePrev15;
		dayPrev15--;
		if (dayPrev15 < 0)
			dayPrev15 = -1;
	}
	//Get Shifters for each timeslot (if available)
	Shifters prev3 = schedule.getShiftersForTimeslot(dayPrev3, timePrev3);
	Shifters prev6 = schedule.getShiftersForTimeslot(dayPrev6, timePrev6);
	Shifters prev9 = schedule.getShiftersForTimeslot(dayPrev9, timePrev9);
	Shifters prev12 = schedule.getShiftersForTimeslot(dayPrev12, timePrev12);
	Shifters prev15 = schedule.getShiftersForTimeslot(dayPrev15, timePrev15);


	//Check if theres a 6 hour shift within a 3 block time
	if (dayPrev3 != -1 && dayPrev6 != -1 && (prev3.desker1 == p || prev3.desker2 == p) && (prev6.desker1 == p || prev6.desker2 == p))
		return false;
	if (dayPrev6 != -1 && dayPrev9 != -1 && (prev6.desker1 == p || prev6.desker2 == p) && (prev9.desker1 == p || prev9.desker2 == p))
		return false;
	if (dayPrev9 != -1 && dayPrev12 != -1 && (prev9.desker1 == p || prev9.desker2 == p) && (prev12.desker1 == p || prev12.desker2 == p))
		return false;
	if (dayPrev12 != -1 && dayPrev15 != -1 && (prev12.desker1 == p || prev12.desker2 == p) && (prev15.desker1 == p || prev15.desker2 == p))
		return true;
	return true;
}
int main()
{
	Schedule schedule;
	int minHours = -1;
	int maxHours = -1;
	int personPriority = -1;
	int reqHours = -1;
	int numDeskers = -1;
	int day = -1;


	list<Person*> deskers;

	bool done = false;

	cout << "Minimum Hours Per Week: ";
	cin >> minHours;
	cout << "Maximum Hours Per Week: ";
	cin >> maxHours;
	cout << "Number of Deskers: ";
	cin >> numDeskers;
	while (!done)
	{
		bool allShifts = false;

		cout << "Enter Person's Priority and Requested Hours: ";
		cin >> personPriority;
		cin >> reqHours;
		cout << endl;

		Person* p = new Person(personPriority, reqHours);
		while (!allShifts)
		{
			int time = -1;
			int shiftPriority = -1;
			char ampm = 'z';

			cout << "Enter Shift Info ([day time a/p rank], for example 0 12 p 1): ";
			cin >> day;
			cin >> time;
			cin >> ampm;
			cin >> shiftPriority;

			char optional = ampm;
			int end = -1;
			if ((time + 3) >= 12 && time != 12)
			{
				if (ampm == 'a')
					optional = 'p';
				else
					optional = 'a';
			}
			if ((time + 3) > 12)
				end = (time + 3) % 12;
			else
				end = time + 3;
			Shift* s = new Shift(p, time, end, ampm, optional, day, shiftPriority);
			p->addShift(s, 0);

			bool flag = false;
			while (!flag)
			{
				cout << "Was that final shift? (y/n): ";
				char tester;
				cin >> tester;
				if (tester == 'y' || tester == 'Y')
				{
					flag = true;
					allShifts = true;
				}
				if (tester == 'n' || tester == 'N')
					flag = true;
			}
		}
		bool personflag = false;

		while (!personflag)
		{
			cout << "Was that the last person? (y/n): ";
			char donetest;
			cin >> donetest;
			if (donetest == 'y' || donetest == 'Y')
			{
				done = true;
				personflag = true;
			}
			if (donetest == 'n' || donetest == 'N')
				personflag = true;
		}
		deskers.push_back(p);
	}
	//Sort
	deskers.sort(compFirst);

	//Begin assignment
	int furthestDesker = numDeskers - 14;
	bool assignedGraveyards = false;
	int graveyardAssigns = 0;
	//Assign Graveyards
	for (list<Person*>::iterator i = deskers.begin(); i != deskers.end(); i++)
	{
		//Assign Graveyards first
		if ((*i)->getPriority() > furthestDesker && !assignedGraveyards)
		{
			Person* p = (*i);
			graveyardAssigns++;
			bool hasAssigned = false;
			while (!hasAssigned)
			{
				list<Shift*> shifts = p->getReqShifts();
				list<Shift*>::iterator iterator = shifts.begin();
				int priority = 1;
				while (iterator != shifts.end())
				{
					if ((*iterator)->getStart() == 12 && (*iterator)->getStartC() == 'a' && (*iterator)->getPriority() == priority)
					{
						if (schedule.addToSchedule((*iterator)->getDay(), 0, p))
						{
							hasAssigned = true;
							p->incrementCurrentHours(6);
							p->addShift((*iterator), 1);
							p->setGraveyard((*iterator));
							iterator = shifts.erase(iterator);
							break;
						}
						else
						{
							priority++;
							break;
						}
					}
					else
						iterator++;
				}
				//FOR WHEN NOT EVERYONE SHOWS UP FOR THE WEEK OR TURNS IN THEIR SCHEDULE
				if (iterator == shifts.end() && !hasAssigned)
					hasAssigned = true;
			}
		}
	}

	//Assign the rest of the schedule
	int loopcount = 0;
	while (loopcount < 10 && !schedule.complete())
	{
		for (list<Person*>::iterator i = deskers.begin(); i != deskers.end(); i++)
		{
			Person* p = (*i);
			list<Shift*> reqShifts = p->getReqShifts();
			//Check if person over hour request
			if (p->getCurrentHours() + 3 > p->getRequestedHours())
			{
				continue;
			}
			else
			{
				for(int count = 0; count < 2; )
				{
					bool placed = false;
					int height = 1;
					while (!placed)
					{
						for (list<Shift*>::iterator it = reqShifts.begin(); it != reqShifts.end(); it++)
						{
							Shift* s = (*it);
							if (s->getPriority() == height && !(s->getStart() == 12 && s->getStartC() == 'a'))
							{
								int timeindex = convertToTimeslot(s->getStart(), s->getStartC());
								//Check if we can actually accept this shift (doesn't break any of the rules)
								if(!formsLongShift(p, s, schedule) && outsideProximity(p, s, schedule))
								{
									if (schedule.addToSchedule(s->getDay(), timeindex, p))
									{
										p->incrementCurrentHours(3);
										p->addShift(s, 1);
										placed = true;
										it = reqShifts.erase(it);
										break;
									}
								}
							}
						}
						if (!placed)
						{
							height++;
							if (height == 50)
							{
								break;
							}
						}
					}
					count++;
				}
			}
		}
		loopcount++;
	}
	if (!schedule.complete())
	{
		deskers.reverse();
		//Try to fill in the rest of the schedule (copied from above)
		int loopcount = 0;
		while (loopcount < 10 && !schedule.complete())
		{
			for (list<Person*>::iterator i = deskers.begin(); i != deskers.end(); i++)
			{
				Person* p = (*i);
				list<Shift*> reqShifts = p->getReqShifts();
				//Check if person over hour request
				if (p->getCurrentHours() + 3 > p->getRequestedHours())
				{
					continue;
				}
				else
				{
					bool placed = false;
					int height = 1;
					while (!placed)
					{
						for (list<Shift*>::iterator it = reqShifts.begin(); it != reqShifts.end(); it++)
						{
							Shift* s = (*it);
							if (s->getPriority() == height && (s->getStart() != 12 || s->getStartC() != 'a'))
							{
								int timeindex = convertToTimeslot(s->getStart(), s->getStartC());
								if (!formsLongShift(p, s, schedule) && outsideProximity(p, s, schedule))
								{
									if (schedule.addToSchedule(s->getDay(), timeindex, p))
									{
										p->incrementCurrentHours(3);
										p->addShift(s, 1);
										placed = true;
										it = reqShifts.erase(it);
										break;
									}
								}
							}
						}
						if (!placed)
						{
							height++;
							if (height == 50)
							{
								break;
							}
						}
					}
				}
			}
			loopcount++;
		}
		schedule.printSchedule();
		cout << endl;
		deskers.reverse();
		for (list<Person*>::iterator i = deskers.begin(); i != deskers.end(); i++)
		{
			cout << (*i)->getPriority() << " requested " << (*i)->getRequestedHours() << " and received " << (*i)->getCurrentHours() << " hours. ";
			if ((*i)->getCurrentHours() < minHours)
				cout << (*i)->getPriority() << " DOES NOT HAVE MINIMUM HOURS OF " << minHours << " HOURS!" << endl;
			else
				cout << endl;
		}
	}
	for (list<Person*>::iterator iterate = deskers.begin(); iterate != deskers.end(); iterate++)
	{
		delete (*iterate);
	}
}



