#include <iostream>
#include "ToolShed.h"

using namespace std;

int main()
{
	ToolShed store;

	store.printAll();

	cout << "\n"
		 << "Total count: " << store.totalCount() << "\n"
		 << "Least count: " << store.leastCount().getCount() << "\n"
		 << "Most count: " << store.mostCount().getCount() << "\n"
		 << "Least cost: " << store.leastCost().getCost() << "\n"
		 << "Most cost: " << store.mostCost().getCost() << "\n";

	return 0;
}
