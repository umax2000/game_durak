#include "Deck.h"
#include <time.h>
#include <algorithm>
#include <random>
#include <stdlib.h>
Deck::Deck() {}
Deck::Deck(int faces, int suits)
{
    int count = faces * suits;
    this->stack = new std::vector<Card>(count);
    for (int i = 0; i < count; ++i)
    {
        stack->at(i) = Card(i % faces, i / faces);
    }
    this->size = count;
}
int randomfunc(int j)
{
    return rand() % j;
}

void Deck::Shuffle()
{
    srand(time(NULL));
    random_shuffle(stack->begin(), stack->end(), randomfunc);
}

Card Deck::Take()
{
    if (size != 0)
    {
        Card temp = stack->back();
        stack->pop_back();
        --size;
        return temp;
    }
    else
    {
        return Card();
    }

}

std::vector<Card> Deck::Take(int i)
{
    std::vector<Card> temp(i);
    for (int j = 0; j < i; ++j)
    {
        temp[j] = this->Take();
    }
    return temp;
}

Card& Deck::operator [](int i)
{
    return stack->at(i);
}

void Deck::Add_Bottom(Card a)
{
    stack->insert(stack->begin(), a);
}