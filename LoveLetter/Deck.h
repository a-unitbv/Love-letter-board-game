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
	//Constructor area
	Deck(string);

	//Getters area
	int getRemainingCards();

	//Methods area
	int isEmpty();
	Card* drawCard();
	void printDeck();
	void shuffleDeck();
	void remakeDeck(vector<Card*>);

	//Destructor area
	~Deck();
};