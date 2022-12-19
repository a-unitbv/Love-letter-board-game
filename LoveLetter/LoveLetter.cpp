#include "LoveLetter.h"

LoveLetter::LoveLetter(string _filename) : status()
{
    cout << "Welcome to LoveLetter Game!" << endl;

    cout << "Please enter no. of affection tokens target for players: ";
    cin >> this->affectionTokensTarget;

    while (!(find_if(this->affectionTokensTarget.begin(), this->affectionTokensTarget.end(), [](char c) { return !isdigit(c); }) == this->affectionTokensTarget.end())) {
        cout << "Enter a valid value: ";
        cin >> this->affectionTokensTarget;
    }

    string playersNumber;
    cout << "Please enter no. of players who're going to play with! (2-4): ";
    cin >> playersNumber;

    while (!(find_if(playersNumber.begin(), playersNumber.end(), [](char c) { return !isdigit(c); }) == playersNumber.end())) {
        cout << "Wrong number of players, try again! (2-4): ";
        cin >> playersNumber;
    }

    while (stoi(playersNumber) > 4 || stoi(playersNumber) < 2) {
        cout << "Wrong number of players, try again! (2-4): ";
        cin >> playersNumber;
    }

    for (int i = 0; i < stoi(playersNumber); i++) {
        string playerName;
        cout << "Enter player's " << i + 1 << " name: ";
        cin >> playerName;
        this->addPlayer(new Player(playerName));
    }

    this->deck = new Deck(_filename);

    this->faceDownCard = move(deck->drawCard());
    cout << "A card has been put aside facedown." << endl;
}

void LoveLetter::addPlayer(Player* player) {
    this->players.push_back(player);
}

void LoveLetter::printGameStatus() {
    for (Player* player : this->players) {
        cout << player->getPlayerName() << " has " << player->getPlayerTokens() << " tokens" << endl;
    }
}

int LoveLetter::isFinished() {
    for (Player* player : this->players) {
        if (player->getPlayerTokens() >= stoi(this->affectionTokensTarget))
            return 1;
    }
    return 0;
}

int LoveLetter::isGameFinished()
{
    if (this->deck->isEmpty()) return 1;
    int count = 0;
    for (Player* player : this->players)
        if (player->getPlayerStatus() == 0)
            count++;
    if (count == 1) return 1;
    return 0;
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
        if (player->getPlayerStatus() == 0)
            maxCardValue < player->getLastCardValue() ? maxCardValue = player->getLastCardValue() : 0;
    }
    for (Player* player : this->players) {
        if (player->getLastCardValue() == maxCardValue) {
            cout << "Player " << player->getPlayerName() << " won the round!" << endl;
            player->giveAffectionTokens(calculateAffectionTokens());
        }
    }
}

void LoveLetter::restartGame()
{
    deck->remakeDeck(this->getFaceDownCard());
    for (Player* player : this->players) {
        deck->remakeDeck(player->getDiscardedCards());
        player->clearDiscardedCards();
        player->setPlayerStatus(0);
    }
    cout << "Deck has been remade!" << endl;
    deck->shuffleDeck();

    this->faceDownCard = move(deck->drawCard());
    cout << "A card has been put aside facedown." << endl;
}

Card* LoveLetter::getFaceDownCard()
{
    return move(this->faceDownCard);
}

void LoveLetter::drawCard()
{
    for (Player* player : this->players)
        drawCard(player);
}

void LoveLetter::drawCard(Player* player) {
    player->drawCard(this->deck->drawCard());
    cout << "Player " << player->getPlayerName() << " has drawn a card! Remaning cards: " << this->deck->getRemainingCards() << endl;
}

void LoveLetter::discardCards()
{
    for (Player* player : this->players)
        if (player->getPlayerStatus() == 0)
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
    cout << "\x1B[2J\x1B[H";
    giveAffectionTokens();
    printGameStatus();
    restartGame();
}

void LoveLetter::newRound() {
    this->status.round++;
    cout << "Round " << this->status.round << endl;
    for (Player* player : this->players) {
        player->setPlayerProtection(0);
        newTurn(player);
    }
    this->status.turn = 0;
}

void LoveLetter::newTurn(Player* player) {
    if (player->getPlayerStatus()) return;
    if (isGameFinished()) return;
    this->status.turn++;
    cout << "Turn " << this->status.turn << endl;
    drawCard(player);
    player->showHand();

    if (countessAction(player)) return;

    string discardedCardIndex;
    cout << "Choose to discard one card (1 or 2): ";
    cin >> discardedCardIndex;

    while (discardedCardIndex != "1" && discardedCardIndex != "2")
    {
        cout << "Choose to discard one card (1 or 2): ";
        cin >> discardedCardIndex;
    }

    Card* discardedCard = player->getSpecificCard(stoi(discardedCardIndex) - 1);

    player->discardCard(stoi(discardedCardIndex) - 1);

    makeAction(player, discardedCard);
}

void LoveLetter::makeAction(Player* player, Card* card) {
    switch (card->getCardValue()) {
    case 1:
        guardAction(player);
        break;
    case 2:
        priestAction(player);
        break;
    case 3:
        baronAction(player);
        break;
    case 4:
        handmaidAction(player);
        break;
    case 5:
        princeAction(player);
        break;
    case 6:
        kingAction(player);
        break;
    case 7:
        break;
    case 8:
        princessAction(player);
        break;
    default:
        cout << "Could not make action, invalid card value!" << endl;
        break;
    }
}

