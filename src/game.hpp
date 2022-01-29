#pragma once

#include <iostream>
#include "player.hpp"
#include "card.hpp"
#include "betmanager.hpp"
#include "rulesmanager.hpp"


struct GameManager
{
    enum class State
    {
        Init,
        Players_turn,
        Dealers_turn,
        End
    };

    Player player;
    Dealer dealer;
    RulesManager rules_mng;
    BetManager bet_mng;
    Deck deck;
    Deck table;
    Shuffle shuffle;
    State game_state = State::Init;

    GameManager() :
            player{1000},
            dealer{},
            rules_mng
            {
                [&](){return player.get_score();},
                [&](){return dealer.get_score();},
            },
            bet_mng
            {   [&](){return player.get_bet();},
                [&](unsigned int money){player.give_money<false>(money);},
                [&](){return rules_mng.get_winner();}
            }
    {}

    State get_state()
    {
        return this->game_state;
    }

    // state functions
    void Init()
    {
        std::cout << "\n +++ New game +++ \n";
        move_to_trash(table);
        deck.fill_deck();
        deck.shuffle(shuffle.FisherYates, 100);
    }

    int Players_turn()
    {
        player.score = 0;
        dealer.score = 0;
        std::cout << "\n  Players turn  \n";
        
        if (bet_mng.collect_bet() == -1)
        {
            return -1;
        }

        for (char input = 'y'; (input == 'y') || (input == 'Y');)
        {
            put_on_table(deck, table);
            if (table.back().name == Card::Name::Ace)
            {
                char input_ace;
                std::cout << "Change Ace value from 11 to 1? (y or n): ";
                std::cin >> input_ace;
                if ((input_ace == 'y') || (input_ace == 'Y'))
                {
                    table.cards.at(table.size() - 1).value = 1;
                }
            }
            player.score = player.score + table.back().value;

            if (player.score >= 21)
            {
                break;
            }

            std::cout << "Next card (y or n) ?: ";
            std::cin >> input;
        }

        switch (rules_mng.rules_check())
        {
        case 0:
            {
                std::cout << "Your score: " << player.score << "\n";
                game_state = State::Dealers_turn;
                return 0;
            }
        case 1:
        case 3:
            {
                return 1;
            }

        default:
                break;
        }
        return -1;
    }

    int Dealers_turn()
    {
        std::cout << "\n  Dealers turn  \n";
        while (dealer.score < 17)
        {
            put_on_table(deck, table);
            dealer.score = dealer.score + table.back().value;

            if (dealer.score >= 21)
            {
                break;
            }
        }

        switch (rules_mng.rules_check())
        {
        case 0:
            {
                std::cout << "Dealers score: " << dealer.score << "\n";
                return 0;
            }
        case 4:
        case 6:
            {
                return 4;
            }
                break;
        
        default:
            break;
        }
        return -1;
    }

    int End()
    {
        bet_mng.cash_out();
        if (deck.size() <= 13)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    // end state functions

    int handler()
    {
        switch (game_state)
        {
        case State::Init:
            {
                Init();
                game_state = State::Players_turn;
                break;
            }

        case State::Players_turn:
            {
                switch (Players_turn())
                {
                case 0:
                    {
                        game_state = State::Dealers_turn;
                        break;
                    }
                case 1:
                    {
                        game_state = State::End;
                        break;
                    }
                case -1:
                    return -1;
                }
            }
                break;

        case State::Dealers_turn:
            {
                Dealers_turn();
                game_state = State::End;
            }
                break;

        case State::End:
            {
                switch (End())
                {
                case 0:
                    {
                        game_state = State::Init;
                        break;
                    }
                case 1:
                    {
                        game_state = State::Players_turn;
                        break;
                    }
                default:
                    break;
                }
            }
        }
    return 0;
    }
};
