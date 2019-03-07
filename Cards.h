#ifndef CARDS_H
#define CARDS_H
#include <iostream>

using namespace std;

struct cards {
	int value;      // 2 - 14
	char card;      // 2 - A
	char suit;      // c, h, s, or d
	bool known;     // used for holePairs algo
};

#endif
