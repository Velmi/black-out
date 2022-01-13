//
// Created by markus on 1/13/22.
//
#pragma once
#include <functional>

struct BetManager
{
    unsigned int current_bet;
    std::function<unsigned int(void)> collect_bet_from_player;
    std::function<void(unsigned int)> cash_out_to_player;

    template<typename CollectTypeCallback, typename CashOutTypeCallback>
    BetManager(CollectTypeCallback collect_function, CashOutTypeCallback cashout_function) :
    current_bet{0},
    collect_bet_from_player{collect_function},
    cash_out_to_player{cashout_function}
    {}

    void collect_bet()
    {
        current_bet = collect_bet_from_player();
    }

    unsigned int cash_out(int winning_type)
    {
        //TODO
    }
};
