#include "Hands.h"
extern int rnd;

hands::hands() {
}

hands::hands(cards a, cards b, cards c, cards d, cards e) {
	hand[0] = a;
	hand[1] = b;
	hand[2] = c;
	hand[3] = d;
	hand[4] = e;
	for (int i = 0; i < 13; i++) {
		array[i] = 0;
	}
	for (int i = 0; i < 5; i++) {  // initializing array
		array[hand[i].value - 2]++;
	}
	score = 0;
	val = 0;
	val2 = 0;
	h1 = 0;
	h2 = 1;
	// cout << h1->card << " of " << h1->suit << endl;
}

void hands::sort() { // bubble sort 
	int i, j;
	for (i = 0; i < 4 + rnd; i++) {     // Last i elements are already in place    
		for (j = 0; j < 4 + rnd - i - 1; j++) {
			if (this->hand[j].value > this->hand[j + 1].value) {
				cards swap = this->hand[j];
				this->hand[j] = this->hand[j + 1];
				this->hand[j + 1] = swap;
				if (j == h1) { h1 = j + 1; }
				else if (j + 1 == h1) { h1 = j; }
				if (j == h2) { h2 = j + 1; }
				else if (j + 1 == h2) { h2 = j; }
			}
		}
	}
}

void hands::analyze() {
	sort();
	int fP = findPairs();
	if (fP > 4) { return; }
	int sF = isStraight_Flush();
	if ((fP == 0) && (sF == 0)) {
		this->score = 1; this->val = this->hand[3 + rnd].value; this->val2 = this->hand[2 + rnd].value;
	} //highCard = true; this->score=1; this->val=this->hand[3+rnd]}
	return;
}

void hands::replace(cards a, cards b) { // NEED TO REPLACE HOLE CARDS...NOT NECESSARILY THE FRONT TWO...
	this->array[hand[h1].value - 2]--;
	this->array[hand[h2].value - 2]--;
	hand[h1] = a;
	hand[h2] = b;
	this->array[a.value - 2]++;
	this->array[b.value - 2]++;
	this->score = 0;
	this->val = 0;
	this->val2 = 0;
	return;
}

void hands::add(cards next) {
	this->hand[3 + rnd] = next;
	this->array[this->hand[3 + rnd].value - 2]++;
	return;
}

