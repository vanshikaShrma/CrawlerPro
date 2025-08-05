#include <iostream>
#include "./stringHeader.h"

using namespace std;
#ifndef LINKED_LIST_HEADER_H
#define LINKED_LIST_HEADER_H

template <typename T>
class Node
{
public:
    T val;
    Node *next;
    // Constructors
    Node(T val)
    {
        this->val = val;
        this->next = NULL;
    }
};

template <typename T>
class List
{
    Node<T> *head = NULL;

public:
    ~List()
    {
        Node<T> *temp;
        while (head)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    // add Node
    void addAtStart(T data);
    void addInMiddle(int index, T data);
    void addAtLast(T data);
    Node<T> *deleteHead();
    Node<T> *deleteatIndex(int index); // 0 indexed
    Node<T> *deleteFromLast();
    // bool contains(T data);
    void display();
};

template <typename T>
void List<T>::addAtStart(T data)
{
    Node<T> *newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
}

// add after the given index (0 indexed)
template <typename T>
void List<T>::addInMiddle(int index, T data) {
    if (index < 0) {
        cout << "Invalid index.\n";
        return;
    }

    Node<T>* newNode = new Node<T>(data);
    if (index == 0 || head == NULL) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node<T>* temp = head;
    int i = 0;
    while (temp != NULL && i < index - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        cout << "Index out of range.\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

template <typename T>
void List<T>::addAtLast(T data)
{
    Node<T> *newNode = new Node<T>(data);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node<T> *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    cout << "[List] Added: " << data << endl;
}

template <typename T>
void List<T>::display()
{
    Node<T> *temp = head;
    if(!temp)
    {
          std::cout << "[List] display(): List is empty!" << std::endl;
    }
    while (temp)
    {
        cout << (temp->val) << "\n";
        temp = temp->next;
    }
}
template <typename T>
Node<T> *List<T>::deleteHead()
{
    if (head == NULL)
    {
        cout << "List undeflow\n";
        return NULL;
    }
    Node<T> *temp = head;
    head = head->next;
    return temp;
}

template <typename T>
Node<T> *List<T>::deleteFromLast()
{
    if (head == NULL)
    {
        cout << "List Underflow\n";
        return NULL;
    }
    if (head->next == NULL)
    {
        Node<T> *temp = head;
        head = NULL; //use delete
        return head;
    }
    Node<T> *temp = head;
    Node<T> *tail = NULL;
    while (temp->next)
    {
        tail = temp;
        temp = temp->next;
    }
    tail->next = NULL;
    return temp;
}

template <typename T>
Node<T> *List<T>::deleteatIndex(int index)
{
    int i = 0;
    Node<T> *temp = head;
    if (head == NULL)
    {
        cout << "List Underflow";
        return NULL;
    }
    if (index == 0)
    {
        Node<T> *t = head;
        head = head->next;
        return t;
    }
    Node<T> *tail = NULL;
    while (temp && i < index)
    {
        tail = temp;
        temp = temp->next;
        i++;
    }
    if (temp == NULL)
    {
        cout << "NO node exist";
        return NULL;
    }
    Node<T> *t = temp;
    tail->next = temp->next;
    return t;
}
// template <typename T>
// bool List<T>::contains(T data) {
//     Node<T>* temp = head;
//     while (temp) {
//         if (temp->val == data)
//             return true;
//         temp = temp->next;
//     }
//     return false;
// }
// bool List<char*>::contains(char* data) {
//     Node<char*>* temp = head;
//     while (temp) {
//         if (my_strcmp(temp->val, data) == 0)
//             return true;
//         temp = temp->next;
//     }
//     return false;
// }
#endif