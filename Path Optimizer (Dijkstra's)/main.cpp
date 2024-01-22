#include "project4.h"

int main()
{
    Graph graph(500000);
    while (true)
    {
        string cmd;
        cin >> cmd;

        if (cmd == "LOAD")
        {
            string filename;
            cin >> filename;
            fstream fin(filename.c_str());

            graph.load(fin);
            cout << "success" << endl;
        }
        if (cmd == "INSERT")
        {
            int a, b;
            double d, s;
            cin >> a;
            cin >> b;
            cin >> d;
            cin >> s;

            try
            {
                if (a >= 1 && a <= 500000 && b >= 1 && b <= 500000 && s > 0 && d > 0)
                {
                    graph.insert(a, b, d, s);
                    cout << "success" << endl;
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
        if (cmd == "PRINT")
        {
            int a;
            cin >> a;

            try
            {
                if (a >= 1 && a <= 500000)
                {
                    if (!graph.print(a))
                    {
                        cout << "failure" << endl;
                    }
                    else
                    {
                        cout << endl;
                    }
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
        if (cmd == "DELETE")
        {
            int a;
            cin >> a;

            try
            {
                if (a >= 1 && a <= 500000)
                {
                    if (graph.deleteVert(a))
                    {
                        cout << "success" << endl;
                    }
                    else
                    {
                        cout << "failure" << endl;
                    }
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
        if (cmd == "PATH")
        {
            int a, b;
            cin >> a;
            cin >> b;

            try
            {
                if (a >= 1 && a <= 500000 && b >= 1 && b <= 500000)
                {
                    if (!graph.path(a, b))
                    {
                        cout << "failure" << endl;
                    }
                    else
                    {
                        cout << endl;
                    }
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
        if (cmd == "TRAFFIC")
        {
            int a, b;
            double adj;
            cin >> a;
            cin >> b;
            cin >> adj;
            try
            {
                if (a >= 1 && a <= 500000 && b >= 1 && b <= 500000)
                {
                    if (graph.traffic(a, b, adj))
                    {
                        cout << "success" << endl;
                    }
                    else
                    {
                        cout << "failure" << endl;
                    }
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
        if (cmd == "UPDATE")
        {
            string filename;
            cin >> filename;
            fstream fin(filename.c_str());

            if (graph.update(fin))
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        if (cmd == "LOWEST")
        {
            int a, b;

            cin >> a;
            cin >> b;
            try
            {
                if (a >= 1 && a <= 500000 && b >= 1 && b <= 500000)
                {
                    if (!graph.lowest(a, b))
                    {
                        cout << "failure" << endl;
                    }
                    else
                    {
                        cout << endl;
                    }
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
        if (cmd == "END")
        {
            break;
        }
    }
}