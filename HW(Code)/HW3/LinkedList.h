// Krish Shah, U75802512, kshah26@bu.edu

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);
    T data;
    Node<T> *next;
    Node<T> *prev;
    Node<T> *up;
    Node<T> *down;
    void printData();
    void print();
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);
    ~LinkedList();
    Node<T>* search(Node<T>* location, T data);
    Node<T>* insert(Node<T>* location, T data);
    void printData();
    void print();
    Node<T>* head;
};

template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

template <class T>
void Node<T>::print()
{
    cout << data << ": [address: " << this << ", next node: " << this->next << ", prev node: " << this->prev << ", up: " << this->up << ", down: " << this->down << "]";
}

template <class T>
LinkedList<T>::LinkedList(T minVal, T maxVal)
{
    head = new Node<T>(minVal);
    head->next = new Node<T>(maxVal);
    head->next->prev = head;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* current = head;
    Node<T>* temp;

    while(current != nullptr)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
}

template<class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data){
    Node<T>* current = location;

    while(current != nullptr)
    {
        if(current->data > data)
        {
            return current->prev;
        }
        else if(current->data == data){
            return current;
        }
        else{
            current = current->next; 
        }
    }
    return current->prev;
}

template<class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data){
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

template<class T>
void LinkedList<T>::printData(){
    Node<T>* current;
    current = head;

    while(current != nullptr){
        current->printData();
        current = current->next;
    }
}

template<class T>
void LinkedList<T>::print(){
    Node<T>* current;
    current = head;

    while(current != nullptr){
        current->print();
        cout << endl;
        current = current->next;
    }
}

#endif 
