#pragma once
#include <string>
#include <iostream>

using namespace std;

class Card {
	string cardName;
	int cardValue;
	string cardDescription;
public:
	Card(string, int, string);

	string getCardName();
	int getCardValue();
	string getCardDescription();

	void printCard();
};