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

struct Shuffle_own_int
{
    void operator()(std::vector<int>::iterator begin, std::vector<int>::iterator end, int interations)
    {
        int deck_size = end - begin;
        std::cout << "deck size: " << deck_size << "\n";
        int rand1;
        int rand2;

        for (; begin != end; ++begin)
        {
            rand1 = get_random(0, deck_size - 1);
            rand2 = get_random(0, deck_size - 1);
            //swap<Card>(*(&begin + rand1), *(&begin + rand2));
            std::cout << "one iteration \n";
        }
    }
};

int main()
{
    auto a = [](int it){ 
        std::cout << "in lambda \n";
        return it + 1 ; };
    Shuffle_own shuf_own;
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

    std::vector<int> int_vec;
    int_vec.push_back(6);
    int_vec.push_back(7);
    int_vec.push_back(8);
    Shuffle_own_int shuffle;
    shuffle(int_vec.begin(), int_vec.end(), 1);
    //deck.aShuffle(shuf_own, 1);


    /*
    // state machine
    while(1)
    {
        switch (current_state)
        {
        case Init:
            fmt::print("\n +++ New game +++ \n");
            move_to_trash(table);
            deck.init_deck();
            deck.shuffle(100);
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
    */
    return 0;
}
