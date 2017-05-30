#ifndef HAND_H_
#define HAND_H_

enum Suit { NONE, CLUBS, DIAMONDS, HEARTS, SPADES };
enum Value { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
enum Strength { HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH };

class Hand
{
public:
	struct Card
	{
		Suit suit;
		Value val;
	};
public:
	Hand();
	Hand( Card* );
	~Hand();
public:
	Strength eval();
	bool has_straight_flush();
	bool has_fours();
	bool has_full();
	bool has_flush();
	bool has_straight();
	bool has_threes();
	bool has_2pairs();
	bool has_pair();
private:
	static bool cardSortAsc( Card, Card );
	void sortHand();
	Value highCard();
	Value pair( Value = ZERO );
	Value threes();
	Value straight();
	Suit flush();
	Value fours();
private:
	Card hand[5];
};

#endif /* HAND_H_ */
