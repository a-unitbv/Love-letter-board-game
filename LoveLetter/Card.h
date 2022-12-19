#pragma once
#include <string>
#include <iostream>

using namespace std;

class Card {
	int cardValue;
	string cardName;
	string cardDescription;
public:
	Card(int, string, string);

	int getCardValue();
	string getCardName();
	string getCardDescription();

	void printCard();

	~Card();
};