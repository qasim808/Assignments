#pragma once
#include "Node.h"
#include "List.h"
#include "Node2.h"
#include <fstream>

using namespace std;

template <class T>
class List
{

private:

    Node<T>* tail;      //the list class contains head and tail and is a DLL however with two different node types. One is Node (contains the actual word) and the second is Node2(contains the information regarding a word)
    Node <T>* head;
    int total_size;

public:



    List();
    void add_New_Node(char* word, string doc_name);
    void make_List(int size, string* docs);
    static void convert_to_lowercase(char*& word);
    void search_List(string);

};



template <class T> List<T>::List() {

    this->head = nullptr;
    this->tail = nullptr;
    this->total_size = 0;
}

template <class T> void List<T>::add_New_Node(char* word, string doc_name) {
    bool isUnique = true;
    Node<T>* temp = new Node<T>();
    Node2<T>* temp_2 = new Node2<T>();
    Node<T>* iterator = new Node<T>();
    //function adds two nodes respectively.

    if (this->total_size > 0) {
        iterator = this->head;
    }


    if (this->total_size == 0) {

        head = temp;
        tail = temp;
        temp->next = nullptr;
        tail->next = temp;
        temp->setData(string(word));
        temp_2->setData(string(doc_name));
        temp_2->increaseCount();
        temp->forward = temp_2;




    }

    for (iterator = head; iterator != this->tail && isUnique; iterator = iterator->next) {

        if (iterator->getWord() != word)
        {
            if (iterator == this->tail) {
                break;
            }
            //checks if the word coming as a parameter is already in the linked list, if not, and iterator reaches to tail, it breaks.
           //else it sets isUnique to false and breaks.
        }
        else {

            isUnique = false;
            break;
        }
    }

    if (this->total_size > 0 && isUnique) {

        //this bit deals with cases where totalsize is greater than 0 and the word is unique, thus, adds the new word at the end.

        tail->next = temp;
        this->tail = temp;
        temp->next = nullptr;
        temp->forward = temp_2;
        temp->setData(string(word));
        temp_2->setData(string(doc_name));
        temp_2->increaseCount();


    }


    else if (!isUnique)
    {

        // this deals if the word is not unique, it stores the iterator from where it broke off in the loop and stores it in temp.
        // loop point 'i' starts searching from temp->forward node type to avoid mismatch and proceeds forth from there.
        temp = iterator;

        for (Node2<T>* i = temp->forward; i != nullptr; i = i->next) {


            if (i->getDocName() == doc_name) {

                i->increaseCount();
                break;
            }

            else if (i->next == nullptr) {


                i->next = temp_2;
                i = temp_2;
                temp_2->setData(string(doc_name));
                i->increaseCount();

            }


        }






    }



    total_size++;
}

template <class T>  void List <T>::convert_to_lowercase(char*& word) {
    //function converts all words to lowercase.
    int x;
    for (int i = 0; word[i] != '\0'; i++) {

        x = tolower(int(word[i]));
        word[i] = char(x);

    }
}

template <class T> void List<T>::make_List(int size, string* docs) {

    char* word_array = new char[45];
    char* doc_name = new char[10];
    char temp;
    int index = 0;
    string local_doc_name = "Doc";
    char* temp2 = new char(1);

    //this function recieves the doc addresses array and the assumtion is that the starting will always be 'Doc and the integer that follows will be <=9
    for (int i = 0; i < size; i++) {

        ifstream file_object(docs[i]);


        while (!file_object.eof() && !file_object.fail()) {



            temp = '\0';
            while (temp != ' ' && !file_object.eof() || temp != '.' && !file_object.eof() || temp != '\n' && !file_object.eof()) {
                //checks if there's a space, or it's the end of the file, or the line to make a new node.
                file_object.get(temp);
                if (temp == ' ' || temp == '\n' || file_object.eof()) {

                    word_array[index] = '\0';
                    convert_to_lowercase(word_array);
                    temp2[0] = int(i + 49);
                    temp2[1] = '\0';
                    local_doc_name += string(temp2);
                    List<T>::add_New_Node(word_array, local_doc_name);
                    local_doc_name = "Doc";

                    index = 0;
                    if (!file_object.eof()) {
                        file_object.get(temp);
                    }
                }
                if (!file_object.eof()) {
                    word_array[index] = temp;
                    index++;
                }




            }


        }



        file_object.close();


    }
}

template <class T> void List<T>::search_List(string word) {


    Node<T>* iterator = head;
    Node2<T>* inner_iterator;
    bool isFound = false;
    int count[5] = [0, 0, 0, 0, 0];





    cout << "Result(s) for " << word << ": ";

    for (iterator = iterator; iterator != nullptr && !isFound; iterator = iterator->next) {

        if (iterator->getWord() == word) {

            for (inner_iterator = iterator->forward; inner_iterator != nullptr; inner_iterator = inner_iterator->next) {

                // inner_iterator->printInformation();
                if (inner_iterator->getDocName == "Doc1") {
                    count[0] += 1;
                }








                cout << endl;
                cout << "----SPACER----" << endl;

            }

            isFound = true;


        }

        else if (iterator->next == nullptr && !isFound) {

            cout << "Couldn't find any result(s). " << endl;
            cout << endl;
            cout << "----SPACER----" << endl;
            break;

        }



    }

}
