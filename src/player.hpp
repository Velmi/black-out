#pragma once

#include"card.hpp"

struct Player
{
    unsigned int score;
    unsigned int rounds_won;
    int wallet;
    unsigned int bet;

    Player (unsigned int Score, unsigned int roundsWon, int Wallet)
    {
        this->score = Score;
        this->rounds_won = roundsWon;
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
