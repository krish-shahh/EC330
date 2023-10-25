// Krish Shah, U75802512

#ifndef SkipList_h
#define SkipList_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
    Node<T>* tail;                                  //tail of list
    LinkedList<T> *down;                            //linked list down pointer
    LinkedList<T> *up;                              //linked list up pointer
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor: accepts -infinity, +infinity values,
                                                    //  creates skip list with top-level only
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
                                                    //  where new node should be inserted in the bottom-most list)
    Node<T>* insert(T data);                        // insert node with data, return pointer if inserted, NULL if error
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T>* addList(LinkedList<T>* current); //adds a list to the SkipList.  returns a pointer to top-most list
    LinkedList<T> *topList;                         // pointer to the top-most list
    int height = 1;                                     //height of Skip Lists
    int randSeed = 330;                             // to be used as seed for the getRand() function
};

//returns 0 or 1 with a 50% chance 
//When it returns 1, insert the node to next level of the skiplist
int getRand(){
    return rand()%2;
}

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}

/****** Implementation of linked list ******/
// Constructor
template <class T>
LinkedList<T>::LinkedList(T minVal, T maxVal)
{
    //Creating head node & assigning it minVal
    head = new Node<T>(minVal);

    //Setting tail, as head->next & assigning it maxVal
    head->next = new Node<T>(maxVal);
    this->tail = head->next;
    //Setting the tail's previous node as the head
    head->next->prev = head;

    //Setting the Linked List up and down pointer to null
    this->down = nullptr;
    this->up = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    //Need to delete all values to delete linked list
    Node<T>* current = head;
    Node<T>* temp;

    //Iterate through Linked List deleting one Node at a time
    while(current != nullptr)
    {
        temp = current->next;
        delete current;
        current = temp;
    }

}

// search for data starting at location, return node <= data
template<class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data){
    Node<T>* current = location;

    // check we are still in bounds of the LinkedList to iterate through
    while(current != nullptr)
    {
        // check if current node's is larger already
        if(current->data > data)
        {
            return current->prev; // return node where new number should be placed
        }

            // if data is contained in the list
        else if(current->data == data){
            return current;
        }

            // otherwise keep iterating
        else{
            current = current->next;
        }
    }
    // data is not in the list and is greater than all current values in linked list
    return current->prev;
}


// insert node with data at new node to be placed directly
template<class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data){
    // first, check if the given location is NULL
    if(location == nullptr){
        cout<< "This location is NULL" << endl;
        return nullptr;
    }

    if(location->data == data){
        return nullptr;
    }

    if(data <= location->data){
        cout << "Error: Inserting data in wrong order." << endl;
        return nullptr;
    }

    if(location->next != nullptr && data >= location->next->data){
        cout << "Error: Inserting data in wrong order." << endl;
        return nullptr;
    }

    Node<T> *inserted_node = new Node <T>(data);

    if (location->data > inserted_node->data)
    {
        return nullptr;
    }

    inserted_node->prev = location;
    inserted_node->next = location->next;
    location->next = inserted_node;
    inserted_node->next->prev = inserted_node;

    return inserted_node;
}

// prints linked list data
template<class T>
void LinkedList<T>::printData(){
    Node<T>* current; // allocate index node
    current = head; // initialize to beginning of the linkedlist

    // check we are still in bounds of the LinkedList
    while(current != nullptr){
        // print each node data with node printData function
        current->printData();
        current = current->next; // iterate through the list
    }
}

// prints linked list with all nodes pointers
template<class T>
void LinkedList<T>::print(){
    Node<T>* current; // allocate index node
    current = head; // initialize to beginning of the linkedlist

    // check we are still in bounds of the LinkedList
    while(current != nullptr){
        // print each node using node print function
        current->print();
        cout << endl; //next line
        current = current->next; // iterate through the list
    }
}

/****** Skip List Implementation ******/

template <class T>
SkipList<T>::SkipList(T minVal, T maxVal)
{
    srand(this->randSeed);
    this->topList = new LinkedList(minVal, maxVal);
}

