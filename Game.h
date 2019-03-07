#ifndef GAME_H
#define GAME_H
#include "Player.h"

class game {
public:
	player* cpu;
	player* dealer;
	player* big;
	player* stop;
	int numPlayers;
	int numFolded;
	int bigBlind;
	int lilBlind;
	int ante;
	int pot;
	int topBet;
	cards bike[52] = {
	{2, '2', 'c', false}, {3, '3', 'c', false}, {4, '4', 'c', false}, {5, '5', 'c', false}, {6, '6', 'c', false}, {7, '7', 'c', false}, {8, '8', 'c', false}, {9, '9', 'c', false}, {10, 'T', 'c', false}, {11, 'J', 'c', false}, {12, 'Q', 'c', false}, {13, 'K', 'c', false}, {14, 'A', 'c', false},
	{2, '2', 'h', false}, {3, '3', 'h', false}, {4, '4', 'h', false}, {5, '5', 'h', false}, {6, '6', 'h', false}, {7, '7', 'h', false}, {8, '8', 'h', false}, {9, '9', 'h', false}, {10, 'T', 'h', false}, {11, 'J', 'h', false}, {12, 'Q', 'h', false}, {13, 'K', 'h', false}, {14, 'A', 'h', false},
	{2, '2', 's', false}, {3, '3', 's', false}, {4, '4', 's', false}, {5, '5', 's', false}, {6, '6', 's', false}, {7, '7', 's', false}, {8, '8', 's', false}, {9, '9', 's', false}, {10, 'T', 's', false}, {11, 'J', 's', false}, {12, 'Q', 's', false}, {13, 'K', 's', false}, {14, 'A', 's', false},
	{2, '2', 'd', false}, {3, '3', 'd', false}, {4, '4', 'd', false}, {5, '5', 'd', false}, {6, '6', 'd', false}, {7, '7', 'd', false}, {8, '8', 'd', false}, {9, '9', 'd', false}, {10, 'T', 'd', false}, {11, 'J', 'd', false}, {12, 'Q', 'd', false}, {13, 'K', 'd', false}, {14, 'A', 'd', false}
	};
	game();
	void reset();
	bool cpupre();
	void cpuflop();
	void cputurn();
	void cpuriver();
	char choose();				// Cpu decision query
	void bets(player* p); 		// Run betting rounds
	void pick(); 				// Decide on winner
	void reveal(player* p);
	void preflop();
	void flop();
	void turn();
	void river();
	void shuffle();				// 3 guesses, first 2 don't count
	int findCard(char card, char suit);
	void deal(); 				// Give each player 2 cards...
	void options();				// Edit game variables
	void show();				// Print game variables
	void show2();				// Print player stats
	// void play();
	
};

#endif
