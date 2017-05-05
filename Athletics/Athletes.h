#ifndef ATHLETES_H_
#define ATHLETES_H_

#include <string>
using std::string;

class Athletes {
public:
	Athletes(string = "NaN", string = "NaN", float = 0.0, string = "NaN");
	~Athletes();
public:
	void setFirstName(const string firstName);
	void setLastName(const string lastName);
	void setBest(const float best);
	void setNationality(const string nationality);

	const string getFirstName() const;
	const string getLastName() const;
	const float getBest() const;
	const string getNationality() const;

private:
	string firstName;
	string lastName;
	float best;
	string nationality;
};

#endif /* ATHLETES_H_ */
