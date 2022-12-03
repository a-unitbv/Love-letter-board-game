#include "Deck.h"

Deck::Deck(string filename) : totalCards(16), remainingCards(16), isShuffled(0) {
	ifstream fileIn(filename);

	int linesNumber;

	string cardName;
	int cardValue;
	string cardDescription;
	int cardDuplicates;

	fileIn >> linesNumber;

	for (int i = 0; i < linesNumber; i++) {
		fileIn >> cardValue >> cardName >> cardDuplicates;
		fileIn.seekg(1, ios::cur);
		getline(fileIn, cardDescription);
		
		for (int j = 0; j < cardDuplicates; j++) {
			this->cardsList.push_back(new Card(cardName, cardValue, cardDescription));
		}
	}
}

void Deck::printDeck() {
	for (Card* card : this->cardsList) {
		card->printCard();
	}
}