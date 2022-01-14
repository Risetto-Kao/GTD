#include <string>
#include <vector>
using namespace std;

// TODO: add command
const vector<string> COMMANDS = {"-h", "-save","-c", "-s","-gr" ,"-a", "-sr","-ar", "-d", "-exit", "-i"};

const string DEFAULT_EVENT_DESCRIPTION = "[Default]-description";
const string DEFAULT_EVENT_NAME = "[Default]-name";
const int DEFAULT_EVENT_ID = -1;
const int DEFAULT_EVENT_POINT = 0;
const bool DEFAULT_EVENT_DONE = false;
const bool DEFAULT_EVENT_HAS_DEADLINE = false;
const string DEFAULT_EVENT_DEADLINE_STRING = "--/--|--:--";

const string DEFAULT_CHECKLIST_NAME = "--";
const int DEFAULT_CHECKLIST_ID = -1;
const int TWO_MIN_LIST_ID = 0;
const int FUTURE_LIST_ID = 1;
const string TWO_MIN_LIST_NAME = "two_min";
const string FUTURE_LIST_NAME = "future";

const string DEFAULT_TARGET_NAME = "[Default]-name";

const string CONTENT_PATH = "text_content/";
const string DATA_PATH = "data/";
const string FILE_TYPE = ".txt";


const string GTD_PATH = DATA_PATH + "data" + FILE_TYPE;
const string REWARD_PATH = DATA_PATH + "reward" + FILE_TYPE;

const int WIDTH = 118;
