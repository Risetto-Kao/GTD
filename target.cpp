#include <iostream>
#include <vector>
#include "target.h"
#include "defaultValue.h"
using namespace std;

Target::Target()
{
    name = DEFAULT_TARGET_NAME;
}

Target::Target(string name)
{
    this->name = name;
}

string Target::getName()
{
    return name;
}

int Target::getEventsCnt()
{
    return eventsNames.size();
}

void Target::setName(string name)
{
    this->name = name;
}

void Target::addEvent(Event name)
{
    eventsNames.push_back(name);
}

void Target::print()
{
    cout << "-------  Target -------\n";
    cout << "name            : " << name << endl;
    cout << "events names    : " << endl;
    for (auto &eventName : eventsNames)
    {
        cout << " * ";
        eventName.print();
    }
    cout << "-----------------------\n";
}

void Target::printEvents()
{
    int length = name.length();
    int size = eventsNames.size();

    string horizantal(length + 6, '-');
    string verticalSpace(length + 4, ' ');
    string vertical = "|" + verticalSpace + "|";
    string nameLine = "|  " + name + "  |";
    

    string spaces(6, ' ');

    if (size == 1)
    {
        cout << horizantal << endl;

        cout << nameLine;
        cout << "  " << 1 << ". ";
        eventsNames[0].printInLine(false);

        cout << horizantal << endl;
        return;
    }
    else if (size == 2)
    {
        cout << horizantal << endl;

        cout << nameLine;
        cout << "  " << 1 << ". ";
        eventsNames[0].printInLine(false);

        cout << vertical;
        cout << "  " << 2 << ". ";
        eventsNames[1].printInLine(false);

        cout << horizantal << endl;
        return;
    }

    for (int i = 0; i < size; i++)
    {

        if (i == 0)
            cout << horizantal;
        else if (i == size - 1)
            cout << horizantal;
        else if (i == (size / 2))
            cout << nameLine;
        else
            cout << vertical;

        cout << "  " << i + 1 << ". ";
        eventsNames[i].printInLine(false);
    }
}