// Destructs SkipList
template <class T>
SkipList<T>::~SkipList()
{
    Node<T> *current = this->topList->head;
    Node<T> *iterator = current;

    // Iterates through each level (vertically)
    while (current)
    {
        Node<T> *downFirst = current->down;

        // Iterates through each Node and deletes it for a given Level
        while (iterator)
        {
            Node<T> *nextIterator = iterator->next;
            delete iterator;
            iterator = nextIterator;
        }

        current = downFirst;
        iterator = current;
    }
}

// Return pointer to a bottom level Node
// Node must contain param data or preceed its expected location
template <class T>
Node<T> *SkipList<T>::search(T data)
{
    Node<T> *iterator = this->topList->head;

    // Start search from topList's head Node
    while (iterator->down || (iterator->next && iterator->next->data <= data))
    {
        // Go down if next Node's data is greater, else keep going to next
        if (iterator->next->data > data)
            iterator = iterator->down;
        else
            iterator = iterator->next;
    }
    return iterator;
}

// Insert new Node with data to SkipList
// return pointer of new Node at bottom level
template <class T>
Node<T> *SkipList<T>::insert(T data)
{
    // Find Node preceeding expected location using search method
    Node<T> *prevNode = search(data);

    // Return NULL if data is already in SkipList
    if (prevNode->data == data)
        return NULL;

    Node<T> *dataNode = new Node<T>(data);
    Node<T> *nextNode = prevNode->next;

    // check if another topList is needed after insertion
    if (!prevNode->prev && !nextNode->next)
    {
        // create another topList
        this->topList = new LinkedList(prevNode->data, nextNode->data);

        prevNode->up = this->topList->head;
        nextNode->up = this->topList->head->next;

        this->topList->head->down = prevNode;
        this->topList->head->next->down = nextNode;
    }

    // Insert new Node with data at bottom level
    prevNode->next = dataNode;
    nextNode->prev = dataNode;

    dataNode->next = nextNode;
    dataNode->prev = prevNode;

    Node<T> *belowDataNode = dataNode;

    // Insert new Node with data at above level if getRand() returns 1 (50% chance)
    while (getRand())
    {
        // Find new Node's expected previous/next Nodes at the above level (now current level)
        while (prevNode->prev || prevNode->up)
        {
            if (prevNode->up)
            {
                prevNode = prevNode->up;
                break;
            }
            if (prevNode->prev)
                prevNode = prevNode->prev;
        }
        nextNode = prevNode->next;

        // check if another topList is needed after insertion
        if (!prevNode->prev && !nextNode->next)
        {
            // create another topList
            this->topList = new LinkedList(prevNode->data, nextNode->data);

            prevNode->up = this->topList->head;
            nextNode->up = this->topList->head->next;

            this->topList->head->down = prevNode;
            this->topList->head->next->down = nextNode;
        }

        // insert new Node with data at current level
        Node<T> *newDataNode = new Node<T>(data);

        prevNode->next = newDataNode;
        nextNode->prev = newDataNode;

        newDataNode->prev = prevNode;
        newDataNode->next = nextNode;

        // Establish connection with new Node to the Node below it with same data
        belowDataNode->up = newDataNode;
        newDataNode->down = belowDataNode;
        belowDataNode = newDataNode;
    }

    // Return pointer to new inserted Node at bottom level (first Node of data to be inserted)
    return dataNode;
}

// Prints each node's data value in SkipList
template <class T>
void SkipList<T>::printData()
{
    Node<T> *vertIterator = this->topList->head;
    Node<T> *horizIterator = this->topList->head;

    // Iterate through each level (vertically)
    while (vertIterator)
    {
        // Iterate through each Node and print at current level
        while (horizIterator)
        {
            horizIterator->printData();
            horizIterator = horizIterator->next;
        }

        vertIterator = vertIterator->down;
        horizIterator = vertIterator;
        cout << endl;
    }
}

// Prints each node's entire content in SkipList
template <class T>
void SkipList<T>::print()
{
    Node<T> *vertIterator = this->topList->head;
    Node<T> *horizIterator = this->topList->head;

    // Iterate through each level (vertically)
    while (vertIterator)
    {
        // Iterate through each Node and print its content at current level
        while (horizIterator)
        {
            horizIterator->print();
            horizIterator = horizIterator->next;
        }

        vertIterator = vertIterator->down;
        horizIterator = vertIterator;
    }
}

#endif /* SkipList_h */