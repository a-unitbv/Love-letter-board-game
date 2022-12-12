#include "LoveLetter.h"

//Constructor area
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
        if(player->getPlayerStatus() == 0)
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
    
    for (Player* player : this->players) {
        deck->remakeDeck(player->getDiscardedCards());
        player->clearDiscardedCards();
        player->setPlayerStatus(0);
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
    player->drawCard(this->deck->drawCard());
    cout << "Player " << player->getPlayerName() << " has drawn a card! Remaning cards: " << this->deck->getRemainingCards() << endl;
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
    cout << "\x1B[2J\x1B[H";
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

void LoveLetter::newTurn(Player* player) {
    if (player->getPlayerStatus()) return;
    if (isGameFinished()) return;
    this->status.turn++;
    cout << "Turn " << this->status.turn << endl;
    drawCard(player);
    player->showHand();
    
    string discardedCardIndex;
    cout << "Choose to discard one card (1 or 2): ";
    cin >> discardedCardIndex;

    while (discardedCardIndex != "1" && discardedCardIndex != "2")
    {
        cout << "Choose to discard one card (1 or 2): ";
        cin >> discardedCardIndex;
    }

    Card* discardedCard = player->getSpecificCard(stoi(discardedCardIndex) - 1);
    makeAction(player, discardedCard);

    player->discardCard(stoi(discardedCardIndex) - 1);
}

void LoveLetter::makeAction(Player * player, Card* card) {
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
        handmainAction(player);
        break;
    case 5:
        princeAction(player);
        break;
    case 6:
        kingAction(player);
        break;
    case 7:
        countessAction(player);
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
    string cardName, playerName;
    cout << "Name a non-Guard card: ";
    cin >> cardName;
    vector<string> cardsNames = { "Princess","King","Countess","Prince","Handmaid","Baron","Priest" };
    while ((std::find(cardsNames.begin(), cardsNames.end(), cardName) == cardsNames.end())) {
        cout << "Unknown card, try again: ";
        cin >> cardName;
    }
    cout << "Enter player name: ";
    cin >> playerName;
    vector<string> playersNames;
    for (Player* p : this->players)
    {
        if (p->getPlayerName() != player->getPlayerName() && p->getPlayerStatus() == 0)
            playersNames.push_back(p->getPlayerName());
    }
    while ((std::find(playersNames.begin(), playersNames.end(), playerName) == playersNames.end())) {
        cout << "Unknown player, try again: ";
        cin >> playerName;
    }

    Player* namedPlayer = getPlayerByName(playerName);
    
    if (namedPlayer->getSpecificCard(0)->getCardName() == cardName) {
        cout << "You were right! " << playerName << " has been eliminated" << endl;
        eliminatePlayer(namedPlayer);
    }
    else {
        cout << "You were wrong!" << endl;
    }
}

void LoveLetter::priestAction(Player* player)
{
    string playerName;
    cout << "Enter player name: ";
    cin >> playerName;
    vector<string> playersNames;
    for (Player* p : this->players)
    {
        if (p->getPlayerName() != player->getPlayerName() && p->getPlayerStatus() == 0)
            playersNames.push_back(p->getPlayerName());
    }
    while ((std::find(playersNames.begin(), playersNames.end(), playerName) == playersNames.end())) {
        cout << "Unknown player, try again: ";
        cin >> playerName;
    }

    Player* namedPlayer = getPlayerByName(playerName);
    cout << namedPlayer->getPlayerName() << " is holding " << namedPlayer->getSpecificCard(0)->getCardName() << endl;
}

void LoveLetter::baronAction(Player*)
{
}

void LoveLetter::handmainAction(Player*)
{
}

void LoveLetter::princeAction(Player*)
{
}

void LoveLetter::kingAction(Player*)
{
}

void LoveLetter::countessAction(Player*)
{
}

void LoveLetter::princessAction(Player*)
{
}

Player* LoveLetter::getPlayerByName(string playerName)
{
    for (Player* player : this->players)
        if (player->getPlayerName() == playerName)
            return player;
}

void LoveLetter::eliminatePlayer(Player* player)
{
    player->setPlayerStatus(1);
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

//Destructor area
LoveLetter::~LoveLetter() {
    delete this->deck;
    for (Player* player : this->players)
        delete player;
}
