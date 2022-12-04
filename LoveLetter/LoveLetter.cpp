#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

int main()
{
    Deck* deck = new Deck("deck.txt");
    deck->shuffleDeck();
    deck->printDeck();

    Player* player = new Player("Flavius");
    player->draw(deck->drawCard());
    player->draw(deck->drawCard());
    player->show();
    player->discard(0);
    player->show();

    deck->printDeck();
}
