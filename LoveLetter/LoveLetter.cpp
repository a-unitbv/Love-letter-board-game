#include "LoveLetter.h"

LoveLetter::LoveLetter(string _filename): game(0), round(0), turn(0)
{
    cout << "Welcome to LoveLetter Game!" << endl;

    cout << "Please enter no. of affection tokens target for players: ";
    cin >> this->affectionTokensTarget;
    
    int playersNumber;
    cout << "Please enter no. of players who're going to play with! (2-4): ";
    cin >> playersNumber;
    while (playersNumber > 4 || playersNumber < 2) {
        cout << "Wrong number of players, try again! (2-4): ";
        cin >> playersNumber;
    }
    for (int i = 0; i < playersNumber; i++) {
        string playerName;
        cout << "Enter player's " << i + 1 << " name: ";
        cin >> playerName;
        this->addPlayer(new Player(playerName));
    }

    this->deck = new Deck(_filename);
}

void LoveLetter::addPlayer(Player * player) {
    this->players.push_back(player);
}

void LoveLetter::printGameStatus() {
    cout << "Game " << this->game << " Round " << this->round << " Turn " << this->turn << endl;
    for (Player* player : this->players) {
        cout << player->getPlayerName() << " has " << player->getPlayerTokens() << " tokens" << endl;
    }
}

void LoveLetter::startGame() {
    printGameStatus();
}