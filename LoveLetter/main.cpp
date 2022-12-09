#include <iostream>
#include "LoveLetter.h"
int main()
{
    LoveLetter* game = new LoveLetter("deck.in");
    game->start();

    delete game;
}
