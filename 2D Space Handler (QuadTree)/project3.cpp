#include "project3.h"

const char *illegal_exception::what() const
{
    return "illegal argument";
}

Point::Point() : x(0), y(0){};

double Point::getX()
{
    return x;
};

double Point::getY()
{
    return y;
};

void Point::setX(double newX)
{
    x = newX;
};

void Point::setY(double newY)
{
    y = newY;
}

Point::~Point()
{
    y = 0, x = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Node::Node(int m, double x0, double y0, double x1, double y1) : left(nullptr), midLeft(nullptr), midRight(nullptr), right(nullptr)
{
    bound0.setX(x0);
    bound0.setY(y0);
    bound1.setX(x1);
    bound1.setY(y1);
    points = new Point[m];
    capacity = 0;
    index = 0;
};

Point Node::getBound0()
{
    return bound0;
};

Point Node::getBound1()
{
    return bound1;
};

Point Node::getPoint(int index)
{
    return points[index];
};

void Node::setPoint(int index, Point point)
{
    points[index] = point;
};

void Node::insertPoint(Point point)
{
    points[index] = point;
    index++;
    capacity++;
}

int Node::getCapacity()
{
    return capacity;
}

void Node::setCapacity(int c)
{
    capacity = c;
}

void Node::setIndex(int i)
{
    index = i;
}

Node::~Node()
{
    if (points != nullptr)
    {
        delete[] points;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QuadTree::QuadTree()
{
    root = nullptr;
    totalPoints = 0;
    size = 0;
    pointsInRange = false;
};

Node *QuadTree::treeSearch(double x, double y, Node *node)
{
    // getting values
    double x0 = node->getBound0().getX();
    double y0 = node->getBound0().getY();
    double x2 = node->getBound1().getX();
    double y2 = node->getBound1().getY();
    // midpoint
    double x1 = (x2 + x0) / 2;
    double y1 = (y2 + y0) / 2;

    // base case/leaf node
    if (node->left == nullptr && x >= x0 && x <= x2 && y >= y0 && y <= y2)
    {
        return node;
    }

    if ((x >= x0 && x <= x1) && (y >= y1 && y <= y2))
    {
        return treeSearch(x, y, node->left);
    }
    else if ((x > x1 && x <= x2) && (y >= y1 && y <= y2))
    {
        return treeSearch(x, y, node->midLeft);
    }
    else if ((x >= x0 && x <= x1) && (y >= y0 && y < y1))
    {
        return treeSearch(x, y, node->midRight);
    }
    else if ((x > x1 && x <= x2) && (y >= y0 && y < y1))
    {
        return treeSearch(x, y, node->right);
    }

    return nullptr;
};

void QuadTree::split(Node *fullNode)
{
    // Get the 4 new bounds
    double x0 = fullNode->getBound0().getX();
    double y0 = fullNode->getBound0().getY();
    double x2 = fullNode->getBound1().getX();
    double y2 = fullNode->getBound1().getY();
    // midpoint
    double x1 = (x2 + x0) / 2;
    double y1 = (y2 + y0) / 2;
    // make 4 new nodes with new bounds and assign children
    Node *leftChild = new Node(size, x0, y1, x1, y2);
    Node *midLeftChild = new Node(size, x1, y1, x2, y2);
    Node *midRightChild = new Node(size, x0, y0, x1, y1);
    Node *rightChild = new Node(size, x1, y0, x2, y1);
    fullNode->left = leftChild;
    fullNode->midLeft = midLeftChild;
    fullNode->midRight = midRightChild;
    fullNode->right = rightChild;
    Point empty;
    // assign points to children
    for (int i{0}; i < fullNode->getCapacity(); i++)
    {
        Point point = fullNode->getPoint(i);
        double x = point.getX();
        double y = point.getY();
        // left child (top left box)
        if ((x >= x0 && x <= x1) && (y >= y1 && y <= y2))
        {
            fullNode->left->insertPoint(point);
        } // middle left (top right box)
        if ((x > x1 && x <= x2) && (y >= y1 && y <= y2))
        {
            fullNode->midLeft->insertPoint(point);
        } // middle right (bottom left box)
        if ((x >= x0 && x <= x1) && (y >= y0 && y < y1))
        {
            fullNode->midRight->insertPoint(point);
        } // right (bottom right)
        if ((x > x1 && x <= x2) && (y >= y0 && y < y1))
        {
            fullNode->right->insertPoint(point);
        }
        // empty points in the full node
        fullNode->setPoint(i, empty);
        fullNode->setIndex(0);
    }
};

void QuadTree::deleteTree(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    deleteTree(node->midLeft);
    deleteTree(node->midRight);
    delete node;
}

void QuadTree::inRange(Node *node, double x0, double y0, double x1, double y1)
{
    for (int i{0}; i < node->getCapacity(); i++)
    {
        Point point = node->getPoint(i);
        double x = point.getX();
        double y = point.getY();

        if ((x > x0 && x < x1) && (y > y0 && y < y1))
        {
            cout << x << " " << y << " ";
            pointsInRange = true;
        }
    }
}

void QuadTree::findNearest(Node *node, double x, double y)
{
    if (node->left == nullptr)
    {
        for (int i{0}; i < node->getCapacity(); i++)
        {
            double x1 = node->getPoint(i).getX();
            double y1 = node->getPoint(i).getY();
            double distance = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));

            if (firstDist)
            {
                firstDist = false;
                shortestDist = distance;
                shortestPoint.setX(x1);
                shortestPoint.setY(y1);
            }
            else if (distance < shortestDist)
            {
                shortestDist = distance;
                shortestPoint.setX(x1);
                shortestPoint.setY(y1);
            }
            else if (distance == shortestDist)
            {
                if (x1 > shortestPoint.getX())
                {
                    shortestPoint.setX(x1);
                    shortestPoint.setY(y1);
                }
                else if (x1 == x && y1 > y)
                {
                    shortestPoint.setX(x1);
                    shortestPoint.setY(y1);
                }
            }
        }
        return;
    }
    findNearest(node->left, x, y);
    findNearest(node->midLeft, x, y);
    findNearest(node->midRight, x, y);
    findNearest(node->right, x, y);
}

void QuadTree::splitRecurs(Node *node, double x, double y)
{

    if (node == nullptr)
    {
        return;
    }
    if (node->getCapacity() < size)
    {
        return;
    }
    split(node);
    Node *searchedNode = treeSearch(x, y, node);
    splitRecurs(searchedNode, x, y);
    return;
}

Node *QuadTree::getRoot()
{
    return root;
}

void QuadTree::init(int m, double x0, double y0, double x1, double y1)
{
    root = new Node(m, x0, y0, x1, y1);
    size = m;
    cout << "success" << endl;
};

bool QuadTree::insert(double x, double y)
{
    Point insertPoint;
    insertPoint.setX(x);
    insertPoint.setY(y);
    Node *searchedNode = treeSearch(x, y, root);

    if (searchedNode == nullptr)
    {
        return false;
    }
    // checking for duplicates
    for (int i{0}; i < searchedNode->getCapacity(); i++)
    {
        Point point = searchedNode->getPoint(i);
        if ((insertPoint.getX() == point.getX()) && (insertPoint.getY() == point.getY()))
        {
            return false;
        }
    }

    if (searchedNode->getCapacity() == size)
    {
        splitRecurs(searchedNode, x, y);
        searchedNode = treeSearch(x, y, searchedNode);
    }

    searchedNode->insertPoint(insertPoint);
    totalPoints++;
    return true;
};

bool QuadTree::search(Node *node, double x, double y, double d)
{
    if (node->left == nullptr)
    {
        for (int i{0}; i < node->getCapacity(); i++)
        {
            Point point = node->getPoint(i);
            double x1 = point.getX();
            double y1 = point.getY();
            double distance = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
            if ((distance < d) || (d == 0 && x1 == x && y1 == y))
            {
                return true;
            }
        }
        return false;
    }

    return search(node->left, x, y, d) ||
           search(node->midLeft, x, y, d) ||
           search(node->midRight, x, y, d) ||
           search(node->right, x, y, d);
}

void QuadTree::nearest(double x, double y)
{
    if (totalPoints == 0)
    {
        cout << "no point exists" << endl;
        return;
    }
    firstDist = true;
    findNearest(root, x, y);
    cout << shortestPoint.getX() << " " << shortestPoint.getY() << endl;
};

void QuadTree::range(Node *node, double x0, double y0, double x1, double y1)
{
    if (node->left == nullptr)
    {
        inRange(node, x0, y0, x1, y1);
        return;
    }

    double xMid = (node->getBound1().getX() + node->getBound0().getX()) / 2;
    double yMid = (node->getBound1().getY() + node->getBound0().getY()) / 2;

    if (x0 <= xMid && y1 >= yMid)
    {
        range(node->left, x0, y0, x1, y1);
    }
    if (x1 > xMid && y1 >= yMid)
    {
        range(node->midLeft, x0, y0, x1, y1);
    }
    if (x0 <= xMid && y0 < yMid)
    {
        range(node->midRight, x0, y0, x1, y1);
    }
    if (x1 > xMid && y0 < yMid)
    {
        range(node->right, x0, y0, x1, y1);
    }
    return;
};

void QuadTree::setPointsInRange()
{
    pointsInRange = false;
}

bool QuadTree::getPointsInRange()
{
    return pointsInRange;
}
void QuadTree::num()
{
    cout << totalPoints << endl;
};

QuadTree::~QuadTree()
{
    deleteTree(root);
};