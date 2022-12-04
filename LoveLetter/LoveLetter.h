#pragma once
#include "Player.h"
#include "Deck.h"

#include <vector>

using namespace std;

class LoveLetter {
	Deck* deck;
	vector<Player*> players;
	int affectionTokensTarget;
	int game;
	int round;
	int turn;
public:
	LoveLetter(string);

	void addPlayer(Player*);
	void printGameStatus();
	void startGame();
};
