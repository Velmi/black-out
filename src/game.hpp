#include <iostream>
#include "player.hpp"
#include "card.hpp"
#include "betmanager.hpp"


struct GameManager
{
    enum class state
    {
        Init,
        Players_turn,
        Dealers_turn,
        Deck_check
    };
    Player player;
    Dealer dealer;
    BetManager bet_mng;
    Deck deck;
    Deck table;
    state game_state = state::Init;

    GameManager() :
            player{1000},
            bet_mng{player.set_bet(), player.get_money()}
    {}

    void Init()
    {
        std::cout << "\n +++ New game +++ \n";
        move_to_trash(table);
        deck.init_deck();
        deck.shuffle(FYShuffle, 100);
    }

    int Players_turn()
    {
        std::cout << "\n  Players turn  \n";
        player.score = 0;

        for (char input = 'y'; (input == 'y') || (input == 'Y');)
        {
            put_on_table(deck, table);
            if (table.back().name == Ace)
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

        if (player.score == 21)
        {
            player.rounds_won++;
            std::cout << "21, Player wins! \n";
            return 1;
        }
        if (player.score > 21)
        {
            std::cout << "Over 21, Dealer wins! \n";
            return 2;
        }
        else
        {
            std::cout << "Your score: " << player.score << "\n";
            return 3;
        }
    }

    int Dealers_turn()
    {
        std::cout << "\n  Dealers turn  \n";
        dealer.score = 0;
        while (dealer.score < 17)
        {
            put_on_table(deck, table);
            dealer.score = dealer.score + table.back().value;

            if (dealer.score >= 21)
            {
                break;
            }
        }

        if (dealer.score == 21)
        {
            std::cout << "21, Dealer wins! \n";
            return 1;
        }
        if (dealer.score > 21)
        {
            player.rounds_won++;
            std::cout << "Over 21, Player wins! \n";
            return 2;
        }
        else
        {
            std::cout << "Dealers score: " << dealer.score << "\n";
            if (dealer.score > player.score) {
                dealer.score++;
                std::cout << "Dealer wins! \n";
            }
            if (player.score > dealer.score) {
                player.score++;
                std::cout << "Player wins! \n";
            }
            if (player.score == dealer.score) {
                std::cout << "Draw! \n";
            }
            return 3;
        }
    }

    void set_bet()
    {

    }

    void handler()
    {
        switch (game_state)
        {
            case state::Init:
            {
                Init();
                game_state = state::Players_turn;
            }
                break;

            case state::Players_turn:
            {
                switch (Players_turn())
                {
                    case 1:
                    case 2:
                    {
                        game_state = state::Deck_check;
                    }
                        break;
                    case 3:
                    {
                        game_state = state::Dealers_turn;
                    }
                        break;
                }
            }
                break;

            case state::Dealers_turn:
            {
                Dealers_turn();
                game_state = state::Deck_check;
            }
                break;

            case state::Deck_check:
            {
                if (deck.size() <= 13)
                {
                    game_state = state::Init;
                }
                else
                {
                    game_state = state::Players_turn;
                }
            }
                break;
        }
    }
};
