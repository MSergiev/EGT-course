#include <iostream>
#include <vector>
#include "pugixml.hpp"
#include "Utility.h"
#include "Book.h"

using namespace std;

int main()
{
	// Load Books.xml
	pugi::xml_document* doc;
	if( !( doc = load() ) )
		cout << "Could not open XML.\n";
	else
		cout << "Successfully opened XML.\n";


	// Print info from Books.xml
	printXML(doc);


	// Store data from Books.xml to vector<Book> store
	vector< Book > store;
	traversal(store, doc);


	// Create Books2.xml from vector<Book>
	create(store);



	return 0;
}
