
#ifndef HANDS_H
#define HANDS_H
#include "Cards.h"

class hands {
public:
	cards hand[7];      // the Hand
	int array[13];      // to keep track of cards in hand, not suit (for find pairs)
	int score;          // \/
	int val;            // used for comparisons     
	int val2;           // ^
	int h1;
	int h2;
	void analyze();
	void sort();
	int findPairs();
	int isStraight_Flush();
	void add(cards next);
	void replace(cards a, cards b);
	void sho();
	hands();
	hands(cards a, cards b, cards c, cards d, cards e);
};

#endif // Hands.h


