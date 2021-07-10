#include "Card.h"
int Card::count = 0;
Card::Card() {}

Card::Card(size_t face, size_t suit)
{
    id = count++;
    this->face = face;
    this->suit = suit;
}

// 0 если бьем, 1 иначе
int Card::Fight(Card& a, size_t trump)
{
    if (this->suit == a.suit)
        return ((this->face > a.face) ? 0 : 1);
    else if ((this->suit == trump) && (a.suit != trump))
        return 0;
    else
        return 1;
}

std::string Card::Print()
{
    char temp[10];
    sprintf_s(temp, "%d of %d", this->face, this->suit);
    return std::string(temp);
}

std::wstring Card::Print2()
{
    return std::wstring(cfaces[face] + csuits[suit]);
}
