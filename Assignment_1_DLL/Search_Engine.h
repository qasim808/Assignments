#pragma once
#include <string>
#include <iostream>
#include "List.h"
using namespace std;
template <class T>
class Search_Engine
{

private:
    string* docs;
    int n;
    List<string> my_List;
public:

    Search_Engine();
    Search_Engine(int);
    void add_docs();
    void search(string);
    void build_index();
    ~Search_Engine();
};

template <class T> Search_Engine<T>::Search_Engine() {

    add_docs(); //loads all the documents and checks if the addresses are fine.

}

template <class T> Search_Engine<T>::Search_Engine(int no_of_docs) {


    this->n = no_of_docs;
    add_docs(no_of_docs);

}

template <class T> void Search_Engine<T>::add_docs() {

    string initial = "C:\\Users\\qasim\\Downloads\\";
    string temp;
    bool isValid = true;

    int n;


    cout << "How many documents would you like to add: " << endl;
    cin >> n;
    this->n = n;

    docs = new string[n];

    for (int i = 0; i < n; i++) {



        cout << "Enter document name (case senstive) at slot " << i + 1 << ":";
        cin >> temp;
        temp = temp + ".txt";
        this->docs[i] = initial + temp;

        ifstream test(docs[i]);

        if (test.fail()) {
            isValid = false;
        }

        //loop checks whether the files can be opened or not and stays false till files are opened and the address becomes valid
        while (!isValid) {
            cout << "ERROR! INCORRECT DOCUMENT NAME! Enter document name (case senstive) at slot " << i + 1 << ":";
            cin >> temp;
            temp = temp + ".txt";
            this->docs[i] = initial + temp;
            ifstream test(docs[i]);
            if (!test.fail()) {
                isValid = true;
            }

        }





    }

}


template <class T> void Search_Engine<T>::build_index() {

    my_List.make_List(this->n, this->docs);

}


template <class T> void Search_Engine<T>::search(string word) {
    my_List.search_List(word);

}

template <class T> Search_Engine<T>::~Search_Engine() {

    delete[]docs;

}
