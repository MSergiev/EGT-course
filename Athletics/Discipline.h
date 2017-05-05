#ifndef DISCIPLINE_H_
#define DISCIPLINE_H_

#include <vector>
using std::vector;

#include <string>
using std::string;

class Discipline {
	struct Pair	{
		string name;
		float record;
	};
public:
	Discipline(string = "NaN", float = 0.0, float = 0.0);
	~Discipline();
public:
	void setName(const string name);
	void setRecord(float);
	void updateWorldRecord(float);

	const string getName() const;
	const float getRecord() const;
	const float getWorldRecord() const;
private:
	float findWorldRecord() const;
	void editWorldRecord(float);
private:
	string name;
	static vector<Pair> worldRecord;
	float record;
};


#endif /* DISCIPLINE_H_ */
