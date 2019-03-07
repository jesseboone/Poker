#include <iostream>
#include <String>
#include "Cards.h"
#include "Hands.h"
#include "Player.h"
#include "Game.h"


using namespace std;
// srand(8);				 	// COULD MAKE THIS TIME LATER

//GLOBALS
int rnd = 0;
// player* cpu; 				I PUT THIS IN GAME CLASS
int knownCards[7] = { 0 };
int abv = 0;
int blw = 0;
// int myChips = 0;
hands myHand;
hands other;
cards deck[52] = {
{2, '2', 'c', false}, {3, '3', 'c', false}, {4, '4', 'c', false}, {5, '5', 'c', false}, {6, '6', 'c', false}, {7, '7', 'c', false}, {8, '8', 'c', false}, {9, '9', 'c', false}, {10, 'T', 'c', false}, {11, 'J', 'c', false}, {12, 'Q', 'c', false}, {13, 'K', 'c', false}, {14, 'A', 'c', false},
{2, '2', 'h', false}, {3, '3', 'h', false}, {4, '4', 'h', false}, {5, '5', 'h', false}, {6, '6', 'h', false}, {7, '7', 'h', false}, {8, '8', 'h', false}, {9, '9', 'h', false}, {10, 'T', 'h', false}, {11, 'J', 'h', false}, {12, 'Q', 'h', false}, {13, 'K', 'h', false}, {14, 'A', 'h', false},
{2, '2', 's', false}, {3, '3', 's', false}, {4, '4', 's', false}, {5, '5', 's', false}, {6, '6', 's', false}, {7, '7', 's', false}, {8, '8', 's', false}, {9, '9', 's', false}, {10, 'T', 's', false}, {11, 'J', 's', false}, {12, 'Q', 's', false}, {13, 'K', 's', false}, {14, 'A', 's', false},
{2, '2', 'd', false}, {3, '3', 'd', false}, {4, '4', 'd', false}, {5, '5', 'd', false}, {6, '6', 'd', false}, {7, '7', 'd', false}, {8, '8', 'd', false}, {9, '9', 'd', false}, {10, 'T', 'd', false}, {11, 'J', 'd', false}, {12, 'Q', 'd', false}, {13, 'K', 'd', false}, {14, 'A', 'd', false}
};

/* void decide() {
	double potOdds = 0.0;
	double myOdds = 0.0;
	int pot;
	int call;
	cout << "What is in the pot?" << endl;
	cin >> pot;
	cout << "What do I need to call?" << endl;
	cin >> call;
	potOdds = (double)call / ( (double)pot + (double)call );
	myOdds = ((double)blw) / ( (double)abv + (double)blw );
	cout << blw << " & " << abv << endl;
	int r = rand(); 
	r = r % (rnd) + 1; 
	if (potOdds > myOdds) { folded = true; cout << "I fold" << endl; return; }
	else if ( (potOdds * (1.25 * r) ) < myOdds) { cout << "I will raise" << endl; return; }
	else cout << "I will call" << endl;
	return;
} */

