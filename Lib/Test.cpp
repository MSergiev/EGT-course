#include <iostream>
#include <ctime>
#include "DoubleRound.h"
#include "Lib.h"

using namespace std;

int main()
{
	// Test for 1
	//cout << format( 20484567, 'ˆ' );
	//cout << format( 24704.607, 'ˆ' );

	// Test for 2
	/*int arr[3][4] = { 123, 321, 4, 87654,
						4356, 2234, 22, 732,
						13156, 6351, 233, 2};
	string arrStr[4] = { "qwea", "dsaaaaa", "56ed3aa", "--112%@" };
	arrPrint( arr, 3, 4 );
	arrPrint( arrStr, 1, 4 );*/

	// Test for 3
	cout << setprecision(7) << fastRound(1445.654448, 2, 5) << "\n";

	clock_t start = clock();
	for (int i = 0; i < 200000; i++)
		slowRound(1445.654448, 2, 5);
	cout << "SlowRound: " << (float) (clock() - start) / CLOCKS_PER_SEC << "\n";

	start = clock();
	for (int i = 0; i < 200000; i++)
		fastRound(1445.654448, 2, 5);
	cout << "FastRound: " << (float) (clock() - start) / CLOCKS_PER_SEC << "\n";

	start = clock();
	for (int i = 0; i < 200000; i++)
		doubleRound(1445.654448, 2, 5);
	cout << "Miro's round: " << (float) (clock() - start) / CLOCKS_PER_SEC;



	return 0;
}








