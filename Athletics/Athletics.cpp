#include <iostream>
#include "Athletes.h"
#include "Discipline.h"

using namespace std;

int main()
{
	Athletes test1("Pesho", "Peshov", 2.02, "Pernik");
	Discipline test2("100m Sprint", 13.2, 9);
	Discipline test3("100m Sprint", 12.3, 2);



	cout << test2.getName() << "\n"
		 << test2.getRecord() << "\n"
		 << test2.getWorldRecord();



	return 0;
}















