#include <iostream>
#include "process.h"
#include "defaultValue.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "checkList.h"
#include <windows.h>
#include <stdio.h>
#include "date_time.h"
using namespace std;

Process::Process()
{
    readData();
    initAllCheckLists();
    initAllTargets();
}

void Process::initAllTargets()
{
    allTargets.clear();
    for (auto &event : allEvents)
    {
        if (!isTargetExist(event.getTargetName()))
        {
            Target target(event.getTargetName());
            allTargets.push_back(target);
        }
    }

    for (auto &event : allEvents)
    {
        for (auto &target : allTargets)
        {
            if (event.getTargetName() == target.getName())
            {
                target.addEvent(event);
            }
        }
    }
}

int Process::inputInt()
{
    string tmp;

    int res;
    while (true)
    {
        cin >> tmp;
        try
        {
            res = stoi(tmp);
            break;
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
        }
    }
    return res;
}

void Process::initAllCheckLists()
{
    allCheckLists.clear();
    CheckList twoMin("two-min");
    CheckList future("future");
    allCheckLists.push_back(twoMin);
    allCheckLists.push_back(future);

    for (auto &event : allEvents)
    {
        if (event.getCheckListName() == "trash")
            continue;
        string checkListName = event.getCheckListName();
        if (checkListName != "two-min" && checkListName != "future")
        {
            if (!isCheckListExist(event.getCheckListName()))
            {
                CheckList newList(event.getCheckListName());
                allCheckLists.push_back(newList);
            }
        }
    }

    for (auto &event : allEvents)
    {
        for (auto &list : allCheckLists)
        {

            if (event.getCheckListName() == list.getName())
            {
                list.addEvent(event);
            }
        }
    }
}

void Process::executeCommand(string command)
{
    // TODO: 10
    if (command == "-exit")
        showExitPage();
    //---------------------------
    else if (command == "-h")
        showHelpPage();
    else if (command == "-save")
        showSavedPage();
    else if (command == "-s")
        showInfoPage();
    else if (command == "-a")
        showAddPage();
    else if (command == "-i")
        showNewTargetPage();
    else if (command == "-d")
        showSetDonePage();
    else if (command == "-sr")
        showRewardPage(false);
    else if (command == "-ar")
        showAddRewardPage();
    else if (command == "-gr")
        showRewardPage(true);
    else if (command == "-c")
        showCheckTimePage();
    initAllCheckLists();
    initAllTargets();
    executeCommand(enterCommand());
}

void Process::showWelcomePage()
{
    cout << introWithFrame("welcome", 3);
}

void Process::showCommand()
{
    cout << introWithFrame("commands", 3);
}

void Process::showAddRewardPage()
{
    string name;
    int point;
    while (true)
    {
        cout << "(��J'-end'���X) <����>�W��: ";
        // cout << "enter '-end' to end / sho"
        cin >> name;
        if (isRewardExist(name))
        {
            cout << "�w�s�b!�Э��s��J\n";
            continue;
        }

        if (name == "-end")
            break;

        cout << "�o��<����>�Φh���I�i�I��: ";
        // cout << "how much point?";
        cin >> point;

        addReward(point, name);
    }
}

void Process::showRewardPage(bool canGain)
{
    cout << "�A�{�b�����ƬO: " << currentPoint << endl;

    for (int i = 0; i < allRewards.size(); i++)
    {
        cout << i + 1 << ". ";
        allRewards[i].print(currentPoint);
    }

    if (canGain)
    {
        int order;
        cout << "�A�Q�I�����Ӽ���\n";

        while (true)
        {
            cout << "(��J 0 ���������`) <����>�s��: ";
            cin >> order;
            int index = order - 1;

            if (order == 0)
                break;
            if (order > allRewards.size())
            {
                cout << "�п�J�X�z���Ʀr\n\n";
                continue;
            }

            if (allRewards[index].getPoint() <= currentPoint)
            {
                currentPoint -= allRewards[index].getPoint();
                cout << "�n�n�ɨ��a!\n";
                break;
            }
            else
            {
                cout << "�I�Ƥ���!\n";
                cout << "�Э��s��J\n";
                continue;
            }
        }
    }
}
string Process::enterCommand()
{
    string inputCommand;
    while (true)
    {
        string stuff(WIDTH, '_');
        cout << endl
             << stuff << endl;
        cout << "��J���O --> ";
        cin >> inputCommand;
        for (auto &command : COMMANDS)
        {
            if (command == inputCommand)
            {
                return inputCommand;
            }
        }
        /// if not in commands
        cout << "�п�J�X�z�����O(�Y�ѰO�i��-h)\n";
    }
    return inputCommand;
}

