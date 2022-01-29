#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <chrono>
#include <thread>
//#include<fmt/format.h>
#include "game.hpp"
#include "card.hpp"
#include "player.hpp"


int main()
{
    std::cout << "Welcome to Black-Jack! \n";
    GameManager game;

    while (1)
    {
        if (game.handler() == -1)
        {
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Game over! \n";

    return 0;
}
