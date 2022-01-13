#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <string>
//#include<fmt/format.h>
//TODO enums to class
enum
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
} typedef Symbol_t;
enum
{
    Jack = 11,
    Queen,
    King,
    Ace
} typedef Name_t;

int get_random(int a, int b)
{
    int rand;
    std::random_device rand_dev;
    std::mt19937 rng(rand_dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(a, b);
    rand = dist(rng);
    return rand;
}

struct Card
{
    Symbol_t symbol;
    Name_t name;
    unsigned int value;

    explicit Card(Symbol_t sym, Name_t n)
    {
        if (sym > 3 || sym < 0)
        {
            throw std::runtime_error("Wrong card symbol!");
        }
        if (n < 2 || n > 14)
        {
            throw std::runtime_error("Wrong card name!");
        }
        if ((n == Ace))
        {
            this->value = 11;
        }
        else
        {
            this->value = 10;
        }
        this->symbol = sym;
        this->name = n;
    }
    explicit Card(Symbol_t sym, unsigned int val)
    {
        if (val < 2 || val > 10)
        {
            throw std::runtime_error("Wrong card value!");
        }
        if (sym > 3 || sym < 0)
        {
            throw std::runtime_error("Wrong card symbol!");
        }
        this->value = val;
        this->symbol = sym;
        this->name = static_cast<Name_t>(val);
    }

    friend std::ostream &operator<<(std::ostream &os, Card const &c)
    {
        std::string print_symbol;
        std::string print_name;
        switch (c.symbol)
        {
        case Hearts:
            print_symbol = "Hearts";
            break;
        case Diamonds:
            print_symbol = "Diamonds";
            break;
        case Clubs:
            print_symbol = "Clubs";
            break;
        case Spades:
            print_symbol = "Spades";
            break;
        default:
            break;
        }

        switch (c.name)
        {
        case 11:
            print_name = "Jack";
            break;
        case 12:
            print_name = "Queen";
            break;
        case 13:
            print_name = "King";
            break;
        case 14:
            print_name = "Ace";
            break;
        default:
            print_name = std::to_string(c.name);
            break;
        }

        os << print_symbol << ", " << print_name << "\n";
        return os;
    }
};

struct Deck
{
    std::vector<Card> cards;
    
    friend std::ostream &operator<<(std::ostream &os, Deck const &d)
    {
        for (size_t i = 0; i < d.cards.size(); i++)
        {
            os << "card" << i + 1 << "\t" << d.cards.at(i);
        }
        return os;
    }

    void generate_face_cards()
    {
        for (unsigned int intSymbol = 0; intSymbol < 4; intSymbol++)
        {
            for (unsigned int intName = 11; intName < 15; intName++)
            {
                cards.push_back(Card(static_cast<Symbol_t>(intSymbol), static_cast<Name_t>(intName)));
            }
        }
    }
    void generate_num_cards()
    {
        for (unsigned int intSymbol = 0; intSymbol < 4; intSymbol++)
        {
            for (unsigned int val = 2; val < 11; val++)
            {
                cards.push_back(Card(static_cast<Symbol_t>(intSymbol), val));
            }
        }
    }

    void init_deck()
    {
        generate_num_cards();
        generate_face_cards();
    }

    template <typename P>
    void shuffle(P alg, int iterations)
    {
        /* Hallo Christoph,
         * hier eine sinnvolle shuffle-Implementierung, ich habe mich
         * aber für meine (weniger sinnvolle) entschieden, weil ich dann
         * da schön Funktionen als Templateparameter übergeben kann
        std::random_device rand_dev;
        std::mt19937 rng(rand_dev());
        std::shuffle(cards.begin(), cards.end(), rng);
         */
        alg(cards, iterations);
    }

    size_t size()
    {
        return cards.size();
    }

    Card back()
    {
        return cards.back();
    }
};

/**
 * @brief swaps two random cards of the deck
 */
auto TRCShuffle = [](std::vector<Card> &cards, std::size_t iterations)
{
    size_t deck_size = cards.size();
    int rand1;
    int rand2;

    for (std::size_t i = 0; i < iterations; i++)
    {
        rand1 = get_random(0, deck_size - 1);
        rand2 = get_random(0, deck_size - 1);
        std::swap<Card>(cards.at(rand1), cards.at(rand2));
    }
    std::cout << "Deck is shuffled \n";
};

/**
 * @brief swaps the first card with a random card of the deck (Fisher-Yates algorithm)
 */
auto FYShuffle = [](std::vector<Card> &cards, std::size_t iterations)
{
    std::size_t deck_size = cards.size();
    int rand1;

    for (std::size_t i = 0; i < iterations; i++)
    {
        rand1 = get_random(0, deck_size - 1);
        std::swap<Card>(cards.at(rand1), cards.at(0));
    }
    std::cout << "Deck is shuffled \n";
};

/**
 * @brief puts one card from the deck on the table and prints it
 * @param deck
 * @param table
 * @return int, -1 if deck is empty, 1 of deck is not empty
 */
int put_on_table(Deck &deck, Deck &table)
{
    if (!deck.cards.empty())
    {
        Card buffer = deck.cards.back();
        deck.cards.pop_back();
        table.cards.push_back(buffer);
        std::cout << "Card put on the table: ";
        std::cout << buffer << "\n";
        return 1;
    }
    else
    {
        return -1;
    }
}

void move_to_trash(Deck &table)
{
    while (!table.cards.empty())
    {
        table.cards.pop_back();
    }
}
