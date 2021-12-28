#pragma once

#include<string>
#include<array>
#include"card.hpp"

struct Player
{
    unsigned int score;
    unsigned int rounds_won;
};

struct Guest : Player
{
    int a;
};

struct Dealer : Player
{
    int a;
};