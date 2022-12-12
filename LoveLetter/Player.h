#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Player {
	string playerName;
	int playerTokens;
	bool playerStatus;
	vector<Card*> playerHand;
	vector<Card*> discardedCards;
public:
	//Constructor area
	Player(string);

	//Getters area
	string getPlayerName();
	bool getPlayerStatus();
	int getPlayerTokens();
	Card* getSpecificCard(int);
	vector<Card*> getDiscardedCards();

	//Setters area
	void setPlayerStatus(bool);

	//Methods area
	void showHand();
	void drawCard(Card*);
	void discardCard(int);
	int getLastCardValue();
	void clearDiscardedCards();
	void giveAffectionTokens(int);

	//Destructor area
	~Player();
};