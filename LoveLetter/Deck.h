#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck {
	int isShuffled;
	int totalCards;
	int remainingCards;
	vector<Card*> cardsList;
public:
	Deck(string);

	int getRemainingCards();

	int isEmpty();
	Card* drawCard();
	void printDeck();
	void shuffleDeck();
	void remakeDeck(Card*);
	void remakeDeck(vector<Card*>);

	~Deck();
};