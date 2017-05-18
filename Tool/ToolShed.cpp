#include "ToolShed.h"

#include <fstream>
using std::ios;
using std::ofstream;
#include <iostream>
using std::cerr;
using std::cout;
using std::cin;

ToolShed::ToolShed()
{
	std::ifstream tempIn;
	tempIn.open("hardware.dat");

	if (tempIn)
	{
		tempIn.close();
		inOutTool.open("hardware.dat", ios::in | ios::out | ios::binary);
		updateVector();
	}
	else
		createFile();
}

ToolShed::~ToolShed()
{
	inOutTool.close();
}

void ToolShed::createFile()
{
	ofstream outTool("hardware.dat", ios::binary);

	if(!outTool)
	{
	  std::cerr << "File could not be opened/created." << "\n";
	  return;
	}

	Tool temp;

	for(int i = 0; i < 100; i++)
		outTool.write(reinterpret_cast <const char*> (&temp), sizeof(Tool));
	updateVector();
}

void ToolShed::addTool()
{
	Tool newTool = createTool();

	inOutTool.seekg((newTool.getRecordNum() - 1) * sizeof(Tool));
	Tool oldTool;
	inOutTool.read(reinterpret_cast<char*>(&oldTool), sizeof(Tool));
	if (oldTool.getRecordNum() == 0)
	{
		inOutTool.seekp((newTool.getRecordNum() - 1) * sizeof(Tool));
		inOutTool.write(reinterpret_cast<char*>(&newTool), sizeof(Tool));
		updateVector();
	}
	else
		cout << "Tool #" << oldTool.getRecordNum() << " already exists.\n";
}

void ToolShed::updateTool()
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
		updateVector();
	}
}

void ToolShed::printAll() const
{
	/*inOutTool.seekg(0);
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
	}*/
	printHeader();
	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		it->print();
}

void ToolShed::deleteTool()
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
	updateVector();
}

Tool ToolShed::createTool()
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

void ToolShed::printHeader() const
{
	cout << "ID   Name       Count   Cost\n";
}

void ToolShed::updateVector()
{
	emptyVector();
	Tool temp;
	inOutTool.seekg(0);
	for(int i = 0; i < 100; i++)
	{
		if(inOutTool.eof())
			return;
		else
		{
			inOutTool.read(reinterpret_cast<char*>(&temp), sizeof(Tool));
			if(temp.getRecordNum() != 0)
				storage.push_back(temp);
		}
	}
}

int ToolShed::totalCount() const
{
	int result = 0;

	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		result += it->getCount();

	return result;
}

Tool ToolShed::leastCount() const
{
	Tool result;
	int min = 99999999;

	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		if(min > it->getCount())
		{
			min = it->getCount();
			result = (*it);
		}
	return result;
}

Tool ToolShed::mostCount() const
{
	Tool result;
	int max = 0;

	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		if(max < it->getCount())
		{
			max = it->getCount();
			result = (*it);
		}
	return result;
}

Tool ToolShed::leastCost() const
{
	Tool result;
	int min = 99999999;

	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		if(min > it->getCost())
		{
			min = it->getCost();
			result = (*it);
		}
	return result;
}

Tool ToolShed::mostCost() const
{
	Tool result;
	int max = 0;

	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		if(max < it->getCost())
		{
			max = it->getCost();
			result = (*it);
		}
	return result;
}

Tool ToolShed::operator [](int ID)
{
	Tool result;
	for(vector<Tool>::iterator it = storage.begin(); it != storage.end(); it++)
		if(ID == it->getRecordNum())
		{
			result = (*it);
			return result;
		}
	return result;

}

void ToolShed::emptyVector()
{
	while(!storage.empty())
		storage.pop_back();
}

void ToolShed::printByID(int ID) const
{
	for(vector<Tool>::const_iterator it = storage.begin(); it != storage.end(); it++)
		if(ID == it->getRecordNum())
		{
			printHeader();
			it->print();
			return;
		}
	cout << "No such ID was found.\n";
}





























