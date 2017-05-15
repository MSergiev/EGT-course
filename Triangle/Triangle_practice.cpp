#include <iostream>
#include "Triangle.h"

using namespace std;

int main()
{
	Triangle t1(12, 13, 14, 100);
	cout << "t1: \n" << t1;

	Triangle t2;
	cin >> t2;
	cout << t2;

	if (t1 == t2)
		cout << "T1 == T2\n";
	if (t1 != t2)
		cout << "T1 != T2\n";
	return 0;
}
