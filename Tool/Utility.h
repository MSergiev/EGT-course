#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <fstream>
#include "Tool.h"

using namespace std;

void init();
void addTool(fstream&);
Tool createTool();
void updateTool(fstream&);
void printHeader();
void printAll(fstream&);
void deleteTool(fstream&);

void init()
{
	ofstream outTool("hardware.dat", ios::binary);

	if(!outTool)
	{
	  cerr << "File could not be opened/created." << "\n";
	  return;
	}

	Tool temp;

	for(int i = 0; i < 100; i++)
		outTool.write(reinterpret_cast <const char*> (&temp), sizeof(Tool));
}

void addTool(fstream& inOutTool)
{
	Tool newTool = createTool();

	inOutTool.seekg((newTool.getRecordNum() - 1) * sizeof(Tool));
	Tool oldTool;
	inOutTool.read(reinterpret_cast<char*>(&oldTool), sizeof(Tool));
	if (oldTool.getRecordNum() == 0)
	{
		inOutTool.seekp((newTool.getRecordNum() - 1) * sizeof(Tool));
		inOutTool.write(reinterpret_cast<char*>(&newTool), sizeof(Tool));
	}
	else
		cout << "Tool #" << oldTool.getRecordNum() << " already exists.\n";
}

Tool createTool()
{
	int recordNum;
	string name;
	int count;
	double cost;

	cout << "Enter tool ID: ";
	cin >> recordNum;
	while (recordNum < 1 || recordNum > 100)
	{
		cout << "Enter valid ID (1-100): ";
		cin >> recordNum;
	}
	cin.clear();

	cout << "Enter tool name: ";
	cin >> name;

	cout << "Enter tool count: ";
	cin >> count;

	cout << "Enter tool cost: ";
	cin >> cost;
	Tool result(recordNum, name, count, cost);
	return result;
}

void updateTool(fstream& inOutTool)
{
	Tool newTool = createTool();

	inOutTool.seekg((newTool.getRecordNum() - 1) * sizeof(Tool));
	Tool oldTool;
	inOutTool.read(reinterpret_cast<char*>(&oldTool), sizeof(Tool));

	if (oldTool.getRecordNum() == 0)
		cout << "Tool #" << oldTool.getRecordNum() << " doesn't exist.\n";
	else
	{
		printHeader();
		oldTool.print();
		cout << "Replaced with:\n";
		newTool.print();
		inOutTool.seekp((newTool.getRecordNum() - 1) * sizeof(Tool));
		inOutTool.write(reinterpret_cast<char*>(&newTool), sizeof(Tool));
	}
}

void printHeader()
{
	cout << "ID   Name       Count   Cost\n";
}

void printAll(fstream& inOutTool)
{
	inOutTool.seekg(0);
	printHeader();

	Tool temp;

	for(int i = 0; i < 100; i++)
	{
		if(inOutTool.eof())
			return;
		else
		{
			inOutTool.read(reinterpret_cast<char*>(&temp), sizeof(Tool));
			if(temp.getRecordNum() != 0)
				temp.print();
		}
	}
}

void deleteTool(fstream& inOutTool)
{
	int temp;
	cout << "Enter ID of tool to delete: ";
	cin >> temp;
	while (temp < 1 || temp > 100)
	{
		cout << "Enter valid ID (1-100): ";
		cin >> temp;
	}
	inOutTool.seekp((temp - 1) * sizeof(Tool));
	Tool emptyTool;
	inOutTool.write(reinterpret_cast<char*>(&emptyTool), sizeof(Tool));
}

#endif /* UTILITY_H_ */
