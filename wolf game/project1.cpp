#include "project1.h"
#include <iostream>
#include <cmath>
using namespace std;

Player::Player(double xstart, double ystart)
{
    x = xstart;
    y = ystart;
    next = nullptr;
    prev = nullptr;
}

double Player::getX()
{
    return x;
}

double Player::getY()
{
    return y;
}

void Player::setX(double newX)
{
    x = newX;
}

void Player::setY(double newY)
{
    y = newY;
}

Player::~Player()
{
    next = nullptr;
    prev = nullptr;
}

Game::Game()
{
    head = nullptr;
    count = 0;
}

void Game::Spawn(double x, double y)
{
    if (x > 0 && y > 0)
    {
        Player *newplayer = new Player(x, y);
        Add(newplayer);
        count++;
        cout << "success\n";
    }
    else
    {
        cout << "failure\n";
    }
};

void Game::Time(double t)
{
    Player *temp = head;
    while (temp != nullptr)
    {
        Player *nextPlayer = temp->next;
        double x = temp->getX();
        double y = temp->getY();

        if (t > 0)
        {
            double deltaX = t * cos(atan2(y, x));
            double deltaY = t * sin(atan2(y, x));
            temp->setX(x - deltaX);
            temp->setY(y - deltaY);
            if (temp->getX() < 0 || temp->getY() < 0)
            {
                Remove(temp);
                count--;
            }
        }
        else
        {
            double distance = sqrt(x * x + y * y);
            if (distance < 1)
            {
                Remove(temp);
                count--;
            }
        }

        temp = nextPlayer;
    }
    Num();
}

void Game::Num()
{
    cout << "number of children still playing: " << count << "\n";
}

void Game::PRT(double D)
{
    Player *current = head;
    int no_child = 0;

    while (current != nullptr)
    {
        double distance = sqrt(current->getX() * current->getX() + current->getY() * current->getY());
        if (distance < D)
        {
            cout << current->getX() << " " << current->getY() << " ";
            no_child++;
        }
        current = current->next;
    }

    if (no_child == 0)
    {
        cout << "no children within distance";
    }

    cout << "\n";
}

void Game::Over()
{
    if (count > 0)
    {
        cout << "the players win\n";
    }
    else
    {
        cout << "the wolf wins\n";
    }
}

void Game::Add(Player *newPlayer)
{
    if (head == nullptr)
    {
        head = newPlayer;
    }
    else
    {
        newPlayer->next = head;
        head->prev = newPlayer;
        head = newPlayer;
    }
}

void Game::Remove(Player *deadPlayer)
{
    if (head == nullptr || deadPlayer == nullptr)
    {
        return;
    }

    Player *temp2 = deadPlayer->prev;
    Player *temp = deadPlayer->next;

    if (temp2 != nullptr)
    {
        temp2->next = temp;
    }
    else
    {
        head = temp;
    }

    if (temp != nullptr)
    {
        temp->prev = temp2;
    }

    delete deadPlayer;
}

Game::~Game()
{
    while (head != nullptr)
    {
        Player *temp = head;
        head = head->next;
        delete temp;
    }
}
