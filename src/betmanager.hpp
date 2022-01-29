#pragma once

#include <functional>

struct BetManager
{
    unsigned int                        current_bet;
    std::function<unsigned int(void)>   collect_bet_from_player;
    std::function<void(unsigned int)>   cash_out_to_player;
    std::function<unsigned int(void)>   who_won;

    template<   typename CollectTypeCallback,
                typename CashOutTypeCallback,
                typename WinTypeCallback>
    BetManager( CollectTypeCallback collect_function,
                CashOutTypeCallback cashout_function,
                WinTypeCallback who_won_function) :
                current_bet{0},
                collect_bet_from_player{collect_function},
                cash_out_to_player{cashout_function},
                who_won{who_won_function}
    {}

    int collect_bet()
    {
        current_bet = collect_bet_from_player();
        return current_bet;
    }

    void cash_out()
    {
        switch (who_won())
        {
        case 1:
            {
                cash_out_to_player(current_bet + current_bet * (3/2));
                break;
            }

        case 2:
        case 6:
            {
                cash_out_to_player(current_bet * 2);
                break;
            }
        case 7:
            {
                cash_out_to_player(current_bet);
                break;
            }
        default:
            {
                cash_out_to_player(0);
                break;
            }
        }
    }
};
