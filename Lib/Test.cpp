#include <iostream>
#include "Lib1.h"

using namespace std;

int main()
{
	// Test for 1
	/*cout << format( 20484567, 'ˆ' );
	cout << format( 24704.607, 'ˆ' );*/

	// Test for 2
	/*int arr[ 3 ][ 4 ] = { 123, 321, 4, 87654,
						4356, 2234, 22, 732,
						13156, 6351, 233, 2};
	string arrStr[ 4 ] = { "qwea", "dsaaaaa", "56ed3aa", "--112%@" };
	arrPrint( arr, 3, 4 );
	arrPrint( arrStr, 1, 4 );*/

	// Test for 3
	/*cout << setprecision( 7 ) << fastRound( 1445.654448, 2, 5 ) << "\n";

	clock_t start = clock();
	for ( int i = 0; i < 200000; i++ )
		slowRound( 1445.654448, 2, 5 );
	cout << "SlowRound: " << (float) ( clock() - start ) / CLOCKS_PER_SEC << "\n";

	start = clock();
	for ( int i = 0; i < 200000; i++ )
		fastRound( 1445.654448, 2, 5 );
	cout << "FastRound: " << (float) ( clock() - start ) / CLOCKS_PER_SEC << "\n";*/

	// Test for 4
	/*int divident = 16, divisor = 3;
	divResult res = divide( divident, divisor );
	cout << "16 / 3 =\n"
		 << "quotient: " << res.quotient << "\n"
		 <<	"remainder: " << res.remainder << "\n";*/

	// Test for 5
	/*int begin = 30, end = 50;

	cout << "Integers between 30 and 50: \n";
	for( int i = 0; i < 20; i++ )
		cout << picker( begin, end ) << "\n";

	cout << "Doubles: \n";
	for( int i = 0; i < 20; i++ )
		cout << doubleRNG() << "\n";

	int arr[ 10 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	shuffleArr( arr, 10 );

	for( int i = 0; i < 10; i++ )
		cout << arr[ i ] << " ";
	cout << "\n";

	int arr2[ 6 ] = { 1, 2, 3, 4, 5, 6 };
	int * subArr = returnFromArr(arr2, 6, 3);

	for( int i = 0; i < 3; i++ )
		cout << subArr[i] << " ";
	cout << "\n";

	RandomQueue randArr;

	for( int i = 0; i < 15; i++ )
		randArr.addElement(i);
	for( int i = 0; i < 15; i++ )
		cout << randArr.removeElement() << " ";
	cout << "\n";*/

	// Test for 6

	/*Hand::Card cards[5];
	cards[0].suit = SPADES;
	cards[0].val = TEN;

	cards[1].suit = CLUBS;
	cards[1].val = EIGHT;

	cards[2].suit = HEARTS;
	cards[2].val = JACK;

	cards[3].suit = SPADES;
	cards[3].val = EIGHT;

	cards[4].suit = DIAMONDS;
	cards[4].val = TEN;

	Hand hand(cards);

	cout << hand.eval();*/



	return 0;
}