/* // rnd 3
void river() { // RETURN CHANCES OF BEST HAND AVAILABLE WINNING AND IF ITS WORTH IT TO STAY IN BASED ON BLINDS/ANTES/OTHER POSSIBLE HANDS
	deck[knownCards[6]].known = true;
	cards c7 = deck[knownCards[6]];
	myHand.add(c7);
	// ANALYZE MY HAND
	myHand.analyze();
	// ANALYZE THE REST TO DECIDE ON ODDS
	int s = myHand.score;
	int v = myHand.val;
	int v2 = myHand.val2;
	cout << s << " & " << v << " & " << v2 << endl;
	other = myHand;
	for (int i = 0; i < 51; i++) {
		for (int j = i + 1; j < 52; j++) {
			if (!(deck[i].known) && !(deck[j].known)) { // If cards haven't been seen yet
				other.replace(deck[i], deck[j]); // Swapping next pair of hole cards to hand
				other.analyze(); // Analyze new hand
				// Adjust scores of abv/blw
				if (other.score > s) { abv++; }
				else if (other.score < s) { blw++; }
				else {
					if (other.val > v) { abv++; }
					else if (other.val < v) { blw++; }
					else {
						if (other.val2 > v2) { abv++; }
						else if (other.val2 < v2) { blw++; }
						else blw++;
					}
				}

			}
		}
	}
	rnd++;
	decide();
	// RETURN CALL, RAISE OR FOLD
}

// rnd 2
void turn() { // RETURN CHANCES OF BEST HAND AVAILABLE WINNING AND IF ITS WORTH IT TO STAY IN BASED ON BLINDS/ANTES/OTHER POSSIBLE HANDS
	deck[knownCards[5]].known = true;
	cards c6 = deck[knownCards[5]];
	myHand.add(c6);
	// ANALYZE MY HAND
	myHand.analyze();
	// ANALYZE THE REST TO DECIDE ON ODDS
	int s = myHand.score;
	int v = myHand.val;
	int v2 = myHand.val2;
	cout << s << " & " << v << " & " << v2 << endl;
	other = myHand;
	for (int i = 0; i < 51; i++) {
		for (int j = i + 1; j < 52; j++) {
			if (!(deck[i].known) && !(deck[j].known)) { // If cards haven't been seen yet
				other.replace(deck[i], deck[j]); // Swapping next pair of hole cards to hand
				other.analyze(); // Analyze new hand
				// Adjust scores of abv/blw
				if (other.score > s) { abv++; }
				else if (other.score < s) { blw++; }
				else {
					if (other.val > v) { abv++; }
					else if (other.val < v) { blw++; }
					else {
						if (other.val2 > v2) { abv++; }
						else if (other.val2 < v2) { blw++; }
						else blw++;
					}
				}

			}
		}
	}
	rnd++;
	decide();
	// RETURN CALL, RAISE OR FOLD
}

// rnd 1
void flop() { // RETURN CHANCES OF THIS HAND WINNING AND IF ITS WORTH IT TO STAY IN BASED ON BLINDS/ANTES/OTHER POSSIBLE HANDS
	for (int i = 0; i < 5; i++) {
		deck[knownCards[i]].known = true;
	}
	cards c1 = deck[knownCards[0]]; cards c2 = deck[knownCards[1]]; cards c3 = deck[knownCards[2]]; cards c4 = deck[knownCards[3]]; cards c5 = deck[knownCards[4]];
	myHand = hands(c1, c2, c3, c4, c5);
	// ANALYZE MY HAND
	myHand.analyze();
	// ANALYZE THE REST TO DECIDE ON ODDS
	int s = myHand.score;
	int v = myHand.val;
	int v2 = myHand.val2;
	cout << s << " & " << v << " & " << v2 << endl;
	other = myHand;
	for (int i = 0; i < 51; i++) {
		for (int j = i + 1; j < 52; j++) {
			if (!(deck[i].known) && !(deck[j].known)) { // If cards haven't been seen yet
				other.replace(deck[i], deck[j]); // Swapping next pair of hole cards to hand
				other.analyze(); // Analyze new hand
				// Adjust scores of abv/blw
				if (other.score > s) { abv++; }
				else if (other.score < s) { blw++; }
				else {
					if (other.val > v) { abv++; }
					else if (other.val < v) { blw++; }
					else {
						if (other.val2 > v2) { abv++; }
						else if (other.val2 < v2) { blw++; }
						else blw++;
					}
				}

			}
		}
	}
	rnd++;
	decide();
	// CALL, RAISE OR FOLD & RETURN
}

// rnd 0
void pre(char c1, char s1, char c2, char s2) { // RETURN CHANCES OF THESE TWO CARDS WINNING AND IF ITS WORTH IT TO STAY IN BASED ON BLINDS/ANTES (OR JUST READ 2D MATRIX)
	// ANALYZE MY HAND VS REST BASED ON MATRIX

	// if good enough, stay in and add myCards to hand, else fold
	rnd++;
	// RETURN CALL, RAISE, OR FOLD
} */

/* int findCard(char card, char suit) {
	int c = 0;
	switch (card) {
	case 'T':
	case 't':
		c = 10;
		break;
	case 'J':
	case 'j':
		c = 11;
		break;
	case 'Q':
	case 'q':
		c = 12;
		break;
	case 'K':
	case 'k':
		c = 13;
		break;
	case 'A':
	case 'a':
		c = 14;
		break;
	default:
		c = card - '0';
	}
	c -= 2;
	switch (suit) {
	case 'C':
	case 'c':
		return c;
		break;
	case 'H':
	case 'h':
		return c + 13;
		break;
	case 'S':
	case 's':
		return c + 26;
		break;
	case 'D':
	case 'd':
		return c + 39;
		break;
	}
	return c;
} */

/* void reset(bool folded) {
	if (!folded) {
		abv = 0;
		blw = 0;
	}
	else {
		abv = 0;
		blw = 0;
		rnd = 0;
		for (int i = 0; i < 4 + rnd; i++) {
			deck[knownCards[i]].known = false;
		}
	}
} */