void Process::saveFile()
{
    ofstream gtdFile;
    gtdFile.open(GTD_PATH);
    if (gtdFile.is_open())
    {
        gtdFile << allEvents.size() << "\n";
        for (auto &event : allEvents) /// save into gtdFile
        {
            gtdFile << event.getName() << " ";
            gtdFile << event.getDescription() << " ";
            gtdFile << event.isDone() << " ";
            gtdFile << event.getTargetName() << " ";
            gtdFile << event.getCheckListName() << " ";
            gtdFile << event.getDeadlineStr(true) << " ";
            gtdFile << event.getPoint() << "\n";
        }
        gtdFile.close();
    }
    else
    {
        cout << "Fail to open file GTD.\n";
    }
    ofstream rewardFile;
    rewardFile.open(REWARD_PATH);
    if (rewardFile.is_open())
    {
        rewardFile << currentPoint << " " << allRewards.size() << endl;
        for (auto &reward : allRewards)
        {
            rewardFile << reward.getName() << " " << reward.getPoint() << endl;
        }
        rewardFile.close();
    }
    else
    {
        cout << "Fail to open file reward.\n";
    }
}
void Process::readData()
{
    // TODO: 10
    ifstream gtdFile;

    /// read GTD data
    gtdFile.open(GTD_PATH);
    if (gtdFile.is_open())
    {
        int eventCnt;
        gtdFile >> eventCnt;
        for (int i = 0; i < eventCnt; i++) /// read and generate event into allEvents
        {
            // TODO: 3
            string name;
            string description;
            bool done;
            string targetName;
            string checkListName;
            string deadline;
            int point;
            gtdFile >> name >> description;
            gtdFile >> done >> targetName >> checkListName;
            gtdFile >> deadline >> point;

            Event event(name);
            event.setDescription(description);
            event.setDone(done);
            event.setTargetName(targetName);

            event.setCheckListName(checkListName);
            event.setDeadline(deadline);
            event.setPoint(point);

            allEvents.push_back(event);
        }
        gtdFile.close();
    }
    else
    {
        cout << "Fail to open file GTD.\n";
    }

    /// read Reward data
    ifstream rewardFile;

    rewardFile.open(REWARD_PATH);
    if (rewardFile.is_open())
    {
        int rewardCnt = 0;
        rewardFile >> currentPoint;
        rewardFile >> rewardCnt;
        for (int i = 0; i < rewardCnt; i++)
        {
            string name;
            int point;
            rewardFile >> name >> point;
            Reward reward(point, name);
            allRewards.push_back(reward);
        }
        rewardFile.close();
    }
    else
    {
        cout << "Fail to open file Reward.\n";
    }
}

void Process::showExitPage()
{
    // TODO: 6
    // if (!isSaved)
    // saveFile();
    cout << introWithFrame("exit", 3);
    saveFile();
    Sleep(5000);
    exit(EXIT_FAILURE);
}
void Process::showHelpPage()
{
    cout << introWithFrame("help", 3);
}
void Process::showSavedPage()
{
    saveFile();
    cout << "�ɮפw�x�s!\n";
}
void Process::showInfoPage() // show target & list
{
    string dash(55, '-');
    string strTarget = dash + "  �ؼ�  " + dash;
    string strCheckList = dash + "  �M��  " + dash;

    cout << strTarget << endl;
    for (auto &target : allTargets)
    {
        target.printEvents();
        cout << endl;
    }
    cout << strCheckList << endl;

    for (auto &list : allCheckLists)
    {
        list.printEvents();
        cout << endl;
    }

}

