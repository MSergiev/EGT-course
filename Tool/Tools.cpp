#include <iostream>
#include "ToolShed.h"

using namespace std;

int main()
{
	ToolShed store;

	store.printAll();

	cout << "\n"
		 << "Total count: " << store.totalCount() << "\n";
	store.printByID(store.leastCount().getRecordNum());

	return 0;
}
