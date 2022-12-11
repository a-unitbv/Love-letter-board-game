#include "Player.h"

//Constructor area
Player::Player(string _playerName) : playerName(_playerName), playerStatus(0), playerTokens(0)
{

}

//Getters area
string Player::getPlayerName()
{
	return this->playerName;
}

bool Player::getPlayerStatus()
{
	return this->playerStatus;
}

int Player::getPlayerTokens()
{
	return this->playerTokens;
}

Card* Player::getSpecificCard(int index)
{
	return this->playerHand[index];
}

vector<Card*> Player::getDiscardedCards()
{
	return this->discardedCards;
}

//Methods area
void Player::showHand() {
	cout << "Player " << this->playerName << " has: " << endl;
	for (Card* card : this->playerHand) {
		cout << "\t- ";
		card->printCard();
	}
}

void Player::drawCard(Card* card) {
	this->playerHand.push_back(move(card));
}

void Player::discardCard(int cardIndex) {
	this->discardedCards.push_back(move(this->playerHand[cardIndex]));
	this->playerHand.erase(this->playerHand.begin() + cardIndex);
}

int Player::getLastCardValue()
{
	return this->discardedCards[this->discardedCards.size() - 1]->getCardValue();
}

void Player::clearDiscardedCards()
{
	this->discardedCards.erase(this->discardedCards.begin(), this->discardedCards.end());
}

void Player::giveAffectionTokens(int tokens)
{
	this->playerTokens += tokens;
}

//Destructor area
Player::~Player() {
}
