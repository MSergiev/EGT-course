#include "Book.h"

#include <iostream>
using std::cout;

Book::Book( string title, string author, int year, float price )
{
	setTitle( title );
	setAuthor( author );
	setYear( year );
	setPrice( price );
}

Book::~Book()
{

}

const string& Book::getAuthor() const
{
	return author;
}

void Book::setAuthor( const string& author )
{
	this->author = author;
}

float Book::getPrice() const
{
	return price;
}

void Book::setPrice( float price )
{
	this->price = price;
}

const string& Book::getTitle() const
{
	return title;
}

void Book::setTitle( const string& title )
{
	this->title = title;
}

int Book::getYear() const
{
	return year;
}

void Book::setYear( int year )
{
	this->year = year;
}

void Book::print()
{
	cout << "Title is: " << title << "\n"
		 << "Author is: " << author << "\n"
		 << "Year of release: " << year << "\n"
		 << "Price: " << price << "\n";
}
