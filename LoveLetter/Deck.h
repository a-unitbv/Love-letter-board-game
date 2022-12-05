#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck {
	int totalCards;
	int remainingCards;
	int isShuffled;
	vector<Card*> cardsList;
public:
	Deck(string);

	int getRemainingCards();

	Card* drawCard();
	int isEmpty();
	void shuffleDeck();
	void printDeck();
};