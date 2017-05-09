#include <iostream>
#include "Athletes.h"
#include "Discipline.h"

using namespace std;

int main()
{
	Athletes test1("Pesho", "Peshov", 2.02, "Pernik");
	//Athletes t(test1);
	Discipline test2("100m Sprint", 13.2, 1.2);
	Discipline test3("100m Sprint", 12.3, 2);



	cout << test3.getName() << "\n"
		 << test3.getRecord() << "\n"
		 << test3.getWorldRecord();



	return 0;
}