void LoveLetter::guardAction(Player* player)
{
    string cardName;
    cout << "Name a non-Guard card: ";
    cin >> cardName;
    vector<string> cardsNames = { "Princess","King","Countess","Prince","Handmaid","Baron","Priest" };
    while ((std::find(cardsNames.begin(), cardsNames.end(), cardName) == cardsNames.end())) {
        cout << "Unknown card, try again: ";
        cin >> cardName;
    }

    Player* namedPlayer = getPlayerByName();

    if (namedPlayer->getSpecificCard(0)->getCardName() == cardName) {
        cout << "You were right! " << namedPlayer->getPlayerName() << " has been eliminated" << endl;
        eliminatePlayer(namedPlayer);
    }
    else {
        cout << "You were wrong!" << endl;
    }
}

void LoveLetter::priestAction(Player* player)
{
    Player* namedPlayer = getPlayerByName();
    if (namedPlayer->getPlayerName() == player->getPlayerName()) return;

    cout << "Player " << namedPlayer->getPlayerName() << " is holding " << namedPlayer->getSpecificCard(0)->getCardName() << endl;
}

void LoveLetter::baronAction(Player* player)
{
    Player* namedPlayer = getPlayerByName();
    if (namedPlayer->getPlayerName() == player->getPlayerName()) return;

    if (player->getSpecificCard(0)->getCardValue() > namedPlayer->getSpecificCard(0)->getCardValue())
    {
        cout << namedPlayer->getPlayerName() << " has been eliminated" << endl;
        eliminatePlayer(namedPlayer);
    }
    else if (player->getSpecificCard(0)->getCardValue() < namedPlayer->getSpecificCard(0)->getCardValue()) {
        cout << player->getPlayerName() << " has been eliminated" << endl;
        eliminatePlayer(player);
    }
}

void LoveLetter::handmaidAction(Player* player)
{
    cout << "Player " << player->getPlayerName() << " is protected this round!" << endl;
    player->setPlayerProtection(1);
}

void LoveLetter::princeAction(Player* player)
{
    Player* namedPlayer = getPlayerByName();
    cout << "Player " << namedPlayer->getPlayerName() << " hand has been discarded" << endl;
    if (namedPlayer->getSpecificCard(0)->getCardName() == "Princess")
    {
        eliminatePlayer(namedPlayer);
        cout << "Player " << namedPlayer->getPlayerName() << " has been eliminated! Princess has been discarded." << endl;
    }
    else {
        namedPlayer->discardCard(0);
        drawCard(namedPlayer);
    }
}

void LoveLetter::kingAction(Player* player)
{
    Player* namedPlayer = getPlayerByName();
    if (namedPlayer->getPlayerName() == player->getPlayerName()) return;

    Card* namedPlayerCard = move(namedPlayer->getSpecificCard(0));
    namedPlayer->discardCard(0);
    namedPlayer->drawCard(move(player->getSpecificCard(0)));
    player->drawCard(move(namedPlayerCard));
    player->discardCard(0);

    cout << "Player " << player->getPlayerName() << " swapped hand with player " << namedPlayer->getPlayerName() << endl;
}

int LoveLetter::countessAction(Player* player)
{
    string firstCard = player->getSpecificCard(0)->getCardName();
    string secondCard = player->getSpecificCard(1)->getCardName();

    if (firstCard == "Countess" && (secondCard == "King" || secondCard == "Prince"))
    {
        player->discardCard(0);
        cout << "Countess has been automatically discarded!";
        return 1;
    }
    else if (secondCard == "Countess" && (firstCard == "King" || firstCard == "Prince")) {
        player->discardCard(1);
        cout << "Countess has been automatically discarded!";
        return 1;
    }
    return 0;
}

void LoveLetter::princessAction(Player* player)
{
    eliminatePlayer(player);
    cout << "Player " << player->getPlayerName() << " has been eliminated! Princess has been discarded." << endl;
}

Player* LoveLetter::getPlayerByName()
{
    vector<string> playersNames;
    for (Player* p : this->players)
    {
        if (p->getPlayerStatus() == 0 && p->getPlayerProtection() == 0)
            playersNames.push_back(p->getPlayerName());
    }

    cout << "Available players: ";
    for (string p : playersNames)
        cout << p << ' ';
    cout << endl;

    string playerName;
    cout << "Enter player name: ";
    cin >> playerName;

    while ((std::find(playersNames.begin(), playersNames.end(), playerName) == playersNames.end())) {
        cout << "Unknown player, try again: ";
        cin >> playerName;
    }

    for (Player* player : this->players)
        if (player->getPlayerName() == playerName)
            return player;
}

void LoveLetter::eliminatePlayer(Player* player)
{
    player->setPlayerStatus(1);
    player->discardCard(0);
}

void LoveLetter::start() {
    while (!isFinished()) {
        newGame();
    }
    printWinner();
}

void LoveLetter::printWinner()
{
    for (Player* player : this->players)
        if (player->getPlayerTokens() >= stoi(this->affectionTokensTarget))
            cout << endl << "The winner is: " << player->getPlayerName() << "! Congratulations" << endl;
}


LoveLetter::~LoveLetter() {
    delete this->deck;
    for (Player* player : this->players)
        delete player;
}
