#include "Discipline.h"

#include <vector>
using std::vector;

vector<Discipline::Pair> Discipline::worldRecord;

Discipline::Discipline(string name, float worldRecord, float record)
{
	this->name = name;
	updateWorldRecord(worldRecord);
	this->record = record;
}

Discipline::~Discipline()
{

}

void Discipline::setName(const string name)
{
	this->name = name;
}

void Discipline::setRecord(float record)
{
	this->record = record;
}

const string Discipline::getName() const
{
	return name;
}

const float Discipline::getRecord() const
{
	return this->record;
}

const float Discipline::getWorldRecord() const
{
	return findWorldRecord();
}

void Discipline::updateWorldRecord(float newRecord)
{
	if (findWorldRecord() == -1.0)
	{
		Pair temp;
		temp.name = this->name;
		temp.record = newRecord;

		worldRecord.push_back(temp);
	}
	else
		if (findWorldRecord() < newRecord)
			editWorldRecord(newRecord);
}

float Discipline::findWorldRecord() const
{
	for(vector<Pair>::iterator it = (this->worldRecord).begin(); it != (this->worldRecord).end(); it++)
		if (it->name == this->name)
			return it->record;
	return -1;
}

void Discipline::editWorldRecord(float newRecord)
{
	for(vector<Pair>::iterator it = (this->worldRecord).begin(); it != (this->worldRecord).end(); it++)
		if (it->name == this->name)
			it->record = newRecord;
}
