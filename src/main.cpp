#include <iostream>
#include <string>
#include <array>
#include <vector>
//#include<fmt/format.h>
#include "game.hpp"
#include "card.hpp"
#include "player.hpp"


int main()
{
    std::cout << "Welcome to Black-Jack! \n";
    Deck deck;
    Deck table;
    GameManager game{Player(1000), Dealer{0}, deck, table};
    GameStates_t current_state = Init;
    GameStates_t next_state;

    // state machine
    while (1)
    {
        switch (current_state)
        {
        case Init:
            std::cout << "\n +++ New game +++ \n";
            move_to_trash(table);
            deck.init_deck();
            deck.shuffle(FYShuffle, 100);
            next_state = Players_turn;
            current_state = next_state;
            break;

        case Players_turn:
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

        case Dealers_turn:
            std::cout << "\n  Dealers turn  \n";
            d.score = 0;
            while (d.score < 17)
            {
                put_on_table(deck, table);
                d.score = d.score + table.back().value;

                if (d.score >= 21)
                {
                    break;
                }
            }

            if (d.score == 21)
            {
                std::cout << "21, Dealer wins! \n";
                next_state = Deck_check;
                current_state = next_state;
                break;
            }
            if (d.score > 21)
            {
                p.rounds_won++;
                std::cout << "Over 21, Player wins! \n";
                next_state = Deck_check;
                current_state = next_state;
                break;
            }
            else
            {
                std::cout << "Dealers score: " << d.score << "\n";
                if (d.score > p.score)
                {
                    d.score++;
                    std::cout << "Dealer wins! \n";
                }
                if (p.score > d.score)
                {
                    p.score++;
                    std::cout << "Player wins! \n";
                }
                if (p.score == d.score)
                {
                    std::cout << "Draw! \n";
                }
                next_state = Deck_check;
                current_state = next_state;
                break;
            }

        case Deck_check:
            if (deck.size() <= 13)
            {
                next_state = Init;
                current_state = next_state;
                break;
            }

            else
            {
                next_state = Players_turn;
                current_state = next_state;
                break;
            }

        default:
            break;
        }
    }
    // end state machine

    return 0;
}
