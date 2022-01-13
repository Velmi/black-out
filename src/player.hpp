#pragma once

#include "card.hpp"

struct Player
{
    unsigned int score;
    unsigned int rounds_won;
    unsigned int wallet;

    //TODO kjonstúktoir

    unsigned int set_bet()
    {
        unsigned int bet = 0;
        while (1)
        {
            std::cout << "Your wallet: " << wallet << "\nSet your bet: ";
            std::cin >> bet;
            if (bet > wallet)
            {
                std::cout << "Bet to high for your wallet Geringverdiener!\n";
                continue;
            }
            break;
        }
        wallet = wallet - bet;
        return bet;
    }

    template<bool unfair = true>
    void get_money(unsigned int money)
    {
        std::cout << "Get money: " << money << "\t Your wallet: " << wallet << "\n";
        if constexpr (unfair)
        {
            wallet = wallet - money;
        }
        else
        {
            wallet = wallet + money;
        }
    }
};

struct Dealer
{
    unsigned int score;
};
