#ifndef LIB1_H_
#define LIB1_H_

#include <iostream>
using std::cout;
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;
#include <iomanip>
using std::setw;
using std::setprecision;
#include <cmath>
using std::pow;


// 1. lib function that formats a currency appropriately (and returns a string)
string format( int, char );
string format( double, char );
// 2. lib function that prints an array (initially specific types, later generic/template) or matrix,
// including columns, spacing tweaking
template < typename T >
void arrPrint( T*, int, int );
// 3. lib function to round a double to a specific number of digits (including after / before comma),
// that produces double (not string)
// 3.1: looks as much as it can to the right and rounds each step accordingly: 14448 -> 1445 -> 145 -> 15
double slowRound( double, int, int );
int _calcLeft( int, int );
double _calcRight( double, int );
int _countDigitsLeft( int );
int _countDigitsRight( double );
// 3.2: looks at 1 digit above the set precision to round up: 14448 -> 14
double fastRound( double, int, int );
int _fcalcLeft( int, int );
double _fcalcRight( double, int );
// 4. lib function that produces quotient and reminder (returning struct)
struct divResult;
divResult divide( int, int );



string format( int value, char currency )
{
	ostringstream sstream;
	sstream << value;
	string str = sstream.str();

	for( int i = str.size() - 3; i > 0; i -= 3 )
		str.insert( i, "," );
	return str + currency;
}

string format( double value, char currency )
{
	std::ostringstream sstream;
	sstream << std::fixed << setprecision(2) << value;
	string str = sstream.str();

	for( int i = str.size(); i > 0; i-- )
	{
		if( str[i] == '.' )
			for(i = i - 3; i > 0; i -= 3 )
				str.insert( i, "," );
	}
	return str + currency;
}

template <typename T>
void arrPrint( T* matrix, int rows, int cols )
{
	if ( rows <= 0 || cols <= 0 )
	{
		cout << "Invalid rows or columns submitted.\n";
		return;
	}

	if( rows == 1 )
	{
		for( int i = 0; i < cols; i++ )
			cout << setw( 8 ) << matrix[i];

		cout << "\n";
	}
	else
		for( int i = 0; i < rows; i++ )
		{
			for( int j = 0; j < cols; j++ )
				cout << setw( 8 ) << matrix[i][j];

			cout << "\n";
		}

	return;
}

double slowRound( double num, int precisionLeft, int precisionRight )
{
	int left = num;
	double right = num - left;

	left = _calcLeft( left, precisionLeft );
	right = _calcRight( right, precisionRight );

	return left + right;
}

int _calcLeft( int num, int precision )
{
	int digits = _countDigitsLeft( num );
	int power_10 = pow( 10, digits - precision ) + 0.5;
	double rounder = 0.5;
	for( int i = 1; i < digits - precision; i++ )
		rounder += 0.5 / pow( 10, i );

	num = static_cast<double>( num ) / power_10 + rounder;

	return num;
}
double _calcRight( double num, int precision )
{
	int digits = _countDigitsRight( num );
	int power_10 = pow( 10, precision ) + 0.5;
	double rounder = 0.5;
	for( int i = 1; i < digits - precision; i++ )
		rounder += 0.5 / pow( 10, i );

	num = floor( num * power_10 + rounder ) / power_10;

	return num;
}

int _countDigitsLeft( int num )
{
	int result = 0;

	do
	{
		num /= 10;
		result++;

	}while( num != 0 );

	return result;
}

int _countDigitsRight( double num )
{
	int result = 0;

	ostringstream sstream;
	sstream << num;
	string str = sstream.str();

	for( int i = str.size() - 1; i >= 0; i-- )
	{
		if( str[i] == '.' )
			break;
		result++;
	}

	return result;
}

double fastRound( double num, int precisionLeft, int precisionRight )
{
	int left = num;
	double right = num - left;

	left = _fcalcLeft( left, precisionLeft );
	right = _fcalcRight( right, precisionRight );

	return left + right;
}

int _fcalcLeft( int num, int precision )
{
	int power_10 = pow( 10, precision ) + 0.5;
	double rounder = 0.5;

	num = static_cast<double>( num ) / power_10 + rounder;

	return num;
}

double _fcalcRight( double num, int precision )
{
	int power_10 = pow( 10, precision ) + 0.5;
	double rounder = 0.5;

	num = floor( num * power_10 + rounder ) / power_10;

	return num;
}

struct divResult
{
	int quotient;
	int remainder;
};
divResult divide( int divident, int divisor )
{

}
























#endif /* LIB1_H_ */
