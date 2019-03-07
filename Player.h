#ifndef PLAYER_H
#define PLAYER_H
#include <String>
#include "Hands.h"


class player {
public:
	string name;
	int chipCnt;
	int in;
	player* next;
	char bet; // f, c, r
	// TEMPORARILY
	cards c[2];
	// or
	hands hand;
	bool allin; // ???
	bool folded;
	bool alive;
	player(string n, int c);
	void fold();
	void call(int &tB, int &p);
	void raise(int &tB, int &p);
};

#endif
