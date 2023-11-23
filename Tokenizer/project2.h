#ifndef PROJECT_2
#define PROJECT_2

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class WordTokenPair
{
public:
    WordTokenPair(string newWord, int newToken);

    string getWord();
    int getToken();
    int getKey();
    void setKey(int newKey);
    WordTokenPair *next;

    ~WordTokenPair();

private:
    string word;
    int token;
    int key;
};

class Tokenizer // hashmap
{
public:
    Tokenizer();
    void M(int m);

    bool insert(string word);
    bool read(fstream &fin);
    void tokenize(string word);
    void retrieve(int token);
    void stok(string sentence);
    void toks(string tokens);
    void print(int index);

    int hash(string word);
    int dictionaryInsert(string word);

    ~Tokenizer();

private:
    WordTokenPair **hashMap;
    int size;
    string *dictionary;
    int capacity;
    int currentDictSize;
};

#endif