#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Player {
	string playerName;
	int playerTokens;
	bool playerStatus;
	bool playerProtection;
	vector<Card*> playerHand;
	vector<Card*> discardedCards;
public:
	Player(string);

	string getPlayerName();
	bool getPlayerStatus();
	int getPlayerTokens();
	bool getPlayerProtection();
	Card* getSpecificCard(int);
	vector<Card*> getDiscardedCards();

	void setPlayerStatus(bool);
	void setPlayerProtection(bool);

	void showHand();
	void drawCard(Card*);
	void discardCard(int);
	int getLastCardValue();
	void clearDiscardedCards();
	void giveAffectionTokens(int);

	~Player();
};