int hands::isStraight_Flush() {
	int c[8] = { 0 }; int h[8] = { 0 };	int s[8] = { 0 };	int d[8] = { 0 };
	for (int i = 0; i < 4 + rnd; i++) {
		switch (this->hand[i].suit) {
		case 'c':
			c[c[7]] = this->hand[i].value;
			c[7]++;
			break;
		case 'h':
			h[h[7]] = this->hand[i].value;
			h[7]++;
			break;
		case 's':
			s[s[7]] = this->hand[i].value;
			s[7]++;
			break;
		case 'd':
			d[d[7]] = this->hand[i].value;
			d[7]++;
			break;
		}
	}
	// Checking for flush and if so, checking for straight flush
	if (c[4] > 0) {
		c[7] -= 4;
		for (int i = 0; i < c[7];i++) {
			int str = 0;
			for (int j = i;j < 4 + i;j++) {
				if (c[j] == c[j + 1] - 1) str++;
				else break;
			}
			if (str == 4) {
				// is straight flush
				this->score = 9;
				if (this->hand[h2].suit == 'c') this->val = this->hand[h2].value;
				if (this->hand[h1].suit == 'c') this->val2 = this->hand[h1].value;
				return 9;
			}
		}
		this->score = 6; // is flush
		if (this->hand[h2].suit == 'c') this->val = this->hand[h2].value;
		if (this->hand[h1].suit == 'c') this->val2 = this->hand[h1].value;
		return 6;
	}
	else if (h[4] > 0) {
		h[7] -= 4;
		for (int i = 0; i < h[7];i++) {
			int str = 0;
			for (int j = i;j < 4 + i;j++) {
				if (h[j] == h[j + 1] - 1) str++;
				else break;
			}
			if (str == 4) {
				// is straight flush
				this->score = 9;
				if (this->hand[h2].suit == 'h') this->val = this->hand[h2].value;
				if (this->hand[h1].suit == 'h') this->val2 = this->hand[h1].value;
				return 9;
			}
		}
		this->score = 6; // is flush
		if (this->hand[h2].suit == 'h') this->val = this->hand[h2].value;
		if (this->hand[h1].suit == 'h') this->val2 = this->hand[h1].value;
		return 6;
	}
	else if (s[4] > 0) {
		s[7] -= 4;
		for (int i = 0; i < s[7];i++) {
			int str = 0;
			for (int j = i;j < 4 + i;j++) {
				if (s[j] == s[j + 1] - 1) str++;
				else break;
			}
			if (str == 4) {
				// is straight flush
				this->score = 9;
				if (this->hand[h2].suit == 's') this->val = this->hand[h2].value;
				if (this->hand[h1].suit == 's') this->val2 = this->hand[h1].value;
				return 9;
			}
		}
		this->score = 6; // is flush
		if (this->hand[h2].suit == 's') this->val = this->hand[h2].value;
		if (this->hand[h1].suit == 's') this->val2 = this->hand[h1].value;
		return 6;
	}
	else if (d[4] > 0) {
		d[7] -= 4;
		for (int i = 0; i < d[7];i++) {
			int str = 0;
			for (int j = i;j < 4 + i;j++) {
				if (d[j] == d[j + 1] - 1) str++;
				else break;
			}
			if (str == 4) {
				// is straight flush
				this->score = 9;
				if (this->hand[h2].suit == 'd') this->val = this->hand[h2].value;
				if (this->hand[h1].suit == 'd') this->val2 = this->hand[h1].value;
				return 9;
			}
		}
		this->score = 6; // is flush
		if (this->hand[h2].suit == 'd') this->val = this->hand[h2].value;
		if (this->hand[h1].suit == 'd') this->val2 = this->hand[h1].value;
		return 6;
	}
	// Flush failed...looking for straight

	int i = this->hand[3 + rnd].value - 2;
	int str = 1;
	while (i > this->hand[0].value - 2) {
		i--;
		if (this->array[i] > 0) { str++; }
		else if (str > 2) return false;
		else str = 0;
	}
	if (str >= 5) { //has straight
		this->score = 5;
		this->val = i + str + 1;
		this->val2 = 0;
		return 5;
	}
	else return 0; // no straight
}

int hands::findPairs() {
	int a = 0;
	int b = 0;
	int c = 0;
	for (int i = this->hand[3 + rnd].value - 2; i >= this->hand[0].value - 2; i--) {
		if (this->array[i] == 3) { if (c == 0) c = i + 2; else if (a == 0) a = i + 2; }
		else if (this->array[i] == 2) { if (a == 0) a = i + 2; else if (b == 0) b = i + 2; }
		else if (this->array[i] == 4) { this->score = 8; this->val = i + 2; return 4; } // 4 OF A KIND
	}
	if (c != 0) {
		if (a != 0) { this->score = 7; this->val = c; this->val2 = a; return 5; } // FULL HOUSE
		else { this->score = 4; this->val = c; this->val2 = a; return 3; } // 3 OF A KIND
	}
	else if (b != 0) { this->score = 3; this->val = a; this->val2 = b; return 2; } // TWO PAIR
	else if (a != 0) { this->score = 2; this->val = a; return 1; } // ONE PAIR
	else return 0; // NONE
}

void hands::sho() {
		for (int i = 0; i < 7; i++) {
			cout << this->hand[i].card << this->hand[i].suit << " ";
		}
		cout << endl << this->score << " " << this->val << " " << this->val2 << endl;
}