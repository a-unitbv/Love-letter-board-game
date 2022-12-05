#include <iostream>
#include "LoveLetter.h"
int main()
{
    LoveLetter* game = new LoveLetter("deck.txt");
    game->start();
}
