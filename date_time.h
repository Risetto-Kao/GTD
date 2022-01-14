#ifndef DATE_TIME_H
#define DATE_TIME_H
#include <iostream>
#include <string>
using namespace std;

class DateTime
{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    string twoDigits(int i);
public:
    DateTime();
    DateTime(int year, int month, int day, int hour, int minute);
    string getDateTime();
    void print();
    bool isEarlierThan(DateTime now);
    void setDateTime(int year, int month, int day,int hour, int minute);

};
#endif