#include "Deck.h"
#include <random>

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
			this->cardsList.push_back(new Card(cardValue, cardName, cardDescription));
		}
	}
	cout << "Deck has been created!" << endl;
	this->shuffleDeck();
}


int Deck::getRemainingCards()
{
	return this->remainingCards;
}

int Deck::isEmpty()
{
	if (this->cardsList.size() == 0)
		return 1;
	return 0;
}

Card* Deck::drawCard()
{
	if (this->remainingCards > 0) {
		this->remainingCards--;
		Card* drawnCard = move(this->cardsList[0]);
		this->cardsList.erase(this->cardsList.begin());
		return drawnCard;
	}
}

void Deck::printDeck()
{
	cout << "Remaining cards (" << this->remainingCards << ")\n";
	for (Card* card : this->cardsList) {
		card->printCard();
	}
}

void Deck::shuffleDeck()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(this->cardsList.begin(), this->cardsList.end(), g);

	cout << "Deck has been shuffled!" << endl;
}

void Deck::remakeDeck(Card* card)
{
	cout << "1 ";
	this->remainingCards += 1;
	this->cardsList.push_back(move(card));
}

void Deck::remakeDeck(vector<Card*> cards)
{
	cout << cards.size() << " ";
	this->remainingCards += cards.size();
	this->cardsList.insert(this->cardsList.end(), make_move_iterator(cards.begin()), make_move_iterator(cards.end()));
}


Deck::~Deck() {
	for (Card* card : this->cardsList) {
		delete card;
	}
}