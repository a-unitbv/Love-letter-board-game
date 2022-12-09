#include "Card.h"

//Constructor area
Card::Card(int _cardValue, string _cardName, string _cardDescription) : cardValue(_cardValue), cardName(_cardName), cardDescription(_cardDescription){
}

//Getters area
int Card::getCardValue() { return this->cardValue; }

string Card::getCardName() { return this->cardName; }

string Card::getCardDescription() { return this->cardDescription; }

//Methods area
void Card::printCard() {
	cout << this->cardName << "(" << this->cardValue << "): " << this->cardDescription << endl;
}

//Destrucotor area
Card::~Card() {
}