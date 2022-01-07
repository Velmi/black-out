#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<fmt/format.h>
#include"card.hpp"
#include"player.hpp"

enum
{
    Init,
    Players_turn,
    Dealers_turn,
    Deck_check
}typedef GameStates_t;


int main()
{
    auto a = [](int it){ 
        std::cout << "in lambda \n";
        return it + 1 ; };
    fmt::print("Welcome to Black-Jack! \n");
    Player p {0, 0};
    Player d {0, 0};
    p.score = 0;
    d.score = 0;

    Deck deck;
    Deck table;
    Deck trash;
    GameStates_t current_state = Init;
    GameStates_t next_state;

    // state machine
    while(1)
    {
        switch (current_state)
        {
        case Init:
            fmt::print("\n +++ New game +++ \n");
            move_to_trash(table);
            deck.init_deck();
            deck.aShuffle(Shuffle_FY{}, 100);
            next_state = Players_turn;
            current_state = next_state;
            break;

        case Players_turn:
            fmt::print("\n  Players turn  \n");
            p.score = 0;

            for (char input = 'y'; (input == 'y') || (input == 'Y');)
            {
                put_on_table(deck, table);
                p.score = p.score + table.back().value;

                if (p.score >= 21)
                {
                    break;
                }

                fmt::print("Next card (y or n) ?: ");
                std::cin >> input;
            }

            if(p.score == 21)
            {
                p.rounds_won++;
                std::cout << "21, Player wins! \n";
                next_state = Deck_check;
                current_state = next_state;
                break;
            }
            if(p.score > 21)
            {
                d.rounds_won++;
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
            fmt::print("\n  Dealers turn  \n");
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

            if(d.score == 21)
            {
                d.rounds_won++;
                std::cout << "21, Dealer wins! \n";
                next_state = Deck_check;
                current_state = next_state;
                break;
            }
            if(d.score > 21)
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
    //end state machine
    
    return 0;
}
