#include "project4.h"

const char *illegal_exception::what() const
{
    return "illegal argument";
}

Pair::Pair() : vertex(-1), weight(DBL_MAX) {}

Pair::Pair(int v, double w) : vertex(v), weight(w) {}

BinaryHeap::BinaryHeap(int capacity)
{
    this->capacity = capacity;
    heapSize = 0;
    heapArr = new Pair[capacity];
    vertexToIndex = new int[capacity];

    // Initialize the lookup table
    for (int i = 0; i < capacity; i++)
    {
        vertexToIndex[i] = -1; // -1 indicates the vertex is not in the heap
    }
}

BinaryHeap::~BinaryHeap()
{
    delete[] heapArr;
    delete[] vertexToIndex;
}

void BinaryHeap::swap(Pair &a, Pair &b)
{
    int tempIndex = vertexToIndex[a.vertex];
    vertexToIndex[a.vertex] = vertexToIndex[b.vertex];
    vertexToIndex[b.vertex] = tempIndex;
    Pair temp = a;
    a = b;
    b = temp;
}

void BinaryHeap::heapify(int i)
{
    int smallest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < heapSize && heapArr[leftChild].weight < heapArr[smallest].weight)
    {
        smallest = leftChild;
    }

    if (rightChild < heapSize && heapArr[rightChild].weight < heapArr[smallest].weight)
    {
        smallest = rightChild;
    }

    if (smallest != i)
    {
        swap(heapArr[i], heapArr[smallest]);
        heapify(smallest);
    }
}