void Process::showCheckTimePage()
{
    time_t t = time(0);
    tm *tm = localtime(&t);
    int year = tm->tm_year;
    int month = tm->tm_mon;
    int day = tm->tm_mday;
    int hour = tm->tm_hour;
    int minute = tm->tm_min;
    DateTime now(year + 1900, month, day, hour, minute);

    cout << "�w�O����<����>�̡A�A�����F�ܡH(�����F�Ы� -d �]�w��done)\n";

    for (auto &event : allEvents)
    {

        if (event.getDeadlineStr(true) == "2022/01/01-00:00")
            continue;
        if (event.getDeadline().isEarlierThan(now))
        {
            if (!event.isDone())
            {
                cout << event.getName() << " " << event.getDeadlineStr(true) << endl;
            }
        }
    }
}

void Process::addReward(int point, string name)
{
    Reward reward(point, name);
    allRewards.push_back(reward);
}
void Process::showNewTargetPage()
{
    cout << introWithFrame("new_target", 3);
    string targetName;
    string checkListName;
    while (true)
    {
        cout << "<�ؼ�>�W��: ";
        cin >> targetName;
        if (isTargetExist(targetName))
            cout << "�w�s�b!�Э��s��J\n";
        else
            break;
    }

    Target target(targetName);
    addEvents(target);
    allTargets.push_back(target);
    modifyEventsInfo(targetName);
    classifyEvents(target);
}
void Process::showSetDonePage()
{

    vector<int> doneIndexes;

    for (int i = 0; i < allEvents.size(); i++)
    {
        cout << i + 1 << ". " << allEvents[i].getName() << endl;
    }

    while (true)
    {
        int index;
        cout << "(��J 0 ���������`) ����<����>�s��: ";
        cin >> index;

        if (index == 0)
            break;
        if (index > allEvents.size() || index < 0)
        {
            cout << "�п�J�X�z���Ʀr\n\n";
            continue;
        }

        doneIndexes.push_back(index - 1);
    }

    for (auto &index : doneIndexes)
    {
        allEvents[index].setDone(true);
    }

    currentPoint = 0;

    for (auto &event : allEvents)
    {
        if (event.isDone())
            currentPoint += event.getPoint();
    }

    // TODO: not done or need to change
}
void Process::classifyEvents(Target &target)
{
    cout << introWithFrame("classify", 3);
    target.printEvents();
    cout << "�Ы�ҨC��<����>�b����<�M��>����\n";
    for (int i = 0; i < allEvents.size(); i++)
    {
        // TODO: the order need to be correct
        if (allEvents[i].getTargetName() != target.getName())
        {
            continue;
        }
        classifyEvent(allEvents[i]);
    }

    // todo list
    cout << introWithFrame("situ", 3);
    int cnt = 0;
    for (int i = 0; i < allEvents.size(); i++)
    {
        if (allEvents[i].getTargetName() != target.getName())
        {
            continue;
        }

        if (allEvents[i].getCheckListName() == "todo")
        {
            classifySituation(allEvents[i], cnt);
            cnt++;
        }
    }
}

void Process::classifySituation(Event &event, int cnt)
{
    string checkListName;

    if (cnt == 0)
    {
        while (true)
        {

            cout << "(��J '-end' ���������`) ����<�M��>�W��: ";
            cin >> checkListName;
            if (isCheckListExist(checkListName))
            {
                cout << "�w�s�b!�Э��s��J\n";
                continue;
            }
            else if (checkListName == "-end")
                break;
            else
            {
                CheckList checkList(checkListName);
                allCheckLists.push_back(checkList);
            }
        }
    }

    cout << "<����>�W��: " << event.getName() << endl;
    cout << "�b���ӱ���<�M��>��: ";
    while (true)
    {
        cin >> checkListName;
        if (isCheckListExist(checkListName))
        {
            event.setCheckListName(checkListName);
            break;
        }
        else
        {
            cout << "���M�椣�s�b!\n";
            continue;
        }
    }
}

