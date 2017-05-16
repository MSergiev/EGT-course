#include <iostream>
#include "Tool.h"
#include "Utility.h"

using namespace std;

int main()
{
	//init();
	fstream inOutTools("hardware.dat", ios::in | ios::out | ios::binary);

	/*addTool(inOutTools);
	addTool(inOutTools);
	addTool(inOutTools);*/

	printAll(inOutTools);

	addTool(inOutTools);
	printAll(inOutTools);


	updateTool(inOutTools);
	printAll(inOutTools);

	deleteTool(inOutTools);
	printAll(inOutTools);


	return 0;
}
