#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

/// ---------------------------------------------
/// ------------------ event --------------------
/// ---------------------------------------------

class Event
{
private:
    int id;
    string name;
    string description;
    bool isEventDone;
    time_t deadline;

public:
    Event();
    Event(int id, string name);
    ~Event();
    void setDescription(string description);
    void setDeadline(time_t deadline);
    bool isDone();
};

Event::Event(int id, string name)
{
    this->id = id;
    this->name = name;
    isEventDone = false;
}

Event::~Event()
{
}

void Event::setDescription(string description)
{
    this->description = description;
}

void Event::setDeadline(time_t deadline)
{
    this->deadline = deadline;
}

bool Event::isDone()
{
    return isEventDone;
}

/// ---------------------------------------------
/// ------------------ TodoList -----------------
/// ---------------------------------------------

class TodoList
{
private:
    int id;
    string name;
    vector<Event> events;

public:
    TodoList();
    TodoList(int id, string name);
    ~TodoList();
    bool isAllEventDone();
    double getProgress(); // TODO: return 4 digit behind .
    int getEventsCnt();
    int getDoneEventsCnt();
    bool hasEvents();
};

TodoList::TodoList(int id, string name)
{
    this->id = id;
    this->name = name;
}

TodoList::~TodoList()
{
}

bool TodoList::hasEvents()
{
    return events.size();
}

bool TodoList::isAllEventDone()
{
    // TO BE BETTER:
    // for (Event event: events){
    //     if (!event.isDone()) return false;
    // }
    // return true;
    int eventCnt = TodoList::getEventsCnt();
    int doneEventCnt = TodoList::getDoneEventsCnt();
    return eventCnt == doneEventCnt;
}

int TodoList::getEventsCnt()
{
    return events.size();
}

int TodoList::getDoneEventsCnt()
{
    int cnt = 0;
    for (Event event : events)
    {
        if (event.isDone())
            cnt++;
    }
    return cnt;
}

double TodoList::getProgress()
{
    int eventCnt = TodoList::getEventsCnt();
    int doneEventCnt = TodoList::getDoneEventsCnt();
    return static_cast<double>(doneEventCnt) / eventCnt;
}

/// ---------------------------------------------
/// ------------------ Target -------------------
/// ---------------------------------------------

class Target
{
private:
    int id;
    string name;
    TodoList twoMinList;
    TodoList futureList;
    vector<TodoList> situationLists;

public:
    Target(int id, string name);
    ~Target();
    double getProgress();
    int getEventCnt();
    int getDoneEventCnt();
    int getListCnt();
    int getDoneListCnt();
};

Target::Target(int id, string name)
{
    this->id = id;
    this->name = name;
    this->twoMinList = TodoList();
}

Target::~Target()
{
}

int Target::getEventCnt()
{
    int cnt = twoMinList.getEventsCnt() + futureList.getEventsCnt();
    for (TodoList list : situationLists)
    {
        cnt += list.getEventsCnt();
    }
    return cnt;
}

int Target::getDoneEventCnt()
{
    int cnt = twoMinList.getDoneEventsCnt() + futureList.getDoneEventsCnt();
    for (TodoList list : situationLists)
    {
        cnt += list.getDoneEventsCnt();
    }
    return cnt;
}

double Target::getProgress()
{
    int eventCnt = Target::getEventCnt();
    int doneEventCnt = Target::getDoneEventCnt();
    return static_cast<double>(doneEventCnt) / eventCnt;
}

int Target::getListCnt()
{
    int cnt = 0;
    if (twoMinList.hasEvents())
        cnt++;
    if (futureList.hasEvents())
        cnt++;
    return cnt + situationLists.size();
}

int Target::getDoneListCnt()
{
    int cnt = 0;
    if (twoMinList.isAllEventDone())
        cnt++;
    if (futureList.isAllEventDone())
        cnt++;
    for (TodoList list : situationLists)
    {
        if (list.isAllEventDone())
            cnt++;
    }
    return cnt;
}

void printList(vector<string> list)
{
    for (string s : list)
    {
        cout << s << endl;
    }
}

bool isNew()
{
    while (true)
    {
        cout << "new target or existed target? ( new / exist )\n";
        string tmp;
        cin >> tmp;
        if (tmp == "new")
        {
            return true;
        }
        else if (tmp == "exist")
        {
            return false;
        }
        else
        {
            cout << "invalid input !!!\n";
            cout << "please input again.\n";
            continue;
        }
    }
}

string getTargetName()
{
    cout << "\ntarget name is: ";
    string target;
    getline(cin, target);
}

int main()
{

    // TODO: good intro
    cout << "introduction\n";
    // cout << "what mode (naive, general)";
    bool isTargetNew = isNew();

    string targetName = getTargetName();

    if (!isTargetNew)
    {
        // readFile(name)
    }
    else
    {
        // init
    }

    /// 捕捉想法
    // TODO: can add time
    cout << "\nThink about what you need to do to this target. If you finish your todos, enter 'end'\n";

    string eventName;
    vector<string> allEvents;
    vector<string> shortTimeEvents;
    vector<string> futureEvents;
    vector<string> conditionEvents;
    vector<string> actionEvents;
    // cin >> eventName;
    do
    {
        getline(cin, eventName);

        if (eventName != "end")
            allEvents.push_back(eventName);
    } while (eventName != "end");

    /// 獲得將來也許清單
    cout << "\n Consider if the thing must be done or not\n";
    for (string s : allEvents)
    {
        cout << s << endl;
        bool needAction = false;
        cin >> needAction;
        cout << endl;
        if (needAction)
        {
            // push an event into ActionList
            actionEvents.push_back(s);
        }
        else
        {
            // push an event into FutureList
            futureEvents.push_back(s);
        }
    }

    /// 2 min list
    cout << "\n Consider if the thing can be done at 2 minutes\n";
    for (string s : actionEvents)
    {
        cout << s << endl;
        bool doneQuick = false;
        cin >> doneQuick;
        if (doneQuick)
        {
            shortTimeEvents.push_back(s);
        }
        else
        {
            conditionEvents.push_back(s);
        }
    }

    /// show result
    cout << "\n2 min List \n";
    printList(shortTimeEvents);
    cout << "\nFuture List \n";
    printList(futureEvents);
    cout << "\nCondition List\n";
    printList(conditionEvents);

    return 0;
}