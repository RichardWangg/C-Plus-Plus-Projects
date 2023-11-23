#include "project3.h"

int main()
{
    QuadTree tree;
    while (true)
    {
        string cmd;
        cin >> cmd;

        if (cmd == "INIT")
        {
            int m;
            double x0, y0, x1, y1;
            cin >> m;
            cin >> x0;
            cin >> y0;
            cin >> x1;
            cin >> y1;
            try
            {
                if (x0 < x1 && y0 < y1)
                {
                    tree.init(m, x0, y0, x1, y1);
                }
                else
                {
                    throw illegal_exception();
                }
            }
            catch (const illegal_exception &ex)
            {
                cout << ex.what() << endl;
            }
        }
        if (cmd == "INSERT")
        {
            double x, y;
            cin >> x;
            cin >> y;
            if (tree.insert(x, y))
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        if (cmd == "SEARCH")
        {
            double x, y, d;
            cin >> x;
            cin >> y;
            cin >> d;
            if (tree.search(tree.getRoot(), x, y, d))
            {
                cout << "point exists" << endl;
            }
            else
            {
                cout << "no point exists" << endl;
            }
        }
        if (cmd == "NEAREST")
        {
            double x, y;
            cin >> x;
            cin >> y;
            tree.nearest(x, y);
        }
        if (cmd == "RANGE")
        {
            double xr0, yr0, xr1, yr1;
            cin >> xr0;
            cin >> yr0;
            cin >> xr1;
            cin >> yr1;
            try
            {
                if (xr0 < xr1 && yr0 < yr1)
                {
                    tree.setPointsInRange();
                    tree.range(tree.getRoot(), xr0, yr0, xr1, yr1);
                    if (!tree.getPointsInRange())
                    {
                        cout << "no points within range";
                    }
                    cout << endl;
                }
                else
                {
                    throw illegal_exception();
                }
            }
            catch (const illegal_exception &ex)
            {
                cout << ex.what() << endl;
            }
        }
        if (cmd == "NUM")
        {
            tree.num();
        }
        if (cmd == "EXIT")
        {
            break;
        }
    }
}