void Process::classifyEvent(Event &event)
{
    string checkListName;
    cout << "<����>�W��: " << event.getName() << endl;
    cout << "�b����<�M��>��( 2 / f / todo ): ";
    while (true)
    {
        cin >> checkListName;

        if (checkListName == "2")
        {
            event.setCheckListName("two-min");
            break;
        }
        else if (checkListName == "f")
        {
            event.setCheckListName("future");
            break;
        }
        else if (checkListName == "todo")
        {
            event.setCheckListName("todo");
            break;
        }
        else if (checkListName == "trash")
        {
            event.setCheckListName("trash");
            break;
        }
        cout << "�п�J�X�z������!( 2 / f / todo )\n";
    }
}

void Process::addEvents(Target &target)
{
    string eventName;
    cout << introWithFrame("add_event", 3);
    while (true)
    {
        cout << "(��J '-end' ���������`) <����>�W��: ";
        cin >> eventName;
        if (eventName == "-end")
            break;

        Event event(eventName);
        event.setTargetName(target.getName());
        allEvents.push_back(event);
    }
}

void Process::modifyEventsInfo(string targetName)
{
    cout << introWithFrame("event_description", 3);
    for (int i = 0; i < allEvents.size(); i++)
    {
        if (allEvents[i].getTargetName() != targetName)
            continue;
        else
        {
            modifyEventInfo(allEvents[i]);
        }
    }
}

void Process::modifyEventInfo(Event &event)
{
    string description = "--";
    string tmp = " ";
    bool hasDeadline;
    DateTime deadline;

    int point;

    cout << "\n<����>�W��: " << event.getName() << endl;

    cout << "�y�z:";
    cin >> description;

    cout << "���S�����u?";
    while (tmp != "y" && tmp != "n")
    {
        cout << " (y/n): ";
        cin >> tmp;
    }
    hasDeadline = tmp == "y";
    if (hasDeadline)
    {
        // int year, mon, day, hour, minute;
        // cout << "�~��: ";
        // cin >> year;
        // cout << "���: ";
        // cin >> mon;
        // cout << "���: ";
        // cin >> day;
        // cout << "�p��: ";
        // cin >> hour;
        // cout << "����: ";
        // cin >> minute;

        // deadline.setDateTime(year, mon, day, hour, minute);
        deadline = askDateTime();
    }
    cout << "��o��h���I��: ";
    cin >> point;
    event.setDescription(description);
    event.setPoint(point);
    event.setDeadline(deadline);
}

DateTime Process::askDateTime()
{
    int year, mon, day, hour, minute;

    while (true)
    {
        cout << "�~��: ";
        cin >> year;
        if (year <= 1000)
        {
            cout << "�п�J�褸�~\n";
            continue;
        }
        else
            break;
    }
    while (true)
    {
        cout << "���: ";
        cin >> mon;
        if (mon > 12)
        {
            cout << "�п�J�X�z�ƭ�\n";
            continue;
        }
        else
            break;
    }
    while (true)
    {
        cout << "���: ";
        cin >> day;
        if (day > 31)
        {
            cout << "�п�J�X�z�ƭ�\n";
            continue;
        }
        else
            break;
    }
    while (true)
    {
        cout << "�p��: ";
        cin >> hour;
        if (hour > 23)
        {
            cout << "�п�J�X�z�ƭ�\n";
            continue;
        }
        else
            break;
    }
    while (true)
    {
        cout << "����: ";
        cin >> minute;
        if (minute > 59)
        {
            cout << "�п�J�X�z�ƭ�\n";
            continue;
        }
        else
            break;
    }

    DateTime deadline(year, mon, day, hour, minute);
    return deadline;
}

