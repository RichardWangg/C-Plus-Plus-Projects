#include "project2.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    Tokenizer tokenizer;
    while (true)
    {
        string cmd;
        cin >> cmd;

        if (cmd == "M")
        {
            int m;
            cin >> m;
            tokenizer.M(m);
        }
        if (cmd == "INSERT")
        {
            string word;
            cin >> word;
            if (tokenizer.insert(word))
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        if (cmd == "READ")
        {
            string filename;
            cin >> filename;
            fstream fin(filename.c_str());

            if (tokenizer.read(fin))
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        if (cmd == "TOKENIZE")
        {
            string word;
            cin >> word;
            tokenizer.tokenize(word);
            cout << endl;
        }
        if (cmd == "RETRIEVE")
        {
            int t;
            cin >> t;
            tokenizer.retrieve(t);
            cout << endl;
        }
        if (cmd == "STOK")
        {
            string sentence;
            getline(cin >> ws, sentence);
            tokenizer.stok(sentence);
            cout << endl;
        }
        if (cmd == "TOKS")
        {
            string sentence;
            getline(cin >> ws, sentence);
            tokenizer.toks(sentence);
            cout << endl;
        }
        if (cmd == "PRINT")
        {
            int k;
            cin >> k;
            tokenizer.print(k);
            cout << endl;
        }
        if (cmd == "EXIT")
        {
            break;
        }
    }
}
