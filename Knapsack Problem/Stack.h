#pragma once
#include "Node.h"
#include <fstream>
#include <iostream>
using namespace std;


template <typename T> 
class Stack
{

private:

    Node<T>* head;
    int total_stack_size;


public:

    Stack();
    Node<T>* pop();
    bool push(Node<T>*);
    void buildStack();
    int getStackSize();

    int inputInt(ifstream& fileobj);
    Node<T>* returnHead();
    ~Stack();
    
};

template <typename T> Stack<T>::Stack() {

    total_stack_size = 0;
    head = nullptr;


}

template <typename T> Node<T>* Stack<T>::returnHead() {

    return this->head;
}


template <typename T> int Stack<T>::inputInt(ifstream& fileObj) {
    char temp;
    int time = 0;
    ifstream &localObj = fileObj;
    int index = 1;
    int factor = 1;
    string my_string;
    

    temp = ',';

    while (temp != ' ' && temp != '\n' && !localObj.eof()) {

        temp = localObj.get();
        
        if (temp != ' ' && temp != '\n' && !localObj.eof()) {
            my_string += temp;
            index++;
        }


    }

     time = stoi(my_string);

    return time;


}


template <typename T> void Stack<T>::buildStack() {

    //ASSUMING THE FILE WILL INPUT WILL BE SORTED BASED ON POINTS.
    ifstream myFile("C:\\Users\\qasim\\Downloads\\file.txt");
    char temp;
    char arr[20];
    string my_string;
    int index = 0, points, time;
    

    temp = myFile.get();

    while (!myFile.eof()) {

        Node<T>* ptr = new Node<T>();
        
       

            arr[index] = temp;
            index++;

            if (temp == ' ' || temp == '\n') {

                arr[index] = '\0';
                ptr->setName(arr);
                ptr->setPoints(this->inputInt(myFile));  //SENDS THE FILE OBJECT TO THE INPUT INT FUNCTION WHICH TRAVERSES TO THE NEXT SPACE AND STORES.
                ptr->setTime(this->inputInt(myFile));

                total_stack_size++;

                push(ptr);
                delete ptr;
                index = 0;
                
            }

            temp = myFile.get();
            

    }



}



template <typename T> bool Stack<T>::push(Node<T>* ptr) {

    Node<T>* temp = new Node<T>();
    temp->setName(ptr->getName());
    temp->setPoints(ptr->getPoints());
    temp->setTime(ptr->getTime());

    if (head == nullptr) {


        head = temp;
        
        return true;

    }
    else {

        temp->next = head;
        head = temp;
        return true;
    }

    return false;
}

template <typename T> Node<T>* Stack<T>::pop() {

    Node<T>* temp = new Node<T>();

    if (head == nullptr) {

        return nullptr;
    }

    else {

        temp = head;

        if (head->next != nullptr) {
            
            head = head->next;
            return temp;
        }
        else {

            head = nullptr;
            return temp;

        }
    }

    return nullptr;

}

template <typename T> int Stack<T>::getStackSize() {

    return this->total_stack_size;

}

template <typename T> Stack<T>::~Stack() {

    for (head = head; head != nullptr; head = head->next) {
        head->~Node();

    }
    this->head = nullptr;
    delete head;
    this->total_stack_size = NULL;



}
