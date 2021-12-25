#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<fmt/format.h>

enum
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
} typedef Symbol_t;


struct Card
{
    Symbol_t symbol;
    int value;

    explicit Card(Symbol_t sym, int val)
    {
        if(val < 1 || val > 12)
        {
            throw std::runtime_error("Wrong card value!");
        }
        if(sym > 3 || sym < 0)
        {
            throw std::runtime_error("Wrong card symbol!");
        }
        this->value = val;
        this->symbol = sym;
    }

    friend std::ostream& operator<<(std::ostream& os, Card const& c)
    {
        std::string print_symbol;
        std::string print_value;
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

        switch (c.value)
        {
        case 10:
            print_value = "Jack";
            break;
        case 11:
            print_value = "Queen";
            break;
        case 12:
            print_value = "King";
            break;
        case 13:
            print_value = "Ass";
            break;
        default:
            print_value = std::to_string(c.value);
            break;
        }

        os << print_symbol << ", " << print_value << "\n";
        return os;
    }
};

struct Deck
{
    std::vector<Card> cards;

    void init_deck()
    {
        for (int intSymbol = 0; intSymbol < 4; intSymbol++)
        {
            for (size_t value = 0; value < 12; value++)
            {
                Symbol_t symbol = static_cast<Symbol_t>(intSymbol);
                cards.push_back(Card{symbol, value + 1});
            }
        }
    }
    void print()
    {
        for (size_t i = 0; i < 52; i++)
        {
            std::cout << "card" << i + 1 << cards[i];
        }
        
    }

};

int main()
{
    fmt::print("Welcome to Black-Jack! \n");
    Deck d;
    d.init_deck();
    d.print();
    return 0;
}
