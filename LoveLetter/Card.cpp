#include "Card.h"

Card::Card(int _cardValue, string _cardName, string _cardDescription) : cardValue(_cardValue), cardName(_cardName), cardDescription(_cardDescription) {
}


int Card::getCardValue() { return this->cardValue; }

string Card::getCardName() { return this->cardName; }

string Card::getCardDescription() { return this->cardDescription; }


void Card::printCard() {
	cout << this->cardName << "(" << this->cardValue << "): " << this->cardDescription << endl;
}


Card::~Card() {
}