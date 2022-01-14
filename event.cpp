
#include <iostream>
#include <string>
#include <ctime>
#include "event.h"
#include "defaultValue.h"
using namespace std;

Event::Event()
{
    name = DEFAULT_EVENT_NAME;
    description = DEFAULT_EVENT_DESCRIPTION;
    done = false;
    DateTime dateTime;
    deadline = dateTime;
    point = DEFAULT_EVENT_POINT;
    targetName = DEFAULT_TARGET_NAME;
    checkListName = DEFAULT_CHECKLIST_NAME;
}

Event::Event(string name)
{
    this->name = name;
    this->description = DEFAULT_EVENT_DESCRIPTION;
    done = DEFAULT_EVENT_DONE;
    DateTime dateTime;
    deadline = dateTime;
    point = DEFAULT_EVENT_POINT;
    targetName = DEFAULT_TARGET_NAME;
    checkListName = DEFAULT_CHECKLIST_NAME;
}

/// getter -----------------------------------------------

string Event::getName()
{
    return name;
}

string Event::getTargetName()
{
    return targetName;
}
string Event::getDescription()
{
    return description;
}

bool Event::isDone()
{
    return done;
}

string Event::getDeadlineStr(bool needTime)
{
    return deadline.getDateTime();
}

DateTime Event::getDeadline(){
    return deadline;
}

int Event::getPoint()
{
    return point;
}

string Event::getCheckListName()
{
    return checkListName;
}

/// setter -------------------------------------------------
void Event::setName(string newName)
{
    this->name = newName;
}

void Event::setDescription(string description)
{
    this->description = description;
}

void Event::setDone(bool done)
{
    this->done = done;
}

void Event::setDeadline(DateTime deadline)
{
    this->deadline = deadline;
}

void Event::setPoint(int point)
{
    this->point = point;
}

void Event::setCheckListName(string checkListName)
{
    this->checkListName = checkListName;
}

void Event::setTargetName(string targetName)
{
    this->targetName = targetName;
}

void Event::print()
{
    cout << "-------  Event -------\n";
    cout << "name          : " << name << endl;
    cout << "description   : " << description << endl;
    cout << "done status   : " << (isDone() ? "[ ]" : "[v]") << endl;
    cout << "deadline      : " << getDeadlineStr(true) << endl;
    cout << "checkList name: " << checkListName << endl;
    cout << "target name   : " << targetName << endl;
    cout << "----------------------\n";
}

void Event::printInLine(bool isInList)
{
    if (isInList)
    {
        if (isDone())
        {
            cout << "[V] " << name << " / 點數: " << point;
            if (!(deadline.getDateTime() == "2022/01/01-00:00"))
            {
                cout << " / 死線: " << deadline.getDateTime();
            }
            cout << endl;
        }
        else
        {
            cout << "[ ] " << name << " / 點數: " << point;
            if (!(deadline.getDateTime() == "2022/01/01-00:00"))
            {
                cout << " / 死線: " << deadline.getDateTime();
            }
            cout << endl;
        }
    }
    else
    {
        if (isDone()) // TODO: deadline
        {
            cout << "[V] " << name
                 << " / " << description << endl;
        }

        else
        {
            cout << "[ ] " << name
                 << " / " << description << endl;
        }
    }
}

void Event::setDeadline(string deadlineString)
{

    int year = stoi(deadlineString.substr(0, 4));
    int month = stoi(deadlineString.substr(5, 6));
    int day = stoi(deadlineString.substr(8, 9));
    int hour = stoi(deadlineString.substr(11, 12));
    int minute = stoi(deadlineString.substr(14, 15));
    deadline = DateTime(year, month, day, hour, minute);
}