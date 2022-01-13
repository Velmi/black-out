#pragma once

#include "card.hpp"

struct Player
{
    unsigned int score;
    unsigned int rounds_won;
    int wallet;
    unsigned int bet;

    Player(int Wallet)
    {
        this->score = 0;
        this->rounds_won = 0;
        this->wallet = Wallet;
    }

    void set_bet(unsigned int Bet)
    {
        this->bet = Bet;
    }
};

struct Dealer
{
    unsigned int score;
};
