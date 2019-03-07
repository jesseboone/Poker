#include "Game.h"
#include <algorithm>
extern int abv;
extern int blw;
extern int rnd;
extern int knownCards[7];
extern hands myHand;
extern hands other;
extern cards deck[52];

game::game() {
	bigBlind = 0;
	lilBlind = 0;
	ante = 0;
	pot = 0;
	topBet = 0;
	numPlayers = 1;
	numFolded = 0;
	cards bike[52] = {
	{2, '2', 'c', false}, {3, '3', 'c', false}, {4, '4', 'c', false}, {5, '5', 'c', false}, {6, '6', 'c', false}, {7, '7', 'c', false}, {8, '8', 'c', false}, {9, '9', 'c', false}, {10, 'T', 'c', false}, {11, 'J', 'c', false}, {12, 'Q', 'c', false}, {13, 'K', 'c', false}, {14, 'A', 'c', false},
	{2, '2', 'h', false}, {3, '3', 'h', false}, {4, '4', 'h', false}, {5, '5', 'h', false}, {6, '6', 'h', false}, {7, '7', 'h', false}, {8, '8', 'h', false}, {9, '9', 'h', false}, {10, 'T', 'h', false}, {11, 'J', 'h', false}, {12, 'Q', 'h', false}, {13, 'K', 'h', false}, {14, 'A', 'h', false},
	{2, '2', 's', false}, {3, '3', 's', false}, {4, '4', 's', false}, {5, '5', 's', false}, {6, '6', 's', false}, {7, '7', 's', false}, {8, '8', 's', false}, {9, '9', 's', false}, {10, 'T', 's', false}, {11, 'J', 's', false}, {12, 'Q', 's', false}, {13, 'K', 's', false}, {14, 'A', 's', false},
	{2, '2', 'd', false}, {3, '3', 'd', false}, {4, '4', 'd', false}, {5, '5', 'd', false}, {6, '6', 'd', false}, {7, '7', 'd', false}, {8, '8', 'd', false}, {9, '9', 'd', false}, {10, 'T', 'd', false}, {11, 'J', 'd', false}, {12, 'Q', 'd', false}, {13, 'K', 'd', false}, {14, 'A', 'd', false}
	};
	// player* stop = new player;
}

void game::reset() {
	player* p = this->dealer;
	for(int i=0; i<this->numPlayers; i++) {
		p->in = 0;
		p->folded = false;
		// p->bet = 'r';
		p = p->next;
	}
	this->dealer = this->dealer->next;
	this->big = this->big->next;
	this->pot = 0;
	this->topBet = bigBlind;
	this->numFolded = 0;
	// if someone died/numPlayers--;
	rnd = 0;
	this->pot = 0;
	for (int i = 0; i < 4 + rnd; i++) {
		deck[knownCards[i]].known = false;
	}
}

bool game::cpupre() { // could use a where am i function instead, just tell it early middle or late (e, m , l)
	int r=0; int c=0;
	int hole[13][13] = {
	1, 1, 2, 2, 3, 5, 5, 5, 5, 5, 5, 5, 5,
	2, 1, 2, 3, 4, 6, 7, 7, 7, 7, 7, 7, 7,
	3, 4, 1, 3, 4, 5, 7, 9, 9, 9, 9, 9, 9,
	4, 5, 5, 1, 3, 4, 6, 8, 9, 9, 9, 9, 9,
	6, 6, 6, 5, 2, 4, 5, 7, 9, 9, 9, 9, 9,
	8, 8, 8, 7, 7, 3, 4, 5, 8, 9, 9, 9, 9,
	9, 9, 9, 8, 8, 7, 4, 5, 6, 8, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 8, 5, 5, 6, 8, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 8, 6, 7, 7, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9, 8, 6, 6, 7, 9,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 7, 8,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7, 8,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7 };
	if ( (this->cpu->c[0].suit == this->cpu->c[1].suit) && (this->cpu->c[1].value > this->cpu->c[0].value) ) {
			r = 14 - this->cpu->c[1].value; c = 14 - this->cpu->c[0].value;
	}
	else if ( (this->cpu->c[0].suit != this->cpu->c[1].suit) && (this->cpu->c[0].value > this->cpu->c[1].value) ) {
			r = 14 - this->cpu->c[1].value; c = 14 - this->cpu->c[0].value;
	}
	else { c = 14 - this->cpu->c[1].value; r = 14 - this->cpu->c[0].value; }
	
	r = hole[r][c]; c=-1;
	player* p = this->big->next;
	while(p != this->cpu) {p=p->next; c++;}

	if (c<=this->numPlayers/3) c=1;
	else if (c>=this->numPlayers/3*2) c=3;
	else c=2;

	if (r <= 5) return true; // 5 if loose/passive, 4 if tight
	else if ( (r == 6) && (c > 1) ) return true;
	else if ( (r == 7) && (c > 2) ) return true;
	return false;
}

