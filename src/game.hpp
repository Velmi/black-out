#include <iostream>
#include "player.hpp"
#include "card.hpp"

/*
enum
{
    Init,
    Players_turn,
    Dealers_turn,
    Deck_check
} typedef GameStates_t;
*/

struct GameManager
{
    Player player;
    Dealer dealer;
    Deck deck;
    Deck table;

    template <typename P>
    void execute_state(P state)
    {
    }

    template <typename P>
    P rules_check()
    {
    }
};

auto Init = [](Player &player, Dealer &dealer, Deck &deck, Deck &table)
{
    std::cout << "\n +++ New game +++ \n";
    move_to_trash(table);
    deck.init_deck();
    deck.shuffle(FYShuffle, 100);
    next_state = Players_turn;
    current_state = next_state;
    break;
}

auto Players_turn = [](Player &player, Dealer &dealer, Deck &deck, Deck &table)
{
    std::cout << "\n  Players turn  \n";
    p.score = 0;

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
        p.score = p.score + table.back().value;

        if (p.score >= 21)
        {
            break;
        }

        std::cout << "Next card (y or n) ?: ";
        std::cin >> input;
    }

    if (p.score == 21)
    {
        p.rounds_won++;
        std::cout << "21, Player wins! \n";
        next_state = Deck_check;
        current_state = next_state;
        break;
    }
    if (p.score > 21)
    {
        std::cout << "Over 21, Dealer wins! \n";
        next_state = Deck_check;
        current_state = next_state;
        break;
    }
    else
    {
        std::cout << "Your score: " << p.score << "\n";
        next_state = Dealers_turn;
        current_state = next_state;
        break;
    }
}