int main(int argc, char const *argv[]) {

	// DO I NEED TO BUILD THE GAME? #ofPLAYERS, AMNT STARTING WITH, BLINDS ETC? Could be a ring linked list and have pointers to big and little blind...
	// PERHAPS I JUST NEED MORE OF A MENU SETUP TO ALTER GAME SETTINGS, PLAYERS, MONEY ETC...
	game g = game();
	cout << "Beginning setup, going to menu" << endl;
	char q = 'n';
	while (q!='y') {
		g.options();
		g.show();
		cout << "Are you satisfied with these settings?" << endl;
		cin >> q;
	}
	// int count = 0;
	while(g.numPlayers > 1) { // while(at least 2 players are alive (or numPlayers is > 1)) {}
		g.shuffle();
		g.deal();
		cout << "Shuffled & dealt" << endl;
		g.pot = g.bigBlind + g.lilBlind;
		g.big->in = g.bigBlind;
		g.big->chipCnt -= g.bigBlind;
		g.dealer->next->in = g.lilBlind;
		g.dealer->next->chipCnt -= g.lilBlind;
		cout << "Blinds in" << endl;
		g.preflop();

		g.pick();
		g.reset();
		g.show2();
		cout << endl;
		// count++;
		// if (count == 5) {count=0; g.show2();}
		// g.reset(); ?
	}

	// Now I need to show my cards, make my decision, and let CPU make its decision...
	// Then move on to next round and next... then repeat until one of us is no longer alive
	// Maybe show chipCnts between every few rounds or so?



	/* while (alive) {
		char card1; char suit1; char card2; char suit2;
		cout << "Enter my hole cards like this '9 h' & 'T s':" << endl;
		cin >> card1 >> suit1 >> card2 >> suit2;
		if( (card1 == 'm') && (suit1 == 'e') && (card2 == 'n') + (suit2 == 'u') ) {
			
		}
		// IF 'MENU' GO TO MENU OPTIONS
		knownCards[0] = findCard(card1, suit1);
		knownCards[1] = findCard(card2, suit2);
		// pre(knownCards[0], knownCards[1]);
		rnd++; // ^^^ GET RID OF THIS AFTER ACTIVATING ABOVE ^^^

		if (!folded) { // FLOP
			char fc[3]; char fs[3];
			cout << "What was in the flop?" << endl;
			cin >> fc[0] >> fs[0] >> fc[1] >> fs[1] >> fc[2] >> fs[2];
			knownCards[2] = findCard(fc[0], fs[0]);
			knownCards[3] = findCard(fc[1], fs[1]);
			knownCards[4] = findCard(fc[2], fs[2]);

			flop();
			reset(folded);
		}
		if (!folded) { // TURN
			cout << "What was in the turn?" << endl;
			cin >> card1 >> suit1;
			knownCards[5] = findCard(card1, suit1);

			turn();
			reset(folded);
		}
		if (!folded) { // RIVER
			cout << "What was in the river?" << endl;
			cin >> card2 >> suit2;
			knownCards[6] = findCard(card2, suit2);

			river();
			reset(folded);
		}
		folded = false;
	} */
	return 0;
}


// 
//
//
//

// ---------------------------------------------------------------------------------------------------------------


			// QUESTIONS
	// DO I NEED TO PUT EVERYTHING INTO THE GAME CLASS? Well I am now
	// 

// ---------------------------------------------------------------------------------------------------------------


			// TO DO LIST
// FIGURE OUT DECIDE FUNCTION...WHAT HAPPENS IF PLAYERS CHECK ETC... ALSO COULD JUST RAISE IF MY HAND IMPROVES...
// ADD PLAYERS AND MAYBE KEEP TRACK OF HISTORY
// ADD MENU FOR GAME CONTROLS...SWITCH STATEMENTS GALORE??
	// changing blinds, buy ins, maybe change multiplier (secret)? Fix game stats...(chips/folded/etc)
// ADD ERROR HANDLING FOR INCORRECT CARD INPUT (SAME CARD/WRONG SUITS/ETC)
// MAKE TESTING SCRIPT TO MAKE SURE IT WORKS, and HAVE IT PLAY GAMES AGAINST OTHERS AND SEE IF IT WINS
// DECIDE COULD BE BETTER BUT I THINK FOR NOW IT IS GOOD
// ANYTHING ELSE? yes

// Preflop own betting round? (Will this fix the problems?)
// Might just need to completely revamp betting, with better variables and such
// raises have to be double the previous

// MAYBE MAKE F, H, C, R PLAYER FUNCTIONS, AND RUN A RECURSIVE-ISH FOR LOOP FOR THE BETTING ROUND...?
// NEED TO ADD TIE CAUSES SPLIT POT

// 1 1000 2 100 50 4 5 JPB n 99 y