void game::cpuflop() {
	for (int i = 0; i < 5; i++) {
		deck[knownCards[i]].known = true;
	}
	cards c1 = deck[knownCards[0]]; cards c2 = deck[knownCards[1]]; cards c3 = deck[knownCards[2]]; cards c4 = deck[knownCards[3]]; cards c5 = deck[knownCards[4]];
	myHand = hands(c1, c2, c3, c4, c5); // MOVED TO FLOP
	// ANALYZE MY HAND
	myHand.analyze();
	this->cpu->hand = myHand;
	// ANALYZE THE REST TO DECIDE ON ODDS
	int s = myHand.score; int v = myHand.val; int v2 = myHand.val2;
	// cout << s << " & " << v << " & " << v2 << endl;
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
}

void game::cputurn() {
	knownCards[5] = findCard(this->bike[8].card, this->bike[8].suit);
	deck[knownCards[5]].known = true;
	cards c6 = deck[knownCards[5]];  // MOVED TO TURN
	// ANALYZE MY HAND
	myHand.analyze();
	this->cpu->hand = myHand;
	// ANALYZE THE REST TO DECIDE ON ODDS
	int s = myHand.score;
	int v = myHand.val;
	int v2 = myHand.val2;
	// cout << s << " & " << v << " & " << v2 << endl;
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
}

void game::cpuriver() {
	deck[knownCards[6]].known = true;
	cards c7 = deck[knownCards[6]];
	myHand.add(c7); // MOVED TO RIVER
	// ANALYZE MY HAND
	myHand.analyze();
	this->cpu->hand = myHand;
	// ANALYZE THE REST TO DECIDE ON ODDS
	int s = myHand.score;
	int v = myHand.val;
	int v2 = myHand.val2;
	// cout << s << " & " << v << " & " << v2 << endl;
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
}

char game::choose() {
	switch (rnd) {
		case 0:
			if (this->cpu->in == this->topBet) { cout << "CPU will check" << endl; return 'h'; }
			if(cpupre()) { cout << "CPU will call" << endl; return 'c'; }
			else { cout << "CPU will fold" << endl; return 'f'; }
			break;
		case 1:
			cpuflop();
			break;
		case 2:
			cputurn();
			break;
		case 3:
			cpuriver();
			break;
		default:
			break;
	}

	double potOdds = 0.0;
	double myOdds = 0.0;
	int call = this->topBet-this->cpu->in;
	if(call < 0) { cout << "CPU will check" << endl; return 'h'; }
	potOdds = (double)call / ((double)this->pot + (double)call);
	myOdds = ((double)blw) / ((double)abv + (double)blw);
	abv = 0; blw = 0;
	// cout << blw << " & " << abv << endl;
	int r = rand();
	r = r % (rnd+1);
	if (potOdds > myOdds) { cpu->folded = true; cout << "CPU will fold" << endl; return 'f'; }
	else if ( ((potOdds * (1.25 * r)) < myOdds) && (this->topBet != this->cpu->in) ) { cout << "CPU will raise to "; return 'r'; }
	else { cout << "CPU will call" << endl; return 'c'; }
}

