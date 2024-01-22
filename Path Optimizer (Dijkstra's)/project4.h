#ifndef PROJECT_4
#define PROJECT_4

#include <cfloat>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class illegal_exception
{
public:
    const char *what() const;
};

class Pair
{
public:
    int vertex;
    double weight;

    Pair();
    Pair(int v, double w);
};

class edgePair
{
public:
    edgePair();
    edgePair(int l, int v);
    int label;
    int vertex;
    ~edgePair();
};

class Edge
{
public:
    Edge();
    Edge(edgePair s, edgePair d, double w, double a);
    edgePair src;
    edgePair dest;
    double weight;
    double SD;
    double A;
    ~Edge();
};

class BinaryHeap
{
private:
    int capacity;
    Pair *heapArr;
    int heapSize;
    int *vertexToIndex;
    void swap(Pair &a, Pair &b);
    void heapify(int i);

public:
    BinaryHeap(int capacity);
    void insert(int vertex, double weight);
    Pair extractMin();
    void update(int v, double newWeight);
    bool isEmpty();
    ~BinaryHeap();
};

class Graph
{
private:
    int capacity; // total length of matrix/vertex list
    int size;
    int numV;
    int *vList;
    int vListCap;
    bool updateOnce;
    Edge *adjList;
    void resize(int newCap);
    void vListResize(int newCap);

public:
    Graph(int cap);
    void insert(int a, int b, double d, double s);
    void load(fstream &fin);
    bool print(int a);
    bool deleteVert(int a);
    void printPath(int parent[], int bVert, int aSrc);
    bool path(int a, int b);
    bool traffic(int a, int b, double newA);
    bool update(fstream &fin);
    bool lowest(int a, int b);
    ~Graph();
};

#endif