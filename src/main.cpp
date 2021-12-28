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
    fmt::print("Welcome to Black-Jack! \n");
    Player p {0, 0};
    Player d {0, 0};

    Deck deck;
    Deck table;
    Deck trash;
    GameStates_t current_state = Init;
    GameStates_t next_state;

    // State machine
    while(1)
    {
        switch (current_state)
        {
        case Init:
            deck.init_deck();
            deck.shuffle(100);
            p.score = 0;
            d.score = 0;
            next_state = Players_turn;
            current_state = next_state;
            break;

        case Players_turn:
            char input;
            do
            {
                put_on_table(deck, table);
                p.score = p.score + table.cards.back().value;

                if(p.score == 21)
                {
                    break;
                }

                do
                {
                    fmt::print("Next card? (y or n): ");
                    std::cin >> input;
                } while ((input != 'y') || (input != 'n'));
            } while((input == 'y') && p.score < 21);

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
                next_state = Dealers_turn;
                current_state = next_state;
                break;
            }
        
        case Dealers_turn:
            do
            {
                put_on_table(deck, table);
                d.score = d.score + table.cards.back().value;

                if(d.score == 21)
                {
                    break;
                }

            } while(d.score >= 17);

            if((d.score == 21))
            {
                d.rounds_won++;
                std::cout << "21, Dealer wins! \n";
                next_state = Deck_check;
                current_state = next_state;
                break;
            }
        default:
            break;
        }
    }
    
    deck.init_deck();
    deck.shuffle(100);
    std::cout << deck;
    //deck.print();

    
    return 0;
}

/*
    while(true)
    {
        static int player_sum = 0;
        // player round
        while(true)
        {
            put_on_table(deck, table);  // to-do: check if deck is empty, if yes, new deck
            table.print();
            player_sum = player_sum + table.cards.back().value;
            std::cout << "Player sum: " << player_sum << "\n";
            fmt::print("Next card?(y or n): ");
            char input;
            std::cin >> input;
            if((input == 'n') || (input == 'N') || (player_sum > 21))
            {
                break;
            }
        }
        if(player_sum == 21)
        {
            fmt::print("21! Player wins! \n");
            // to-do: player gets 1 point or something...
            break;
        }
        if(player_sum > 21)
        {
            fmt::print("Croupier wins!");
        }

        // croupier round
        static int croupier_sum = 0;
        for(int j; j < 4; j++)
        {
            put_on_table(deck, table);  // to-do: check if deck is empty, if yes, new deck
            table.print();
            croupier_sum = croupier_sum + table.cards.back().value;
            if((croupier_sum > 21) || (croupier_sum == 21))
            {
                break;
            }
        }
        if(croupier_sum == 21)
        {
            fmt::print("21!");
            // to-do: croupier gets 1 point or something...
            break;
        }
        if(croupier_sum > 21)
        {
            fmt::print("Player wins! \n");
        }
        else
        {
            if(player_sum < croupier_sum)
            {
                fmt::print("Croupier wins! \n");
            }
            if(player_sum > croupier_sum)
            {
                fmt::print("Player wins! \n");
            }
            if(player_sum == croupier_sum)
            {
                fmt::print("Stand-off! \n");
            }
        }
    }
    */