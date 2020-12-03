#pragma once
#include "Stack.h"
#include "Node.h"
template <typename T>
class EngineRef
{

private:
    Stack<T> my_Stack;
    Stack<T> local_stack;
    Node<T>* recursiveSearch(Node<T>* temp, Node<T>* highest, int input_time); //ACTUAL RECURSIVE FUNCTION WHICH WILL BE WRAPPED AROUND, AND SEARCHES FOR THE HIGHEST STAGES.


public:

    EngineRef();
    void buildLocalStack(int input_time); //BUILDS A LOCAL STACK FROM MY_STACK BASED UPON TIME INPUT. 
    void iterativeSearch(int);
    void recursiveSearch(int); //WRAPPER FUNCTION
    ~EngineRef();




};

template <typename T> EngineRef<T>::EngineRef() {

    my_Stack.buildStack(); //CALLS BUILD STACK AND BUILDS THE STACK BASED UPON THE FILE AND ASSUMES THAT THE FILE INPUT WILL BE SORTED BY POINTS
    
}

template <typename T> Node<T>* EngineRef<T>::recursiveSearch(Node<T>* temp, Node<T>* highest, int input_time) {

    
    if (temp==nullptr) {
        return highest; //RETURNS HIGHEST ONCE TEMP IS NULL.
   }

    else {

        temp = local_stack.pop();
        if (temp != nullptr) {
            if (temp->getPoints() > highest->getPoints()) {

                highest = temp;

            }
        }
        return recursiveSearch(temp, highest, input_time);

    }

    


}

template <typename T> void EngineRef<T>::recursiveSearch(int input_time) {
    Node<T>* temp = new Node<T>(), * HighTemp = new Node<T>();
    temp = local_stack.pop();
    HighTemp = temp;
   HighTemp =  recursiveSearch(temp, HighTemp, input_time);
    
    cout << "Favoured Stages are: " << endl;
    cout << HighTemp->getName() << endl;
    cout << "Total score: " << endl;
    cout << HighTemp->getPoints() << endl;
    cout << "Total time taken (for stages): " << endl;
    cout << HighTemp->getTime() << endl;


}



template <typename T> void EngineRef<T>::buildLocalStack(int input_time) {

    Node<T> * ptr = new Node<T>();
    Node<T>* temp = new Node<T>();
    Node<string>** temp_Arr = new Node<T> * [my_Stack.getStackSize()]; //ALLOCATED AN 2-D ARRAY OF NODES BASED UPON THE ACTUAL STACK SIZE/NUMBER OF STAGES
    int index = 0;
    int AccTime = 0;
    int indexHis = 0; //INDEX HISTORY USED IN THE LOOP LOGIC

    int currentTime;

    ptr = my_Stack.pop(); //POPS FROM THE MAIN STACK (my_Stack) AND STORES IT THE TEMP_ARR.
    temp_Arr[index] = ptr;
    index++;


    while (ptr != nullptr) {
        local_stack.push(ptr);
        ptr = my_Stack.pop();

        if (ptr != nullptr) {
            temp_Arr[index] = ptr;
            index++;
        }

    }

    index = 0; 
    
    while ( index < my_Stack.getStackSize()) {
        
        //REMEMBERS THE PREVIOUS INDEX COUNT, AND RESETS INDEX BACK TO THE PREV STORED ONE.
        indexHis = index;

        if (temp_Arr[index]->getTime() < input_time && index!=my_Stack.getStackSize()) {
            //GETS THE TIME AND EVALUATES IF IT'S LESS THAN THE INPUT TIME.
            while (AccTime <= input_time && index != my_Stack.getStackSize()) {
                //ENTERS THIS LOOP WHICH TRAVERSES THROUGH THE REST OF THE ARRAY, ADDING ONLY IF THE TIME OF THE STAGE AND ALREADY EXISTING COUNT IS LESS OR EQUAL TO INPUT TIME.
                if (AccTime + temp_Arr[index]->getTime() <= input_time) {
                    AccTime = temp_Arr[index]->getTime() + AccTime;
                    temp->setName(temp_Arr[index]->getName() + temp->getName());
                    temp->setPoints(temp_Arr[index]->getPoints() + temp->getPoints());
                    temp->setTime(temp_Arr[index]->getTime() + temp->getTime());
                    //SETS THE NODE.
                }
                index++;

                if (index == my_Stack.getStackSize() &&  AccTime <= input_time) {
                    //PUSHES THE NODE IN THE STACK AND THEN INITLIAZES IT BACK TO 0.
                    local_stack.push(temp);
                    temp->initializeNode();
                    AccTime = 0; //COUNT IS ALSO RESET TO 0

                }
            }


            


        }
        //THIS WORKS FOR CERTAIN NODES/STAGES WHICH ARE EQUAL TO THE INPUT TIME.
        else if (temp_Arr[index]->getTime() == input_time) {

            temp->setName(temp_Arr[index]->getName());
            temp->setPoints(temp_Arr[index]->getPoints());
            temp->setTime(temp_Arr[index]->getTime());
            local_stack.push(temp);
            temp->initializeNode();
            index++;
            AccTime = 0;
        }






        //INDEX (MAIN LOOP VARIABLE) IS SET BACK TO THE HISTORY.
        
        index = indexHis;
        index++;


    }

   



   






}


template <typename T> void EngineRef<T>::iterativeSearch(int input_time) {

    //POPS THE STACK AND COMPARES IT AS IT GOES TO FIND THE NODE (WHICH IS NOW A COMBINATION OF DIFFERENT STAGES AND SUM OF THEIR TIME AND POINTS
    Node<T>* temp = new Node<T>();
    Node<T>* HighTemp = new Node<T>();
    //INITILIAZES IT TO 0 BY DEFAULT
    HighTemp->initializeNode();

    temp = local_stack.pop();
    HighTemp = temp;
    

    for (temp = local_stack.pop(); temp != nullptr; temp = local_stack.pop()) {

        if (temp->getPoints() > HighTemp->getPoints()) {

            HighTemp = temp;

        }
    }



    cout << "Favoured Stages are: " << endl;
    cout << HighTemp->getName() << endl;
    cout << "Total score: " << endl;
    cout << HighTemp->getPoints() << endl;
    cout << "Total time taken (for stages): " << endl;
    cout << HighTemp->getTime() << endl;










}

template <typename T> EngineRef<T>::~EngineRef() {

    my_Stack.~Stack();
    local_stack.~Stack();
   

}
