#ifndef REWARD_H
#define REWARD_H

#include <string>
using namespace std;

class Reward
{
private:
    int point;
    string name;
public:
    Reward();
    Reward(int point,string name);
	void setName(string name);
    void setPoint(int point);
	void gain(int &currentPoint); // call if the user gains the reward
    void print(int currentPoint);
    string getName();
    int getPoint();
};


#endif