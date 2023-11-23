#ifndef PROJECT_1
#define PROJECT_1

class Player
{
private:
    double x;
    double y;

public:
    Player *next;
    Player *prev;

    Player(double xstart, double ystart);

    double getX();

    double getY();

    void setX(double newX);

    void setY(double newY);

    ~Player();
};

class Game
{
private:
    Player *head;
    int count;

public:
    Game();

    void Spawn(double x, double y);

    void Time(double t);

    void Num();

    void PRT(double D);

    void Over();

    void Add(Player *newPlayer);

    void Remove(Player *deadPlayer);

    ~Game();
};

#endif