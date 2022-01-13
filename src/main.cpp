#include <iostream>
#include <string>
#include <array>
#include <vector>
//#include<fmt/format.h>
#include <chrono>
#include <thread>
#include "game.hpp"
#include "card.hpp"
#include "player.hpp"


int main()
{
    std::cout << "Welcome to Black-Jack! \n";
    Deck deck;
    Deck table;
    GameManager game{Player(1000), Dealer{0}, deck, table};

    while (1)
    {
        game.handler();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
