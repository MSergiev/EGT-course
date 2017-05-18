#ifndef TOOL_H_
#define TOOL_H_

#include <string>
using std::string;

class Tool
{
public:
	Tool(int = 0, string = "NaN", int = 0, double = 0);
	~Tool();
public:
	double getCost() const;
	void setCost(double cost);
	int getCount() const;
	void setCount(int count);
	string getName() const;
	void setName(const string& name);
	int getRecordNum() const;
	void setRecordNum(int recordNum);
public:
	void print() const;
private:
	int recordNum;
	char name[10];
	int count;
	double cost;
};

#endif /* TOOL_H_ */
