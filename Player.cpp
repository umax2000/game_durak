#include "Player.h"
#include <iostream>
#include "Pair.h"
using namespace std;

int Player::count = 0;

Player::Player() {}

Player::Player(std::wstring a)
{
    id = count++;
    this->name = a;
}

void Player::Take(std::vector<Pair> heap)
{
    for (size_t i = 0; i < heap.size(); i++)
    {
        vector<Card> temp = heap[i].Contains();
        hand.insert(hand.end(),
            std::make_move_iterator(temp.begin()),
            std::make_move_iterator(temp.end()));
    }
}

void Player::Take(int count, Deck& source)
{
    std::vector<Card> temp;
    //нужна проверка на то, что столько карт можно взять из колоды
    for (int i = 0; i < count; ++i)
    {
        if (source.size != 0)
            temp.push_back(source.Take());
    }

    //набор руки
    if ((hand.size() != 0) && (temp.size() != 0))
        hand.insert(hand.end(), temp.begin(), temp.end());
    else if (hand.size() == 0)
    {
        hand = temp;
    }
}

std::shared_ptr<Card> Player::Thrown() //вызывается при 1ом ходе
{
    while (1)
    {
        int choice = 0;
        wcout << this->name << L": choose card to thrown" << endl;
        for (size_t i = 0; i < hand.size(); i++)
        {
            wcout << i << ". " << hand[i].Print2() << endl;
        }
        cin >> choice;
        if (choice >= 0)
        {
            std::shared_ptr<Card> temp(new Card(hand[choice]));
            hand.erase(hand.begin() + choice);
            return temp;
        }
    }
}

std::shared_ptr<Card> Player::Thrown(vector<Pair>& heap)
//при 2-ух и последующих
{
    vector<Card> stack;
    for (size_t i = 0; i < heap.size(); i++)
    {
        vector<Card> tmp = heap[i].Contains();
        stack.insert(stack.end(), tmp.begin(), tmp.end());
    }
    while (1)
    {
        int choice = 0;
        wcout << L"Cards on table: ";
        for (size_t i = 0; i < stack.size(); i++)
            wcout << stack[i].Print2() << L" ";
        wcout << endl;
        wcout << this->name << L": choose card to thrown" << endl;
        wcout << L"-1. Nothing" << endl;
        for (size_t i = 0; i < hand.size(); i++)
        {
            wcout << i << ". " << hand[i].Print2() << endl;
        }
        cin >> choice;
        if (choice != -1)
        {
            for (size_t i = 0; i < stack.size(); i++)
                if (hand[choice].face == stack[i].face)
                {
                    std::shared_ptr<Card> temp(new Card(hand[choice]));
                    hand.erase(hand.begin() + choice);
                    return temp;
                }
        }
        else
        {
            return nullptr;
        }
    }
}

int Player::Answer(Pair& current, int trump)
{
    while (1)
    {
        int choice = 0;
        wcout << this->name << L": choose card to answer for "
            << current.first->Print2() << endl;
        wcout << L"-1. Give up" << endl;
        for (size_t i = 0; i < hand.size(); i++)
        {
            wcout << i << L". " << hand[i].Print2() << endl;
        }
        cin >> choice;
        if (choice != -1)
        {
            if (current.Beat(std::make_shared<Card>(hand[choice]), trump))
            {
                hand.erase(hand.begin() + choice);
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
}

void Player::Sort()
{
    for (size_t i = 0; i < hand.size(); ++i)
    {
        for (size_t j = i; j < hand.size(); ++j)
        {
            if (hand[i].id > hand[j].id)
                std::swap<Card>(hand[i], hand[j]);
        }
    }
}