#include "Tool.h"

#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

Tool::Tool(int recordNum, string name, int count, double cost)
{
	setRecordNum(recordNum);
	setName(name);
	setCount(count);
	setCost(cost);
}

Tool::~Tool()
{

}

double Tool::getCost() const
{
	return cost;
}

void Tool::setCost(double cost)
{
	this->cost = cost;
}

int Tool::getCount() const
{
	return count;
}

void Tool::setCount(int count)
{
	this->count = count;
}

string Tool::getName() const
{
	return name;
}

void Tool::setName(const string& name)
{
	const char *nameValue = name.data();
	int length = name.size();
	if(length > 9)
		length = 9;
	strncpy(this->name, nameValue, length);
	this->name[length] = '\0';
}

int Tool::getRecordNum() const
{
	return recordNum;
}

void Tool::setRecordNum(int recordNum)
{
	this->recordNum = recordNum;
}

void Tool::print() const
{
	cout << left << setw(5) << getRecordNum()
				  << setw(11) << getName()
				  << setw(8) << getCount()
				  << setw(8) << getCost() << "\n";
}



















