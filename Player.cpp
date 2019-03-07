#include "Player.h"

player::player(string n, int c) {
    name = n;    
	chipCnt = c; 
    in = 0;
	folded = false; 
    alive = true;
    allin = false;
}

void player::fold() {
	this->folded = true;
	return;
}

void player::call(int &tB, int &p) {
	p += (tB - this->in);
	this->chipCnt -= (tB - this->in);
	this->in = tB;
	return;
}

void player::raise(int &tB, int &p) {
	p += abs(in - tB);
	this->chipCnt -= abs(in - tB);
	this->in = tB;
	return;
}

