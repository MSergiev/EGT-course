#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <iostream>
using std::istream;
using std::ostream;

class Triangle
{
public:
	Triangle(int = 0, int = 0, int = 0, int = 0);
	Triangle(const Triangle&);
	~Triangle();
public:
	Triangle& operator=(const Triangle&);
	friend istream& operator>>(istream&, Triangle&);
	friend ostream& operator<<(ostream&, const Triangle&);
	bool operator==(const Triangle&);
	bool operator!=(const Triangle&);
public:
	int getA() const;
	void setA(int a);
	int getB() const;
	void setB(int b);
	int getC() const;
	void setC(int c);
	int getH() const;
	void setH(int h);
private:
	void _init(int, int, int, int);
	void _copy(const Triangle&);
	void _delete();
private:
	int a, b, c, h;
};

#endif /* TRIANGLE_H_ */
