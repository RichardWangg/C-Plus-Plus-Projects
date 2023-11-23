#include "project2.h"
#include <iostream>
#include <string>
using namespace std;

// the class for each (word, number) pair (each node in the linked list)
WordTokenPair::WordTokenPair(string newWord, int newToken)
{
    word = newWord;
    token = newToken;
    int key = 0;
    next = nullptr;
}

string WordTokenPair::getWord()
{
    return word;
}

int WordTokenPair::getToken()
{
    return token;
}

int WordTokenPair::getKey()
{
    return key;
}

void WordTokenPair::setKey(int newKey)
{
    key = newKey;
}

WordTokenPair::~WordTokenPair()
{
    next = nullptr;
}

// the class for the tokenizer (hashmap)
Tokenizer::Tokenizer()
{
    size = 0;
    capacity = 0;
    currentDictSize = 0;
    hashMap = nullptr;
    dictionary = nullptr;
}

void Tokenizer::M(int m) // MAKE command will just make an instance of this
{
    hashMap = new WordTokenPair *[m];
    size = m;
    capacity = m;
    dictionary = new string[capacity];

    for (int i{0}; i < size; i++)
    {
        hashMap[i] = nullptr;
    }

    cout << "success" << endl;
}

bool Tokenizer::insert(string word)
{
    int key = hash(word);
    int index = key % size;
    // checking for duplicates and non alpabetical characters
    bool proceed = true;
    WordTokenPair *current = hashMap[index];

    while (current != nullptr)
    {
        if (current->getWord() == word)
        {
            proceed = false;
        }
        current = current->next;
    }

    for (int i{0}; i < word.length(); i++)
    {
        char ascii = word[i];
        if (!((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)))
        {
            proceed = false;
        }
    }

    // inserting into dictionary and storing the index(token)

    if (proceed)
    {
        int token = dictionaryInsert(word);
        WordTokenPair *newPair = new WordTokenPair(word, token);
        newPair->next = hashMap[index];
        hashMap[index] = newPair;
        newPair->setKey(key);
    }

    return proceed;
}

bool Tokenizer::read(fstream &fin)
{
    string toRead;
    bool insertedOnce = false;

    while (fin >> toRead)
    {
        if (!insertedOnce && insert(toRead))
        {
            insertedOnce = true;
        }
        insert(toRead);
    }

    return insertedOnce;
}

void Tokenizer::tokenize(string word)
{
    int key = hash(word);
    int index = key % size;

    bool wordDNE = true;

    WordTokenPair *current = hashMap[index];
    while (current != nullptr)
    {
        if (current->getWord() == word)
        {
            cout << current->getToken() << " ";
            wordDNE = false;
        }
        current = current->next;
    }

    if (wordDNE)
    {
        cout << 0 << " ";
    }
}

void Tokenizer::retrieve(int token)
{
    token--;
    if (token >= 0 && token < currentDictSize && !dictionary[token].empty())
    {
        cout << dictionary[token] << " ";
    }
    else
    {
        cout << "UNKNOWN ";
    }
}

void Tokenizer::stok(string sentence)
{
    sentence.erase(sentence.find_last_not_of(" \t\n\r\f\v") + 1);
    string word = "";

    for (int i{0}; i < sentence.length(); i++)
    {
        if (sentence[i] == ' ')
        {
            if (word != "_DONE_")
            {
                tokenize(word);
            }
            word = "";
        }
        else
        {
            word += sentence[i];
        }
    }
}

void Tokenizer::toks(string tokens)
{
    tokens.erase(tokens.find_last_not_of(" \t\n\r\f\v") + 1);
    string token = "";

    for (int i{0}; i < tokens.length(); i++)
    {

        if (tokens[i] == ' ')
        {
            if (token != "-1")
            {
                retrieve(stoi(token));
            }
            token = "";
        }
        else
        {
            token += tokens[i];
        }
    }
}

void Tokenizer::print(int index)
{
    WordTokenPair *current = hashMap[index];

    if (current == nullptr)
    {
        cout << "chain is empty";
    }
    else
    {
        while (current != nullptr)
        {
            cout << current->getKey() << " ";
            current = current->next;
        }
    }
}

int Tokenizer::hash(string word)
{
    int key{0};
    for (int i{0}; i < word.length(); i++)
    {
        char ascii = word[i];
        key += ascii;
    }
    return key;
}

int Tokenizer::dictionaryInsert(string word)
{
    if (currentDictSize == capacity)
    {
        capacity = capacity * 2;
        string *newDictionary = new string[capacity];
        for (int i = 0; i < currentDictSize; i++)
        {
            newDictionary[i] = dictionary[i];
        }
        delete[] dictionary;
        dictionary = newDictionary;
    }

    dictionary[currentDictSize] = word;
    currentDictSize++;
    return currentDictSize;
}

Tokenizer::~Tokenizer()
{
    for (int i = 0; i < size; i++)
    {
        WordTokenPair *current = hashMap[i];
        while (current != nullptr)
        {
            WordTokenPair *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] hashMap;
    delete[] dictionary;
}