#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Event
{
private:
    string name;
    string description;
    bool isDone;
public:
    Event(string name);
    ~Event();
    void setDescription(string descriptuion);
    string getName();
    // void setDone(bool isDone);
};

Event::Event(string name)
{
    this->name = name;
}

Event::~Event()
{
}

void Event::setDescription(string descriptuion){
    this->description = description;
}

string Event::getName(){
    return this->name;
}

void printList(vector<string> list){
    for (string s:list){
        cout << s << endl;
    }
}


int main()
{
    // TODO: good intro
    cout << "introduction\n";
    // cout << "what mode (naive, general)";

    // //TODO: enum
    // int mode = 0; // 0: naive / 1: general
    // cin >> mode;

    cout << "new target or existed target?\n";
    bool isNew = true;
    cin >> isNew;

    cout << "\ntarget name is: ";

    string target = "";
    cin >> target;

    if (!isNew)
    {
        // readFile(name)
        // show the statement
    }
    else
    {
        //
        // init
    }

    /// 捕捉想法
    // TODO: can add time
    cout << "\nThink about what you need to do to this target. If you finish your todos, enter 'end'\n";

    string eventName = " ";
    vector<string> allEvents;
    vector<string> shortTimeEvents;
    vector<string> futureEvents;
    vector<string> conditionEvents;
    vector<string> actionEvents;
        // cin >> eventName;
    do
    {
        cin >> eventName;
        
        if (eventName != "end") allEvents.push_back(eventName);
    } while (eventName != "end");   


    /// 獲得將來也許清單
    cout << "\n Consider if the thing must be done or not\n";
    for (string s : allEvents){
        cout << s << endl;  
        bool needAction = false;
        cin >> needAction;
        cout << endl;
        if (needAction){
            // push an event into ActionList
            actionEvents.push_back(s);
        } else {
            // push an event into FutureList
            futureEvents.push_back(s);
        }
    }

    /// 2 min list
    cout << "\n Consider if the thing can be done at 2 minutes\n";
    for (string s: actionEvents){
        cout << s << endl;
        bool doneQuick = false;
        cin >> doneQuick;
        if (doneQuick){
            shortTimeEvents.push_back(s);
        }
        else {
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