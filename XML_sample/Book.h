#ifndef BOOK_H_
#define BOOK_H_

#include <string>
using std::string;

class Book
{
public:
	Book( string = "NaN", string = "NaN", int = 0, float = 0.0 );
	~Book();
public:
	const string& getAuthor() const;
	void setAuthor( const string& author );

	float getPrice() const;
	void setPrice( float price );

	const string& getTitle() const;
	void setTitle( const string& title );

	int getYear() const;
	void setYear( int year );
public:
	void print();
private:
	string title;
	string author;
	int year;
	float price;
};

#endif /* BOOK_H_ */
