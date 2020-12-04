#pragma once
#include <string>
using namespace std;
template <typename T>

class Node {

private:
    string name;
    int time;
    int points;

public:
    Node<T>* next;
    Node();
    Node(string, int, int);
    void setName(string);
    string getName();
    void setTime(int);
    int getTime();
    void setPoints(int);
    int getPoints();
    void initializeNode();
    void operator = (const Node<T>*& D);
    ~Node();
};

template <typename T> Node<T>::Node() {

    this->name = "";
    this->next = nullptr;
    this->time = 0;
    this->points = 0;
}

template <typename T> void Node<T>::initializeNode() {

    this->name = "";
    this->next = nullptr;
    this->time = 0;
    this->points = 0;
}

template <typename T> Node<T>::Node(string name, int time, int points) {

    this->name = name;
    this->time = time;
    this->points = points;
    this->next = nullptr;
}

template <typename T> void Node<T>::setName(string input) {

    this->name = input;

}
template <typename T> void Node<T>::setPoints(int input) {

    this->points = input;
}

template <typename T> void Node<T>::setTime(int input) {

    this->time = input;
}

template <typename T> int Node<T>::getTime() {

    return this->time;
}

template <typename T> int Node<T>::getPoints() {

    return this->points;
}

template <typename T> string Node<T>::getName() {

    return this->name;
}

//COPY OPERATOR

template <typename T> void Node<T>::operator = (const Node<T>*& D) {

    time = D->getTime();
    points = D->points();
    name = D->getName();
}
template <typename T> Node<T>::~Node() {

    next = nullptr;
    delete next;
    name = "";
    points = NULL;
    time = NULL;
}
