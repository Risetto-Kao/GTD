
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "checkList.h"
#include "defaultValue.h"
using namespace std;

CheckList::CheckList()
{
    name = DEFAULT_CHECKLIST_NAME;
}

CheckList::CheckList(string name)
{
    this->name = name;
}

string CheckList::getName()
{
    return name;
}

int CheckList::getEventsCnt()
{
    return eventsNames.size();
}

void CheckList::addEvent(Event eventName)
{
    eventsNames.push_back(eventName);
}

// void CheckList::removeEvent(int order)
// {
//     int index = order - 1;
//     eventsNames.erase(eventsNames.begin() + index);
// }

// void CheckList::removeEvent(string eventName)
// {
//     for (int i = eventsNames.size() - 1; i >= 0; i--)
//     {
//         if (eventsNames[i].getName() == eventName)
//         {
//             eventsNames.erase(eventsNames.begin() + i);
//             return;
//         }
//     }
// }

void CheckList::setName(string name)
{
    this->name = name;
}

void CheckList::print()
{
    cout << "-------  CheckList -------\n";
    cout << "name :  " << name << endl;
    cout << "events: \n";
    for (auto &eventName : eventsNames)
        cout << "-- " << eventName.getName() << endl;
    cout << "-------------------------\n";
}

void CheckList::printEvents()
{
    int length = name.length();
    int size = eventsNames.size();

    string horizantal(length + 6, '-');
    string verticalSpace(length + 4, ' ');
    string vertical = "|" + verticalSpace + "|";
    string nameLine = "|  " + name + "  |";
    ;
    
    string spaces(6, ' ');

    if (size == 1){
        cout << horizantal << endl;

        cout << nameLine;
        cout << "  " << 1 << ". ";
        eventsNames[0].printInLine(true);

        cout << horizantal << endl;
        return;
    } else if (size == 2){
        cout << horizantal << endl;

        cout << nameLine;
        cout << "  " << 1 << ". ";
        eventsNames[0].printInLine(true);

        cout << vertical;
        cout << "  " << 2 << ". ";
        eventsNames[1].printInLine(true);

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
        eventsNames[i].printInLine(true);
    }
}
