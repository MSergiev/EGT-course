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
	Tool operator[](int);
public:
	void createFile();
	void addTool();
	void updateTool();
	void printAll() const;
	void printByID(int) const;
	void deleteTool();
public:
	int totalCount() const;
	Tool leastCount() const;
	Tool mostCount() const;
	Tool leastCost() const;
	Tool mostCost() const;
private:
	Tool createTool();
	void printHeader() const;
	void updateVector();
	void emptyVector();
private:
	fstream inOutTool;
	vector<Tool> storage;
};

#endif /* TOOLSHED_H_ */
