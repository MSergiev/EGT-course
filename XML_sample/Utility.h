#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <cstdlib>
#include <sstream>
using std::ostringstream;
#include "Book.h"

pugi::xml_document* load();
void printXML( pugi::xml_document* );
void traversal(vector< Book >&, pugi::xml_document* );
void create( vector< Book >& );




pugi::xml_document* load()
{
	pugi::xml_document* doc = new pugi::xml_document();
	if ( !doc->load_file( "Books.xml" ) )
		return 0;
	return doc;
}

void printXML( pugi::xml_document* doc )
{
	pugi::xml_node books = doc->child( "Books" );
	for ( pugi::xml_node book = books.first_child(); book; book = book.next_sibling() )
	{
		Book temp;

		temp.setTitle( book.child_value( "title" ) );
		temp.setAuthor( book.child_value( "author" ) );
		temp.setYear( book.child( "year" ).text().as_int() );
		temp.setPrice( book.child( "price" ).text().as_float() );

		temp.print();
		cout << "//////////////////////////////////////////////\n";
	}
}

void traversal( vector< Book >& store, pugi::xml_document* doc )
{
	pugi::xml_node books = doc->child("Books");
	for ( pugi::xml_node book = books.first_child(); book; book = book.next_sibling() )
	{
		Book temp;

		temp.setTitle( book.child_value( "title" ) );
		temp.setAuthor( book.child_value( "author" ) );
		temp.setYear( book.child( "year" ).text().as_int() );
		temp.setPrice( book.child( "price" ).text().as_float() );

		store.push_back(temp);
	}
}

void create( vector< Book >& store )
{
	pugi::xml_document doc;
	pugi::xml_node root = doc.append_child( "Books" );

	for ( vector< Book >::iterator it = store.begin(); it != store.end(); it++ )
	{
		pugi::xml_node newBook = root.append_child( "Book" );

		pugi::xml_node newTitle = newBook.append_child( "title" );
		newTitle.append_child( pugi::node_pcdata ).set_value( it->getTitle().data() );

		pugi::xml_node newAuthor = newBook.append_child( "author" );
		newAuthor.append_child( pugi::node_pcdata ).set_value( it->getAuthor().data() );

		ostringstream temp;
		temp << it->getYear();
		string tempStr(temp.str());
		pugi::xml_node newYear = newBook.append_child( "year" );
		newYear.append_child( pugi::node_pcdata ).set_value( tempStr.data() );

		temp.clear();
		temp.str(string());
		temp << it->getPrice();
		tempStr = temp.str();
		pugi::xml_node newPrice = newBook.append_child( "price" );
		newPrice.append_child( pugi::node_pcdata ).set_value( tempStr.data() );
	}

	doc.save_file("Books2.xml");

}
































#endif /* UTILITY_H_ */