void BinaryHeap::insert(int vertex, double weight)
{
    int i = heapSize;
    vertexToIndex[vertex] = i;
    heapArr[i].vertex = vertex;
    heapArr[i].weight = weight;
    heapSize++;

    // restore the min heap
    while (i > 0 && heapArr[(i - 1) / 2].weight > heapArr[i].weight)
    {
        swap(heapArr[i], heapArr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Pair BinaryHeap::extractMin()
{
    Pair emptyPair(-1, DBL_MAX); // Return an empty pair if the heap is empty

    if (heapSize <= 0)
    {
        return emptyPair;
    }

    if (heapSize == 1)
    {
        heapSize--;
        return heapArr[0];
    }

    Pair root = heapArr[0];
    heapArr[0] = heapArr[heapSize - 1];
    heapSize--;

    // Restore the min heap property
    heapify(0);

    return root;
}

void BinaryHeap::update(int v, double newWeight)
{
    int i = vertexToIndex[v];
    heapArr[i].weight = newWeight;

    while (i >= 0 && heapArr[(i - 1) / 2].weight > heapArr[i].weight)
    {
        swap(heapArr[i], heapArr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool BinaryHeap::isEmpty()
{
    return heapSize == 0;
}

edgePair::edgePair()
{
    label = 0;
    vertex = 0;
}

edgePair::edgePair(int l, int v)
{
    label = l;
    vertex = v;
}

edgePair::~edgePair()
{
    label = 0;
    vertex = 0;
}

Edge::Edge()
{
    dest = edgePair(0, 0);
    src = edgePair(0, 0);
    weight = 0;
    A = 0;
    SD = 0;
}

Edge::Edge(edgePair s, edgePair d, double w, double a)
{
    dest = d;
    src = s;
    weight = w;
    A = a;
}

Edge::~Edge()
{
    dest = edgePair(0, 0);
    src = edgePair(0, 0);
    weight = 0;
    A = 0;
    SD = 0;
}

Graph::Graph(int cap)
{
    capacity = cap;
    numV = 0;
    size = 0;
    vListCap = cap;
    updateOnce = false;
    adjList = new Edge[capacity];
    vList = new int[vListCap];
}

void Graph::vListResize(int newCap)
{
    int *newVList = new int[newCap];
    for (int i = 0; i < numV; i++)
    {
        newVList[i] = vList[i];
    }
    delete[] vList;
    vList = newVList;
    vListCap = newCap;
}

void Graph::resize(int newCap)
{
    Edge *newAdjList = new Edge[newCap];
    for (int i = 0; i < capacity; i++)
    {
        newAdjList[i] = adjList[i];
    }
    delete[] adjList;
    adjList = newAdjList;
    capacity = newCap;
}

void Graph::insert(int a, int b, double d, double s)
{
    // Check if the graph needs to be resized
    if (size == capacity)
    {
        resize(capacity * 2);
    }
    if (numV + 2 == vListCap)
    {
        vListResize(vListCap * 2);
    }

    bool aExists = false;
    bool bExists = false;
    bool abExists = false;
    int indexAB = -1;
    int aVert = -1;
    int bVert = -1;
    double weight = d / s;

    for (int i{0}; i < size; i++)
    {
        if ((adjList[i].src.label == a && adjList[i].dest.label == b) ||
            (adjList[i].src.label == b && adjList[i].dest.label == a))
        {
            indexAB = i;
            aExists = true;
            bExists = true;
            abExists = true;
            break;
        }
    }
    for (int i{0}; i < numV; i++)
    {
        if (vList[i] == a)
        {
            aExists = true;
            aVert = i;
        }
        if (vList[i] == b)
        {
            bExists = true;
            bVert = i;
        }
    }

    if (abExists)
    {
        adjList[indexAB].SD = weight;
        adjList[indexAB].weight = adjList[indexAB].SD / adjList[indexAB].A;
    }
    else if (!aExists && !bExists)
    {
        Edge newEdge(edgePair(a, numV), edgePair(b, numV + 1), weight, 1);
        newEdge.SD = weight;
        adjList[size] = newEdge;
        size++;
        vList[numV] = a;
        vList[numV + 1] = b;
        numV += 2;
    }
    else if (aExists && !bExists)
    {
        Edge newEdge(edgePair(a, aVert), edgePair(b, numV), weight, 1);
        newEdge.SD = weight;
        adjList[size] = newEdge;
        size++;
        vList[numV] = b;
        numV++;
    }
    else if (bExists && !aExists)
    {
        Edge newEdge(edgePair(b, bVert), edgePair(a, numV), weight, 1);
        newEdge.SD = weight;
        adjList[size] = newEdge;
        size++;
        vList[numV] = a;
        numV++;
    }
    else
    {
        Edge newEdge(edgePair(a, aVert), edgePair(b, bVert), weight, 1);
        newEdge.SD = weight;
        adjList[size] = newEdge;
        size++;
    }
}

void Graph::load(fstream &fin)
{
    int a, b;
    double d, s;

    while (fin >> a >> b >> d >> s)
    {
        insert(a, b, d, s);
    }
}

bool Graph::print(int a)
{
    int indexA = -1;

    for (int i = 0; i < numV; i++)
    {
        if (vList[i] == a)
        {
            indexA = i;
            break;
        }
    }

    if (indexA == -1)
    {
        return false;
    }

    for (int i = 0; i < size; i++)
    {
        if (adjList[i].src.label == a || adjList[i].dest.label == a)
        {
            cout << (adjList[i].src.label == a ? adjList[i].dest.label : adjList[i].src.label) << " ";
        }
    }

    return true;
}

bool Graph::deleteVert(int a)
{
    // deleting from vertex list
    int indexA = -1;

    for (int i = 0; i < numV; i++)
    {
        if (vList[i] == a)
        {
            indexA = i;
            break;
        }
    }

    if (indexA == -1)
    {
        return false;
    }
    if (indexA != -1)
    {
        for (int i = indexA; i < numV - 1; i++)
        {
            vList[i] = vList[i + 1];
        }
        vList[numV - 1] = 0;
    }
    numV--;

    // Shift the adjacency list
    int i = 0;
    while (i < size)
    {
        if (adjList[i].src.label == a || adjList[i].dest.label == a)
        {

            for (int j = i; j < size - 1; j++)
            {
                adjList[j] = adjList[j + 1];
            }
            Edge emptyEdge;
            adjList[size - 1] = emptyEdge;
            size--;
        }
        else
        {
            i++;
        }
    }

    for (int i{0}; i < size; i++)
    {
        if (adjList[i].src.vertex > indexA)
        {
            adjList[i].src.vertex--;
        }
        if (adjList[i].dest.vertex > indexA)
        {
            adjList[i].dest.vertex--;
        }
    }

    return true;
}

bool Graph::path(int a, int b)
{
    int aVert = -1;
    int bVert = -1;
    for (int i = 0; i < size; i++)
    {
        if (adjList[i].src.label == a || adjList[i].dest.label == a)
        {
            aVert = adjList[i].src.label == a ? adjList[i].src.vertex : adjList[i].dest.vertex;
        }
        if (adjList[i].src.label == b || adjList[i].dest.label == b)
        {
            bVert = adjList[i].src.label == b ? adjList[i].src.vertex : adjList[i].dest.vertex;
        }
    }

    if (aVert == -1 || bVert == -1)
    {
        return false;
    }
    // Initialize distances and visited array

    double *dist = new double[numV];
    bool *visited = new bool[numV];
    int *parent = new int[numV];
    BinaryHeap minHeap(numV);

    for (int i{0}; i < numV; i++)
    {
        dist[i] = DBL_MAX;
        visited[i] = false;
        parent[i] = -1;
        minHeap.insert(i, DBL_MAX);
    }

    dist[aVert] = 0;
    minHeap.update(aVert, 0);

    while (!minHeap.isEmpty())
    {
        Pair current = minHeap.extractMin();
        int u = current.vertex;

        // Mark the current vertex as visited
        visited[u] = true;

        // Traverse the adjacency list of the current vertex
        for (int i = 0; i < size; ++i)
        {
            if (adjList[i].src.vertex == u || adjList[i].dest.vertex == u)
            {
                // cout << "found edge with " << u << endl;
                int v = (adjList[i].src.vertex == u) ? adjList[i].dest.vertex : adjList[i].src.vertex;
                // cout << "edge spans " << u << " to " << v << endl;
                double weight = adjList[i].weight;
                bool proceed = true;

                // Relaxation step
                if (!visited[v] && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    minHeap.update(v, dist[v]);
                }
            }
        }
    }

    // Output the vertices along the shortest path from 'a' to 'b'
    if (dist[bVert] == DBL_MAX)
    {
        delete[] dist;
        delete[] visited;
        delete[] parent;
        return false;
    }
    else
    {
        printPath(parent, bVert, a);
        delete[] dist;
        delete[] visited;
        delete[] parent;
        return true;
    }
}

void Graph::printPath(int parent[], int bVert, int aSrc)
{
    // Base Case: If j is the source
    if (parent[bVert] == -1)
    {
        cout << aSrc << " ";
        return;
    }

    printPath(parent, parent[bVert], aSrc);

    for (int i{0}; i < size; i++)
    {
        if (adjList[i].src.vertex == bVert || adjList[i].dest.vertex == bVert)
        {
            int printLabel = adjList[i].src.vertex == bVert ? adjList[i].src.label : adjList[i].dest.label;
            cout << printLabel << " ";
            return;
        }
    }
}

bool Graph::traffic(int a, int b, double newA)
{
    bool inGraph = false;

    for (int i = 0; i < size; i++)
    {
        if ((adjList[i].src.label == a && adjList[i].dest.label == b) || (adjList[i].src.label == b && adjList[i].dest.label == a))
        {
            inGraph = true;
        }
    }

    if (!inGraph || newA < 0 || newA > 1)
    {
        return false;
    }

    for (int i{0}; i < size; i++)
    {
        if ((adjList[i].src.label == a && adjList[i].dest.label == b) || (adjList[i].src.label == b && adjList[i].dest.label == a))
        {
            if (adjList[i].A != newA)
            {
                adjList[i].weight = newA != 0 ? adjList[i].SD / newA : DBL_MAX;
                adjList[i].A = newA;
                updateOnce = true;
            }
        }
    }
    return true;
}

bool Graph::update(fstream &fin)
{
    updateOnce = false;
    int a, b;
    double A;

    while (fin >> a >> b >> A)
    {
        traffic(a, b, A);
    }

    return updateOnce;
}

bool Graph::lowest(int a, int b)
{
    int aVert = -1;
    int bVert = -1;
    for (int i = 0; i < size; i++)
    {
        if (adjList[i].src.label == a || adjList[i].dest.label == a)
        {
            aVert = adjList[i].src.label == a ? adjList[i].src.vertex : adjList[i].dest.vertex;
        }
        if (adjList[i].src.label == b || adjList[i].dest.label == b)
        {
            bVert = adjList[i].src.label == b ? adjList[i].src.vertex : adjList[i].dest.vertex;
        }
    }

    if (aVert == -1 || bVert == -1)
    {
        return false;
    }

    double *dist = new double[numV];
    bool *visited = new bool[numV];
    BinaryHeap minHeap(numV);
    // Initialize distances and visited array
    for (int i{0}; i < numV; i++)
    {
        dist[i] = DBL_MAX;
        visited[i] = false;
        minHeap.insert(i, DBL_MAX);
    }

    dist[aVert] = 0;
    minHeap.update(aVert, 0);

    while (!minHeap.isEmpty())
    {
        Pair current = minHeap.extractMin();
        int u = current.vertex;
        // cout << "look at vertex " << u << endl;

        // Mark the current vertex as visited
        visited[u] = true;

        // Traverse the adjacency list of the current vertex
        for (int i = 0; i < size; ++i)
        {
            if (adjList[i].src.vertex == u || adjList[i].dest.vertex == u)
            {
                // cout << "found edge with " << u << endl;
                int v = (adjList[i].src.vertex == u) ? adjList[i].dest.vertex : adjList[i].src.vertex;
                // cout << "edge spans " << u << " to " << v << endl;
                double weight = adjList[i].weight;

                // Relaxation step
                if (!visited[v] && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    minHeap.update(v, dist[v]);
                }
            }
        }
    }

    // Output the vertices along the shortest path from 'a' to 'b'
    if (dist[bVert] == DBL_MAX)
    {
        delete[] dist;
        delete[] visited;
        return false;
    }
    else
    {
        cout << "lowest is " << dist[bVert];
        delete[] dist;
        delete[] visited;
        return true;
    }
}

Graph::~Graph()
{
    delete[] adjList;
    delete[] vList;
}
