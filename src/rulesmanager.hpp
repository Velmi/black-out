# pragma once

#include <iostream>
#include <functional>
#include "player.hpp"
#include "game.hpp"

struct RulesManager
{
    enum class WinningType
    {
        Player21 = 1,
        PlayerWinComp,
        PlayerOver21,
        Dealer21,
        DealerWinComp,
        DealerOver21,
        Draw
    };

    WinningType winning_type;
    unsigned int player_score;
    unsigned int dealer_score;
    std::function<unsigned int(void)>       get_score_from_player;
    std::function<unsigned int(void)>       get_score_from_dealer;

    template<       typename GetPlayerScoreType,
                    typename GetDealerScoreType
                    >
    RulesManager(   GetPlayerScoreType get_p_score_function,
                    GetDealerScoreType get_d_score_funtion) : 
                    get_score_from_player{get_p_score_function},
                    get_score_from_dealer{get_d_score_funtion}
    {}

    unsigned int rules_check()
    {
        player_score = get_score_from_player();
        dealer_score = get_score_from_dealer();

        if (player_score > 21)
        {
            std::cout << "Over 21! Dealer wins! \n";
            winning_type = WinningType::PlayerOver21;
            return static_cast<unsigned int>(winning_type);
        }
        else if (player_score == 21)
        {
            std::cout << "21! Player wins! \n";
            winning_type = WinningType::Player21;
            return static_cast<unsigned int>(winning_type);
        }
        else if (dealer_score > 21)
        {
            std::cout << "Over 21! Player wins! \n";
            winning_type = WinningType::DealerOver21;
            return static_cast<unsigned int>(winning_type);
        }
        else if (dealer_score == 21)
        {
            std::cout << "21! Dealer wins! \n";
            winning_type = WinningType::Dealer21;
            return static_cast<unsigned int>(winning_type);
        }
        else
        {
            winning_type = static_cast<WinningType>(0);
            return 0;
        }
    }

    unsigned int get_winner()
    {
        if (    (winning_type == WinningType::PlayerOver21) || 
                (winning_type == WinningType::Player21)     ||
                (winning_type == WinningType::DealerOver21) ||
                (winning_type == WinningType::Dealer21)     )
        {
            return static_cast<unsigned int>(winning_type);
        }
        else if (player_score > dealer_score)
        {
            std::cout << "Player wins! \n";
            winning_type = WinningType::PlayerWinComp;
            return static_cast<unsigned int>(winning_type);
        }
        else if (player_score < dealer_score)
        {
            std::cout << "Dealer wins! \n";
            winning_type = WinningType::DealerWinComp;
            return static_cast<unsigned int>(winning_type);
        }
        else if (player_score == dealer_score)
        {
            std::cout << "Draw! \n";
            winning_type = WinningType::Draw;
            return static_cast<unsigned int>(winning_type);
        }
        else
        {return 0;}
    }
};
