#include "Player.h"

Player::Player(string _playerName) : playerName(_playerName), playerStatus(0), playerTokens(0)
{

}

void Player::draw(Card* card) {
	this->playerHand.push_back(move(card));
}

void Player::discard(int cardIndex) {
	this->playerHand.erase(this->playerHand.begin() + cardIndex);
}

void Player::show() {
	cout << "Player " << this->playerName << " has: " << endl;
	for (Card* card : this->playerHand) {
		cout << "\t- ";
		card->printCard();
	}
}