void game::bets(player* p) {
	int i = this->numPlayers;
	for (i; i>0; i--) {
		if (this->numPlayers - this->numFolded == 1) { return; } // Stop if everyone else folded
		p = p->next;
		if (!p->folded) {
			if (p == this->cpu) { p->bet = choose(); }
			else {
				cout << "Would " << p->name << " like to fold, check/call, or raise? (f, c, r): ";
				cin >> p->bet;
			}
			switch (p->bet) {
			case 'f':
				this->numFolded++;
				(*p).fold();
				break;
			case 'h':
				break;
			case 'c':
				if(p->in==this->topBet) {break;} // handling check? maybe don't need check now...
				(*p).call(this->topBet, this->pot);
				break;
			case 'r':
				if (p == this->cpu) { this->topBet *= 2; cout << this->topBet << endl; }
				else {
					cout << "To what? (Minimum is " << 2 * this->topBet << ") : ";
					cin >> this->topBet;
				}
				(*p).raise(this->topBet, this->pot);
				break;
			}
			if (p->bet == 'r') { bets(p); i = 0; break; }
		}
	}
	for (i= this->numPlayers; i > 0; i--) {
		p = p->next;
		p->in = 0;
	}

/* 	this->stop = p;
	player* go = p->next;
	this->stop->bet = 'r';
	while (stop->bet == 'r') {
		while (go->folded) { go = go->next; }
		if (this->numPlayers - this->numFolded == 1) { return; } // Stop if everyone folded
		if(go==cpu) {go->bet = choose();}
		else {
			cout << "Would " << go->name << " like to fold, check, call, or raise? (f, h, c, r): ";
			cin >> go->bet;
		}

		switch (go->bet) {
		case 'f':
			go->folded = true;
			this->numFolded++;
			this->pot += go->in;
			go->chipCnt -= go->in;
			go->in = 0;
			break;
		case 'h':
			break;
		case 'c':
			pot += (this->topBet - go->in);
			go->chipCnt -= (this->topBet - go->in);
			go->in = this->topBet;
			break;
		case 'r':
			if (go == cpu) { this->topBet += this->pot*0.25; cout << this->topBet << endl; } // Need to figure out how much to raise by (some formula dependent on odds or percentage/random amount of pot)
			else {
				cout << "To what? (Minimum is " << 2*this->topBet << ") : ";
				cin >> this->topBet; }
			this->pot += this->topBet-go->in;
			go->chipCnt -= this->topBet-go->in;
			go->in = this->topBet;
			stop = go;
			break;
		} 
		go = go->next;
	}
	 */
	this->topBet = 0;
}

void game::pick() {			// SERIOSULY GIVE IT ANOTHER LOOK, WHAT IS IT EVEN DOING?		// ANALYZE THIS MORE CAREFULLY		 // I THINK IT SHOUOLD BE A FOR LOOP INSTEAD
	int h1;
	int h2;				// Need to keep track of last hands h1 & h2 so I can use them later...
	player* win = this->cpu;
	while(win->folded) {win = win->next;}
	h1 = win->hand.h1;
	h2 = win->hand.h2;
	player* p = win->next;
	while(p != win) {
		if (p->folded) { cout << p->name << " folded with: " << p->c[0].card << p->c[0].suit << " & " << p->c[1].card << p->c[1].suit << endl; }
		else {
			//Making and showing hands
			p->hand = this->cpu->hand;
			p->hand.replace(p->c[h1], p->c[h2]);
			p->hand.analyze();
			if (rnd == 3) { cout << p->name << ": "; p->hand.sho(); }

			// Picking winner
			if (p->hand.score > win->hand.score) { win = p; }
			else if (p->hand.score < win->hand.score) { this->pot += p->in; break;}
			else {
				if (p->hand.val > win->hand.val) { win = p; }
				else if (p->hand.val < win->hand.val) { this->pot += p->in; break; }
				else {
					if (p->hand.val2 > win->hand.val2) { win = p; }
					else { this->pot += p->in; break;}
				}
			}

		}
		p = p->next;
	}
	if(rnd==3) {win->hand.sho();}
	// start at first not folded, compare down the line keeping track of highest not folded, give pot to winner
	cout << win->name << " won! Adding pot to their chips" << endl;
	win->chipCnt += this->pot;
}

void game::reveal(player* p) {
	cout << p->name << " has " << p->c[0].card << p->c[0].suit << " " << p->c[1].card << p->c[1].suit << endl;
}

void game::shuffle() {
	random_shuffle(&this->bike[0], &this->bike[52]);
}

int game::findCard(char card, char suit) {
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
}

void game::deal() { // shuffle deck, deal cards to players
	shuffle();
	player* p = this->dealer->next;;
	for(int i=0; i<this->numPlayers; i++) {
		p->c[0] = bike[i];
		p->c[1] = bike[i+this->numPlayers];
		p = p->next;
	}
	knownCards[0] = findCard(this->cpu->c[0].card, this->cpu->c[0].suit);
	knownCards[1] = findCard(this->cpu->c[1].card, this->cpu->c[1].suit);
	// flop turn and river will be fixed numbers every time, so I can just show them and use them after the shuffle
}

void game::preflop() { // MAKE preflop include its own betting round and then call bets for the rest (less cases) (and gives big blind a chance to bet)
	player* p = this->cpu->next;
	while(p != this->cpu) {reveal(p); p=p->next;} // Shows players their cards
	// reveal(this->cpu); // Shows CPUs cards
	bets(this->big);
	if (this->numFolded == this->numPlayers-1) return; // If only one player remains, it returns
	else flop();
}

