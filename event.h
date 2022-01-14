#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <ctime>
#include "date_time.h"

using namespace std;
class Event
{
private:
    string name;
    string description;
    bool done;
    // bool hasDeadline;
    DateTime deadline;
    int point;
    string checkListName;
    string targetName;

public:
    Event();
    Event(string name);
    /// getter
    static int getObjectCnt();
    string getName();
    string getDescription();
    bool isDone();
    string getDeadlineStr(bool needTime);
    DateTime getDeadline();
    int getPoint();
    string getCheckListName();
    string getTargetName();
    // string saveStructure();

    /// setter
    void setName(string newName);
    void setDescription(string description);
    void setDone(bool done);
    void setDeadline(DateTime deadline);
    void setDeadline(string deadlineString);
    void setPoint(int point);
    void setCheckListName(string checkListName);
    void setTargetName(string targetName);


    void print();
    void printInLine(bool isInList);
};



#endif /* EVENT_H */