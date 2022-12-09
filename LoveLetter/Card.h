#pragma once
#include <string>
#include <iostream>

using namespace std;

class Card {
	int cardValue;
	string cardName;
	string cardDescription;
public:
	//Constructor area
	Card(int, string, string);

	//Getters area
	int getCardValue();
	string getCardName();
	string getCardDescription();

	//Methods area
	void printCard();

	//Destructor area
	~Card();
};