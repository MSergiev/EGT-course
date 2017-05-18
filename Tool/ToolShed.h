#ifndef TOOLSHED_H_
#define TOOLSHED_H_

#include <fstream>
using std::fstream;
#include <vector>
using std::vector;
#include "Tool.h"

class ToolShed
{
public:
	ToolShed();
	~ToolShed();
public:
	void clearFile();
	void addTool();
	void updateTool();
	void printAll();
	void deleteTool();
public:
	int totalCount();
	Tool leastCount();
	Tool mostCount();
	Tool leastCost();
	Tool mostCost();
private:
	Tool createTool();
	void printHeader();
	void init();
	void updateVector();
	void emptyVector();
private:
	fstream inOutTool;
	vector<Tool> storage;
};

#endif /* TOOLSHED_H_ */
