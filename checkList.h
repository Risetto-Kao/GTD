#ifndef CHECKLIST_H
#define CHECKLIST_H
#include <iostream>
#include <string>
#include <vector>
#include "event.h"
using namespace std;

class CheckList
{
private:
    string name;
    vector<Event> eventsNames;

public:
    CheckList();
    CheckList(string name);

    string getName();
    int getEventsCnt();
 

    /// TODO: 14
    void setName(string name);
    void addEvent(Event eventName);
    // void removeEvent(int order);
    // void removeEvent(string eventName);

    void print();
    void printEvents();
};


#endif /* CHECKLIST_H */