void Process::addEvent()
{
    if (allTargets.empty())
    {
        cout << "�Х������@��<�ؼ�>.\n\n";
        return;
    }
    string eventName;
    string targetName;
    string checkListName;

    // TODO: 10
    while (true)
    {
        cout << "<����>�W��: ";
        cin >> eventName;
        if (isEventExist(eventName))
            cout << "�w�s�b!�Э��s��J\n";
        else
            break;
    }

    Event event(eventName);

    while (true)
    {
        // TODO: show all exist target
        cout << "�ݩ����<�ؼ�>: ";
        cin >> targetName;
        if (isTargetExist(targetName))
            break;
        else
            cout << "�ؼФ��s�b�A�Э��s��J\n";
    }

    modifyEventInfo(event);

    while (true)
    {
        // TODO: 9
        cout << "�ݩ����<�M��>: ";
        cin >> checkListName;
        if (isCheckListExist(checkListName))
            break;
        else
            cout << "�M�椣�s�b�A�Э��s��J\n\n";
    }

    event.setTargetName(targetName);
    event.setCheckListName(checkListName);
    allEvents.push_back(event);
}

void Process::showAddPage()
{
    addEvent();
}

void Process::printFile(string fileName)
{
    string path = CONTENT_PATH + fileName + FILE_TYPE;
    ifstream contentFile(path);
    if (!contentFile.is_open())
    {
        cerr << "Could not open the file '" << path << "'";
        exit(EXIT_FAILURE);
    }
    string content((istreambuf_iterator<char>(contentFile)), istreambuf_iterator<char>());
    cout << content;
}

bool Process::isCheckListExist(string checkListName)
{
    for (auto &list : allCheckLists)
    {
        if (list.getName() == checkListName)
            return true;
    }
    return false;
}

bool Process::isTargetExist(string targetName)
{
    for (auto &target : allTargets)
    {
        if (target.getName() == targetName)
            return true;
    }
    return false;
}

bool Process::isEventExist(string eventName)
{
    for (auto &event : allEvents)
    {
        if (event.getName() == eventName)
            return true;
    }
    return false;
}

bool Process::isRewardExist(string rewardName)
{
    for (auto &reward : allRewards)
    {
        if (reward.getName() == rewardName)
            return true;
    }
    return false;
}

string Process::introWithFrame(string fileName, int type)
{
    string total = oneLine("", 1);

    string path = CONTENT_PATH + fileName + FILE_TYPE;
    ifstream contentFile(path);
    if (!contentFile.is_open())
    {
        cerr << "Could not open the file '" << path << "'";
        exit(EXIT_FAILURE);
    }

    while (!contentFile.eof())
    {
        string tmp;
        getline(contentFile, tmp);
        total += oneLine(tmp, type);
    }

    total += oneLine("", 2);

    return total;
}

string Process::oneLine(string context, int type)
{
    string line;
    if (type == 0) // space
    {
        string spaces(WIDTH - 2, ' ');
        line = "|" + spaces + "|";
    }
    if (type == 1) // upper
    {
        string middleLine(WIDTH - 2, '-');
        line = "-" + middleLine + "-";
    }

    if (type == 2) // lower
    {
        string middleLine(WIDTH - 2, '-');
        line = "-" + middleLine + "-";
    }

    if (type == 3) // has content -- left shift 4 digits
    {
        string frontSpaces(4, ' ');
        line = frontSpaces + context + "\n";
    }

    if (type == 4) // has content -- middle
    {
        int length = context.length();
        int frontLength;
        int backLength;
        if (length % 2 == 0)
        {
            frontLength = (WIDTH - length - 2) / 2;
            backLength = frontLength;
        }
        else
        {
            frontLength = (WIDTH - length - 2) / 2;
            backLength = frontLength + 1;
        }
        string frontSpaces(frontLength, ' ');
        string backSpaces(backLength, ' ');
        line = frontSpaces + context + backSpaces;
    }

    if (type == 5)
    {
        return context;
    }

    return line;
}
