#include <iostream>
#include "Triangle.h"

using namespace std;

int main()
{
	Triangle t1(12, 13, 14, 100);
	Triangle t2(3, 4, 5, 8);

	if (t1 == t2)
		cout << "T1 == T2\n";
	if (t1 != t2)
		cout << "T1 != T2\n";
	return 0;
}
