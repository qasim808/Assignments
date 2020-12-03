#pragma once
#include "Node2.h"
using namespace std;


template <class T>
class Node
{

private:

    string maindata;


public:
    Node2<T>* forward;
    Node<T>* next;
    Node();
    Node(string word);
    void setData(string word);
    string getWord();

};

template <class T> Node<T>::Node() {

    this->forward = nullptr;
    this->next = nullptr;

}

template <class T> Node<T>::Node(string word) {
    this->forward = nullptr;
    this->next = nullptr;
    this->maindata = word;
}

template <class T> void Node<T>::setData(string word) {

    this->maindata = word;

}

template <class T> string Node<T>::getWord() {

    return this->maindata;
}
