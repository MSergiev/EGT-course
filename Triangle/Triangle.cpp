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











