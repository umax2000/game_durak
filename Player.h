#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Deck.h"
#include "Pair.h"

class Player
{
    static int count;
   
public:
    int id;
    std::wstring name;
    std::vector<Card> hand;
    Player();
    Player(Player& a);
    Player(std::wstring a);
    //    Player(std::string a, socket something);
    void Take(int count, Deck& source);
    void Take(std::vector<Pair> heap);
    std::shared_ptr<Card> Thrown();
    std::shared_ptr<Card> Thrown(std::vector<Pair>& heap);
    int Answer(Pair& current, int trump);
    void Sort();
};

#endif // PLAYER_H