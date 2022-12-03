#include "Card.h"

Card::Card(string _cardName, int _cardValue, string _cardDescription) : cardName(_cardName), cardValue(_cardValue), cardDescription(_cardDescription){
}

string Card::getCardName() { return this->cardName; }

int Card::getCardValue() { return this->cardValue; }

string Card::getCardDescription() { return this->cardDescription; }

void Card::printCard() {
	cout << this->cardName << "(" << this->cardValue << "): " << this->cardDescription << endl;
}