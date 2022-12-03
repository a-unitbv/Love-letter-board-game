#include <iostream>
#include "Card.h"
#include "Deck.h"

int main()
{
    Deck* deck = new Deck("deck.txt");
    
    deck->printDeck();
}
