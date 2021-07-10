#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>

class Deck
{
private:
    std::vector<Card>* stack;
public:
    int size;
    Deck(int faces, int suits);
    void Shuffle();
    Card Take();
    std::vector<Card> Take(int i);
    Card& operator[](int i);
    void Add_Bottom(Card a);
    Deck();
};

#endif // DECK_H