void game::flop() {
	rnd++;
	knownCards[2] = findCard(this->bike[4].card, this->bike[4].suit);
	knownCards[3] = findCard(this->bike[5].card, this->bike[5].suit);
	knownCards[4] = findCard(this->bike[6].card, this->bike[6].suit);
	/*for (int i = 0; i < 5; i++) {
		deck[knownCards[i]].known = true;
	}
	cards c1 = deck[knownCards[0]]; cards c2 = deck[knownCards[1]]; cards c3 = deck[knownCards[2]]; cards c4 = deck[knownCards[3]]; cards c5 = deck[knownCards[4]];
	myHand = hands(c1, c2, c3, c4, c5);*/
	cout << "Table Cards: " << this->bike[4].card << this->bike[4].suit << " " << this->bike[5].card << this->bike[5].suit << " " << this->bike[6].card << this->bike[6].suit << endl;
	bets(this->dealer);
	if (this->numFolded == this->numPlayers-1) return;
	else turn();
}

void game::turn() {
	rnd++;
	knownCards[5] = findCard(this->bike[8].card, this->bike[8].suit);
	/*deck[knownCards[5]].known = true;
	cards c6 = deck[knownCards[5]];
	myHand.add(c6);*/
	cout << "Table Cards: " << this->bike[4].card << this->bike[4].suit << " " << this->bike[5].card << this->bike[5].suit << " " << this->bike[6].card << this->bike[6].suit << " " << this->bike[8].card << this->bike[8].suit << endl; 
	bets(this->dealer);
	if (this->numFolded == this->numPlayers-1) return;
	else river();
}

void game::river() {
	rnd++;
	knownCards[6] = findCard(this->bike[10].card, this->bike[10].suit);
	/*deck[knownCards[6]].known = true;
	cards c7 = deck[knownCards[6]];
	myHand.add(c7); */
	cout << "Table Cards: " << this->bike[4].card << this->bike[4].suit << " " << this->bike[5].card << this->bike[5].suit << " " << this->bike[6].card << this->bike[6].suit << " " << this->bike[8].card << this->bike[8].suit << " " << this->bike[10].card << this->bike[10].suit << endl; 
	bets(this->dealer);
	return;
}

void game::options() {
	int m = 0;
	while(m!=99) {
		char q = 'y';
		switch (m) {
			case 0:
				cout << "Input the number to " << endl;
				cout << "1. Set starting chips" << endl;
				cout << "2. Set blinds" << endl;
				cout << "3. Set antes" << endl;
				cout << "4. Add cpu as dealer" << endl;
				cout << "5. Add players" << endl;
				// cout << "6. Remove players" << endl;
				cout << "99. Return to game" << endl;
				break;
			case 1:
				cout << "How much is each player starting with? ";
				cin >> this->pot; // just using pot to hold chipCnt
				break;
			case 2:
				cout << "What will big and lil blinds be? ";
				cin >> this->bigBlind >> this->lilBlind;
				this->topBet = bigBlind;
				break;
			case 3:
				cout << "What will the ante be? ";
				cin >> this->ante;
				break;
			case 4:
				cout << "Adding cpu" << endl;
				this->cpu = new player("CPU", this->pot);
				this->dealer = this->cpu;
				break;
			case 5:
				while(q!='n') {
					this->numPlayers++;
					string n;
					cout << "What is his or her name? ";
					cin >> n;
					player* p = new player(n, this->pot);
					player* put = this->cpu;
					while(put->next != NULL) { put = put->next; }
					put->next = p;
					this->stop = p;
					if (this->numPlayers == 2) { this->dealer->next = p; }
					cout << "Add another player? ";
					cin >> q;
				}
				break;
			case 6:
				cout << "Maybe eventually this will remove players" << endl;
				break;
			case 7:
				cout << "Maybe eventually this will change rand seeds" << endl;
				break;
			default:
				break;
		}
		cout << ": ";
		cin >> m;
	}
	this->pot = 0;
	this->stop->next = this->dealer;
	this->big = this->dealer->next->next;
	return;
}

void game::show() {
	if(this->ante == 0) { cout << "Big & Lil Blinds: " << this->bigBlind << " & " << this->lilBlind << endl; }
	else {cout << "Ante is: " << this->ante << endl;} 

	cout << "Number of players is: " << this->numPlayers << endl;
	cout << "Dealer is: " << this->dealer->name << endl;
	cout << "Big Blind is: " << this->big->name << endl;
	// Maybe show players and their chips too?
}

void game::show2() {
	player* p = this->cpu;
	for(int i=0; i<this->numPlayers; i++) {
		cout << p->name << " has " << p->chipCnt << endl;
		p = p->next;
	}
}


