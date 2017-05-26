#include "RandomQueue.h"
#include <algorithm>

RandomQueue::RandomQueue()
{
	arr = 0;
	size = length = 0;
}

RandomQueue::~RandomQueue()
{
	delete[] arr;
	arr = 0;
	size = length = 0;
}

void RandomQueue::addElement( int elem )
{
	if( length == size )
		expandArr();

	arr[ length ] = elem;
	length++;
	shuffleArr(arr, length);
}

int RandomQueue::removeElement()
{
	if( length == 0 )
		return 0;

	length--;
	return arr[ length ];
}

void RandomQueue::expandArr()
{
	int* newArr = new int[ size + 10 ];

	for( int i = 0; i < size; i++ )
		newArr[i] = arr[i];

	delete[] arr;
	arr = newArr;
	size += 10;
}

void RandomQueue::shuffleArr( int* arr, int size )
{
	std::random_shuffle( arr, arr + size );
}

























