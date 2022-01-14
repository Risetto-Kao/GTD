#include <iostream>
#include <string>
#include <vector>
#include "process.h"
using namespace std;


int main()
{


    Process process;

    process.showWelcomePage();
    process.showCommand();
    string command = process.enterCommand();
    process.executeCommand(command);

    return 0;
}