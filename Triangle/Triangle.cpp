#include "Triangle.h"

Triangle::Triangle(int a, int b, int c, int h)
{
	_init(a, b, c, h);
}

Triangle::Triangle(const Triangle& other)
{
	_copy(other);
}

Triangle::~Triangle()
{
	_delete();
}

void Triangle::_init(int a, int b, int c, int h)
{
	setA(a);
	setB(b);
	setC(c);
	setH(h);
}

void Triangle::_copy(const Triangle& other)
{
	setA(other.getA());
	setB(other.getB());
	setC(other.getC());
	setH(other.getH());
}

void Triangle::_delete()
{
	//No need to do anything
}

Triangle& Triangle::operator=(const Triangle& other)
{
	if (*this != other)
	{
		_delete();
		_copy(other);
	}
	return *this;
}

istream& operator>> (istream& in, Triangle& obj)
{
	int temp;

	in.ignore(1);
	in >> temp;
	obj.setA(temp);

	in.ignore(1);
	in >> temp;
	obj.setB(temp);

	in.ignore(1);
	in >> temp;
	obj.setC(temp);

	in.ignore(1);
	in >> temp;
	obj.setH(temp);

	return in;
}

ostream& operator<<(ostream& out, const Triangle& obj)
{
	out << "-" << obj.getA()
		<< "-" << obj.getB()
		<< "-" << obj.getC()
		<< "-" << obj.getH();

	return out;
}

bool Triangle::operator==(const Triangle& other)
{
	if (*this == other)
		return true;

	if (this->getA() == other.getA() &&
		this->getB() == other.getB() &&
		this->getC() == other.getC() &&
		this->getH() == other.getH())
			return true;

	return false;
}

bool Triangle::operator!=(const Triangle& other)
{
	return !(*this == other);
}

int Triangle::getA() const
{
	return a;
}

void Triangle::setA(int a)
{
	this->a = a;
}

int Triangle::getB() const
{
	return b;
}

void Triangle::setB(int b)
{
	this->b = b;
}

int Triangle::getC() const
{
	return c;
}

void Triangle::setC(int c)
{
	this->c = c;
}

int Triangle::getH() const
{
	return h;
}

void Triangle::setH(int h)
{
	this->h = h;
}











