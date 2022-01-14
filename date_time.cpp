#include "date_time.h"
#include <iostream>
using namespace std;

DateTime::DateTime()
{
    year = 2022;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
}

string DateTime::twoDigits(int i)
{
    string res;

    if (i >= 10)
        res = to_string(i);
    else
        res = "0" + to_string(i);
    return res;
}

string DateTime::getDateTime()
{
    string yearStr = to_string(year);
    string monthStr = twoDigits(month);
    string dayStr = twoDigits(day);
    string hourStr = twoDigits(hour);
    string minuteStr = twoDigits(minute);
    string tmp = yearStr + "/" + monthStr + "/" + dayStr + "-" + hourStr + ":" + minuteStr;
    return tmp;
}

void DateTime::print()
{
    if (getDateTime() == "2022/01/01-00:00")
    {
        return;
    }

    cout << getDateTime() << endl;
}

// TODO: ¸É¥\¯à
bool DateTime::isEarlierThan(DateTime now)
{
    // cout << now.getDateTime();
    if (now.year > year)
        return true;
    else if (now.year < year)
        return false;
    if (now.month > month)
        return true;
    else if (now.month < month)
        return false;
    if (now.day > day)
        return true;
    else if (now.day < day)
        return false;
    if (now.hour > hour)
        return true;
    else if (now.hour < hour)
        return false;
    if (now.minute > minute)
        return true;
    else if (now.minute < minute)
        return false;

    return true;
}

void DateTime::setDateTime(int year, int month, int day, int hour, int minute)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
}


