#include "LoveLetter.h"

//Constructor area
LoveLetter::LoveLetter(string _filename) : status()
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

//Methods area
void LoveLetter::addPlayer(Player * player) {
    this->players.push_back(player);
}

void LoveLetter::printGameStatus() {
    for (Player* player : this->players) {
        cout << player->getPlayerName() << " has " << player->getPlayerTokens() << " tokens" << endl;
    }
}

int LoveLetter::isFinished() {
    for (Player* player : this->players) {
        if (player->getPlayerTokens() >= this->affectionTokensTarget)
            return 1;
    }
    return 0;
}

int LoveLetter::isGameFinished()
{
    return this->deck->isEmpty();
}

int LoveLetter::calculateAffectionTokens()
{
    if (this->players.size() == 2) return 7;
    else if (this->players.size() == 3) return 5;
    else if (this->players.size() == 4) return 4;
}

void LoveLetter::giveAffectionTokens()
{
    int maxCardValue = 0;
    for (Player* player : this->players) {
        maxCardValue < player->getLastCardValue() ? maxCardValue = player->getLastCardValue() : 0;
    }
    for (Player* player : this->players) {
        if (player->getLastCardValue() == maxCardValue) {
            player->giveAffectionTokens(calculateAffectionTokens());
        }
    }
}

void LoveLetter::restartGame()
{
    for (Player* player : this->players) {
        deck->remakeDeck(player->getDiscardedCards());
        player->clearDiscardedCards();
    }
    cout << "Deck has been remade!" << endl;
    deck->shuffleDeck();
}

void LoveLetter::drawCard()
{
    for (Player* player : this->players)
        drawCard(player);
}

void LoveLetter::drawCard(Player* player) {
    cout << "Player " << player->getPlayerName() << " has drawn a card! Remaning cards: " << this->deck->getRemainingCards() << endl;
    player->drawCard(this->deck->drawCard());
}

void LoveLetter::discardCards()
{
    for (Player* player : this->players)
        player->discardCard(0);
}

void LoveLetter::newGame() {
    drawCard();
    this->status.game++;
    cout << "Game " << this->status.game << endl;
    while (!isGameFinished()) {
        newRound();
    }
    this->status.round = 0;
    discardCards();
    giveAffectionTokens();
    printGameStatus();
    restartGame();
}

void LoveLetter::newRound() {
    this->status.round++;
    cout << "Round " << this->status.round << endl;
    for (Player* player : this->players) {
        newTurn(player);
    }
    this->status.turn = 0;
}

void LoveLetter::newTurn(Player * player) {
    if (this->deck->isEmpty()) return;
    if (player->getPlayerStatus()) return;
    this->status.turn++;
    cout << "Turn " << this->status.turn << endl;
    drawCard(player);
    player->showHand();
    cout << "Choose to discard one card (1 or 2): ";
    int discardedCard;
    cin >> discardedCard; 
    player->discardCard(discardedCard - 1);
}

void LoveLetter::start() {
    /*while (!isFinished()) {
        newGame();
    }
    printWinner();*/
}

void LoveLetter::printWinner()
{
    for (Player* player : this->players)
        if (player->getPlayerTokens() >= this->affectionTokensTarget)
            cout << endl << "The winner is: " << player->getPlayerName() << "! Congratulations" << endl;
}

//Destructor area
LoveLetter::~LoveLetter() {
    delete this->deck;
    for (Player* player : this->players)
        delete player;
}
