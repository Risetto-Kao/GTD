#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <vector>
#include "event.h"
#include "target.h"
#include "checkList.h"
#include "reward.h"
using namespace std;

class Process
{
private:
    // TODO: 6
    // bool isSaved;
    int currentPoint;
    vector<Event> allEvents;
    vector<Target> allTargets;
    vector<CheckList> allCheckLists;
    vector<Reward> allRewards;

    void printFile(string path);
    bool isCheckListExist(string checkListName);// TODO: 13
    bool isTargetExist(string targetName); // TODO: 13 check targetName;
    bool isEventExist(string eventName); 
    bool isRewardExist(string rewardName); // TODO: 15 <T>
    // TODO: 9
    void printExistTarget();
    void printExistCheckList();
    void addEvents(Target &target);
    void modifyEventsInfo(string targetName);
    void classifyEvents(Target &target);
    void classifyEvent(Event &event);
    void classifySituation(Event &event, int cnt);

    void init();
    void initAllTargets();
    void initAllCheckLists();
    // void resetTargets();

    void addReward(int point, string name);
    void addEvent();
    void modifyEventInfo(Event &event);

    string introWithFrame(string fileName, int type);
    string oneLine(string context, int type);
    DateTime askDateTime();


public:
    Process();
        int inputInt();
    void saveFile();
    void readData();
    void showWelcomePage();
    /// print for fix value
    void showCommand();
    void showHelpPage();
    void showSavedPage();
    void showExitPage();
    void showInfoPage();
    void showAddPage();
    void showNewTargetPage();
    void showSetDonePage();
    void showRewardPage(bool canGain);
    void showAddRewardPage();
    void showCheckTimePage();

    string enterCommand();
    void executeCommand(string command);

};

#endif