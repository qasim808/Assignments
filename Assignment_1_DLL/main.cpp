#include <iostream>
#include <fstream>
#include <string>
#include "Search_Engine.h"
#include "List.h"
#include "Node.h"
#include "Node2.h"

using namespace std;


int search_engine_run() {

    bool END_PROGRAM = false;
    char* input = new char[100]; //maximum 25 letter input.
    int choice;
    char* temp = new char[25];
    int index = 0;

    string word;
    string* words = new string[10];
    Search_Engine<string> my_search_engine;
    my_search_engine.build_index();


    while (!END_PROGRAM) {


        cout << "Enter -1 to terminate the program, and any NUMBER to continue" << endl;
        cin >> choice;

        if (choice != -1) {

            cout << "Enter query:  " << endl;
            cin.ignore();
            cin.getline(input, 100);


            for (int z = 0; input[z] != '\0'; z++) {

                if (input[z] != ' ') {
                    temp[index] = input[z]; //tokenizes the words one by one based on spaces and \0.
                    index++;
                }

                if (input[z + 1] == ' ' || input[z + 1] == '\0') {

                    temp[index] = '\0';
                    List<string>::convert_to_lowercase(temp); //all words are searched as case-insensitive and converted to lowercased strings before being searched.
                    index = 0;
                    word = string(temp);
                    my_search_engine.search(word); //searches the list.

                }


            }




        }

        if (choice == -1) {

            return 0;
        }
















    }





}

int main() {




    search_engine_run();








    system("pause");
    return 0;
}
