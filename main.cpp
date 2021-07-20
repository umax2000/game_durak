#include <iostream>
#include "Deck.h"
#include "Player.h"
#include <cstdlib>
#include <memory>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    Deck my(13, 4);
    my.Shuffle();

    std::vector<Player> players(3);
    players[0] = Player(L"1");
    players[1] = Player(L"2");
    players[2] = Player(L"3");

    //¬сем игрокам раздаетс€ по 6 карт.
    for (Player& pl : players)
    {
        pl.Take(6, my);
        pl.Sort();//сортировка в пор€дке увеличени€
    }

    //¬ыбираетс€ козырь.
    Card trump_card = my.Take();
    int trump = trump_card.suit;
    wcout << L"Current trump:"
        << trump_card.Print2() << endl;
    my.Add_Bottom(trump_card);/* ¬озвращаем козырь
    в колоду*/

    //¬ыбираетс€ игрок с козырем наименьшего значени€.
    size_t tmin = 100;
    size_t apl = 0;
    for (size_t i = 0; i < players.size(); ++i)
    {
        for (size_t j = 0; j < players[i].hand.size(); ++j)
        {
            if ((players[i].hand[j].suit == trump) 
                && (players[i].hand[j].face < tmin))
            {
                tmin = players[i].hand[j].face;
                apl = i;
            }
        }
    };
    int vpl = (apl + 1);
    wcout << L"Player " << players[apl].name
        << L" has lowest trump-card" << endl;

    //MAIN LOOP
    while (1)
    {
        bool vpl_take = false;
        vector<Pair> heap;
        shared_ptr<Card> temp = players[apl].Thrown();
        heap.push_back(Pair(temp));
        while (1)
        {
            if (players[vpl].Answer(heap[heap.size() - 1], trump) == 1)
            {
                players[vpl].Take(heap);
                vpl_take = true;
                break;
            }
            else if (players[vpl].hand.size() == 0)
                break;
            shared_ptr<Card> temp = players[apl].Thrown(heap);
            if (temp == nullptr)
            {
                break;
            }
            heap.push_back(Pair(temp));
        }
        if ((!vpl_take) && (players[vpl].hand.size() != 0))
        {
            while (1)
            {
                for (int i = (apl + 2) % players.size();
                    i != (apl + 1) % players.size();
                    i = (i + 1) % players.size())
                {
                    if (i == vpl) continue;

                    shared_ptr<Card> temp = players[i].Thrown(heap);
                    if (temp == nullptr)
                    {
                        continue;
                    }
                    else
                    {
                        heap.push_back(Pair(temp));
                        break;
                    }
                }
                if (heap[heap.size() - 1].second == nullptr)
                {
                    if (players[vpl].Answer(heap[heap.size() - 1], trump) == 1)
                    {
                        players[vpl].Take(heap);
                        vpl_take = true;
                        break;
                    }
                    else if (players[vpl].hand.size() == 0)
                        break;
                }
                else
                {
                    break;
                }
            }
        }
        wcout << L"End of a turn" << endl;
        if (players[apl].hand.size() < 6)
            players[apl].Take((6 - players[apl].hand.size()), my);

        for (int i = (apl + 2) % players.size();
            i != apl;
            i = (i + 1) % players.size())
        {
            if (i == vpl) continue;

            if (players[i].hand.size() < 6)
                players[i].Take((6 - players[i].hand.size()), my);
        }
        //vpl берет последним
        if (players[vpl].hand.size() < 6)
            players[vpl].Take((6 - players[vpl].hand.size()), my);
        //удаление игрока из вектора
        for (size_t i = 0; i < players.size(); i++)
        {
            if (players[i].hand.size() == 0)
            {
                players.erase(players.begin() + i);
                if (i <= apl)
                {
                    apl = (apl - 1) % players.size();
                    if ((vpl < apl) && (apl == i))
                        vpl = (vpl) % players.size();
                    else
                        vpl = (vpl - 1) % players.size();
                }
                i = (i - 1) % players.size();
            }
        }
        //         огда осталс€ 1 игрок - он считаетс€ проигравшим.
        if (players.size() == 1)
        {
            wcout << L"Player " << players[0].name << L" is a durak!" << endl;
            break;
        }
        else if (players.size() == 0)
        {
            wcout << L"Draw!";
            break;
        }
        if (!vpl_take)
        {
            apl = vpl;
            vpl = (apl + 1) % players.size();
        }
    }
    return 0;
}