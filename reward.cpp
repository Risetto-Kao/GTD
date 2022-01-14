#include <iostream>
#include <string>
#include "reward.h"
using namespace std;

Reward::Reward()
{
	point = 0;
	name = " ";
}

Reward::Reward(int point, string name)
{
	this->point = point;
	this->name = name;
}

void Reward::setName(string name)
{
	this->name = name;
}

void Reward::gain(int &currentPoint)
{
	if (point > currentPoint)
	{
		cout << "**Sorry, This reward needs more points!**";
		return;
	}
	currentPoint -= point;
}

void Reward::setPoint(int point)
{
	this->point = point;
}

void Reward::print(int currentPoint)
{
	if (point <= currentPoint)
		cout << "[O] ";
	else
		cout << "[ ] ";
	cout << point << "  " << name << endl;
}

string Reward::getName()
{
	return name;
}

int Reward::getPoint()
{
	return point;
}