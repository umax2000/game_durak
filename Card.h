#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
public:
    int id;
    static int count;
    std::wstring cfaces[13] = { L"2", L"3", L"4", L"5",
        L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K", L"A" };
    std::wstring csuits[4] = { L" of Clubs",L" of Diamonds",
        L" of Hearts",L" of Spades" };
    size_t face;
    size_t suit;
    Card();
    Card(size_t face, size_t suit);
    int Fight(Card& a, size_t trump);
    std::string Print();
    std::wstring Print2();
};

#endif // CARD_H
