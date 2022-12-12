#pragma once
#include "Player.h"
#include "Deck.h"
#include <vector>

using namespace std;

struct GameStatus {
	int game, round, turn;
	GameStatus() : game(0), round(0), turn(0) {}
};

class LoveLetter {
	Deck* deck;
	GameStatus status;
	Card* faceDownCard;
	vector<Player*> players;
	string affectionTokensTarget;

public:
	//Constructor area
	LoveLetter(string);

	//Methods area
	void start();
	void addPlayer(Player*);
	void drawCard();
	void drawCard(Player*);
	void newGame();
	void newRound();
	void newTurn(Player*);
	void makeAction(Player*, Card*);
	void guardAction(Player*);
	void priestAction(Player*);
	void baronAction(Player*);
	void handmainAction(Player*);
	void princeAction(Player*);
	void kingAction(Player*);
	void countessAction(Player*);
	void princessAction(Player*);
	Player* getPlayerByName(string);
	void eliminatePlayer(Player*);
	void discardCards();
	void restartGame();
	int isFinished();
	int isGameFinished();
	int calculateAffectionTokens();
	void giveAffectionTokens();
	void printGameStatus();
	void printWinner();

	//Destructor area
	~LoveLetter();
};
