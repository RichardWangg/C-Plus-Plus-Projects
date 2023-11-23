#ifndef PROJECT_3
#define PROJECT_3
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
using namespace std;

class illegal_exception
{
public:
    const char *what() const;
};

class Point
{
private:
    double x;
    double y;

public:
    Point();
    double getX();
    double getY();
    void setX(double newX);
    void setY(double newY);
    ~Point();
};

class Node
{
private:
    Point bound0;
    Point bound1;
    int capacity;
    Point *points;
    int index;

public:
    Node *left;
    Node *right;
    Node *midLeft;
    Node *midRight;

    Node(int m, double x0, double y0, double x1, double y1);
    Point getBound0();
    Point getBound1();
    Point getPoint(int index);
    void setPoint(int index, Point point);
    void insertPoint(Point point);
    int getCapacity();
    void setCapacity(int c);
    void setIndex(int i);
    ~Node();
};

class QuadTree
{
public:
    QuadTree();
    Node *treeSearch(double x, double y, Node *node);
    void split(Node *fullNode);
    void splitRecurs(Node *node, double x, double y);
    void deleteTree(Node *node);
    void inRange(Node *node, double x0, double y0, double x1, double y1);
    void findNearest(Node *node, double x, double y);
    Node *getRoot();
    void setPointsInRange();
    bool getPointsInRange();

    void init(int m, double x0, double y0, double x1, double y1);
    bool insert(double x, double y);
    bool search(Node *node, double x, double y, double d);
    void nearest(double x, double y);
    void range(Node *node, double x0, double y0, double x1, double y1);
    void num();

    ~QuadTree();

private:
    Node *root;
    int totalPoints;
    int size;
    Point shortestPoint;
    double shortestDist;
    bool firstDist;
    bool pointsInRange;
};

#endif