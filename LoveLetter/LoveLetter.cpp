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
    //move cards

    deck->shuffleDeck();
}

void LoveLetter::drawCard()
{
    for (Player* player : this->players)
        drawCard(player);
}

void LoveLetter::drawCard(Player* player) {
    cout << "Player " << player->getPlayerName() << " has drawn a card! Remaning cards: " << this->deck->getRemainingCards() << endl;
    player->draw(this->deck->drawCard());
}

void LoveLetter::discardCards()
{
    for (Player* player : this->players)
        player->discard(0);
}

void LoveLetter::newGame() {
    drawCard();
    this->game++;
    cout << "Game " << this->game << endl;
    while (!isGameFinished()) {
        newRound();
    }
    this->round = 0;
    discardCards();
    giveAffectionTokens();
    printGameStatus();
    restartGame();
}

void LoveLetter::newRound() {
    this->round++;
    cout << "Round " << this->round << endl;
    for (Player* player : this->players) {
        newTurn(player);
    }
    this->turn = 0;
}

void LoveLetter::newTurn(Player * player) {
    if (this->deck->isEmpty()) return;
    if (player->getPlayerStatus()) return;
    this->turn++;
    cout << "Turn " << this->turn << endl;
    drawCard(player);
    player->show();
    cout << "Choose to discard one card (1 or 2): ";
    int discardedCard;
    cin >> discardedCard; 
    player->discard(discardedCard - 1);
}

void LoveLetter::start() {
    //while (!isFinished()) {
        newGame();
    //}
}