#pragma once

#include "card.hpp"

struct Player
{
    unsigned int score;
    unsigned int rounds_won;
    unsigned int wallet;

    Player(unsigned int w) : 
            score{0},
            rounds_won{0},
            wallet{w}
    {}

    unsigned int get_score()
    {
        return this->score;
    }

    int get_bet()
    {
        unsigned int bet = 0;
        if (wallet == 0)
        {
            return -1;
        }
        
        while (1)
        {
            std::cout << "Your wallet: " << wallet << "\nSet your bet: ";
            std::cin >> bet;
            if (bet > wallet)
            {
                std::cout << "Bet to high for your wallet low earner!\n";
                continue;
            }
            break;
        }
        wallet = wallet - bet;
        std::cout << "Set money: " << bet << "\t Your wallet: " << wallet << "\n";
        return bet;
    }

    template <bool unfair = true>
    void give_money(unsigned int money)
    {
        if constexpr (unfair)
        {
            wallet = wallet - money;
        }
        else
        {
            wallet = wallet + money;
        }
        std::cout << "Get money: " << money << "\t Your wallet: " << wallet << "\n";
    }
};

struct Dealer
{
    unsigned int score;
    unsigned int rounds_won;

    Dealer() : 
    score{0},
    rounds_won{0}
    {}

    unsigned int get_score()
    {
        return this->score;
    }
};
