#pragma once
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Node2
{
private:
    //this is the class which contains the document name and the frequency count of each word in a file. 

    string document_name;
    int frequency_count;

public:
    Node2<T>* next;

    Node2();
    Node2(string doc, int freq);
    void setData(string doc);
    string getDocName();
    void increaseCount();
    void printInformation();


};

template <class T> Node2<T>::Node2(string doc, int freq) {
    this->document_name = new string(doc);
    this->frequency_count = freq;

}


template <class T> Node2<T>::Node2() {
    this->document_name = "junk";
    this->frequency_count = 0;
}


template <class T> void Node2<T>::setData(string doc) {

    this->document_name = doc;


}

template <class T> string Node2<T>::getDocName() {

    return this->document_name;
}

template <class T> void Node2<T>::increaseCount() {

    this->frequency_count += 1;

}

template <class T> void Node2<T>::printInformation() {


    cout << "Word found in document: " << this->document_name << endl;
    cout << "With term frequency: " << this->frequency_count << endl;



}
