#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Player {
	string playerName;
	vector<Card*> playerHand;
	int playerTokens;
	bool playerStatus;
public:
	Player(string);

	void draw(Card*);
	void discard(int);
	void show();
};