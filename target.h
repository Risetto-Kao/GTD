#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <vector>
#include "event.h"
using namespace std;

class Target
{
private:
    string name;
    vector<Event> eventsNames;

public:
    Target();
    Target(string eventName);

    string getName();
    int getEventsCnt();

    void setName(string name);
    void addEvent(Event name);

    // TODO: 14
    // void removeEvent(int index);
    // void removeEvent(string name);

    void print();
    void printEvents();
};

#endif /* TARGET_H */