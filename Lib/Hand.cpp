#include "Hand.h"

#include <algorithm>

Hand::Hand()
{
}

Hand::Hand( Card* arr )
{
	for( int i = 0; i < 5; i++ )
		hand[ i ] = arr[ i ];
	sortHand();
}

Hand::~Hand()
{
}

Strength Hand::eval()
{
	int result = 8;
	Strength st;
	do
	{
		st = static_cast< Strength > ( result );

		switch( st )
		{
		case STRAIGHT_FLUSH:
			if( has_straight_flush() )
				return st;
			break;
		case FOUR_OF_A_KIND:
			if( has_fours() )
				return st;
			break;
		case FULL_HOUSE:
			if( has_full() )
				return st;
			break;
		case FLUSH:
			if( has_flush() )
				return st;
			break;
		case STRAIGHT:
			if( has_straight() )
				return st;
			break;
		case THREE_OF_A_KIND:
			if( has_threes() )
				return st;
			break;
		case TWO_PAIR:
			if( has_2pairs() )
				return st;
			break;
		case PAIR:
			if( has_pair() )
				return st;
			break;
		case HIGH_CARD:
			return st;
		}

		result--;
	}while( st >= HIGH_CARD );

	return st;
}

bool Hand::has_straight_flush()
{
	if( has_straight() && has_flush() )
		return true;
	return false;
}

bool Hand::has_fours()
{
	if( fours() != ZERO )
		return true;
	return false;
}

bool Hand::has_full()
{
	if( has_threes() && pair( threes() ) != ZERO )
		return true;
	return false;
}

bool Hand::has_flush()
{
	if( flush() != NONE )
		return true;
	return false;
}

bool Hand::has_straight()
{
	if( straight() != ZERO )
		return true;
	return false;
}

bool Hand::has_threes()
{
	if( threes() != ZERO )
		return true;
	return false;
}

bool Hand::has_2pairs()
{
	if( pair() != ZERO && pair( pair() ) != ZERO )
		return true;
	return false;
}

bool Hand::has_pair()
{
	if( pair() != ZERO )
		return true;
	return false;
}

bool Hand::cardSortAsc( Card card1, Card card2 )
{
	return card1.val < card2.val;
}

void Hand::sortHand()
{
	std::sort( hand, hand + 5, cardSortAsc );
}

Value Hand::highCard()
{
	return hand[ 4 ].val;
}

Value Hand::pair( Value exception )
{
	for( int i = 1; i < 5; i++ )
		if( hand[ i ].val != exception
		 && hand[ i ].val == hand[ i - 1 ].val )
				return hand[ i ].val;
	return ZERO;
}

Value Hand::threes()
{
	for( int i = 2; i < 5; i++ )
		if( hand[ i ].val == hand[ i - 1 ].val
		 && hand[ i ].val == hand[ i - 2 ].val )
				return hand[ i ].val;
	return ZERO;
}

Value Hand::straight()
{
	for( int i = 1; i < 5; i++ )
		if( hand[ i ].val - hand[ i - 1 ].val != 1 )
			return ZERO;
	return hand[ 4 ].val;
}

Suit Hand::flush()
{
	for( int i = 1; i < 5; i++ )
		if( hand[ i ].suit != hand[ i - 1 ].suit )
			return NONE;
	return hand[ 4 ].suit;
}

Value Hand::fours()
{
	for( int i = 3; i < 5; i++ )
		if( hand[ i ].val == hand[ i - 1 ].val
		 && hand[ i ].val == hand[ i - 2 ].val
		 && hand[ i ].val == hand[ i - 3 ].val )
				return hand[ i ].val;
	return ZERO;
}
