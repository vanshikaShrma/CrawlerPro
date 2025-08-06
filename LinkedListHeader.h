#include <iostream>
#include "./stringHeader.h"

using namespace std;
#ifndef LINKED_LIST_HEADER_H
#define LINKED_LIST_HEADER_H

template <typename T>
class NodeL
{
public:
    T val;
    NodeL *next;
    // Constructors
    NodeL(T val)
    {
        this->val = val;
        this->next = NULL;
    }
};

template <typename T>
class List
{
    NodeL<T> *head = NULL;

public:
    ~List()
    {
        NodeL<T> *temp;
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
    NodeL<T> *deleteHead();
    NodeL<T> *deleteatIndex(int index); // 0 indexed
    NodeL<T> *deleteFromLast();
    void display();
};

template <typename T>
void List<T>::addAtStart(T data)
{
    NodeL<T> *newNode = new NodeL<T>(data);
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

    NodeL<T>* newNode = new NodeL<T>(data);
    if (index == 0 || head == NULL) {
        newNode->next = head;
        head = newNode;
        return;
    }

    NodeL<T>* temp = head;
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
    NodeL<T> *newNode = new NodeL<T>(data);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    NodeL<T> *temp = head;
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
    NodeL<T> *temp = head;
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
NodeL<T> *List<T>::deleteHead()
{
    if (head == NULL)
    {
        cout << "List undeflow\n";
        return NULL;
    }
    NodeL<T> *temp = head;
    head = head->next;
    return temp;
}

template <typename T>
NodeL<T> *List<T>::deleteFromLast()
{
    if (head == NULL)
    {
        cout << "List Underflow\n";
        return NULL;
    }
    if (head->next == NULL)
    {
        NodeL<T> *temp = head;
        head = NULL; //use delete
        return head;
    }
    NodeL<T> *temp = head;
    NodeL<T> *tail = NULL;
    while (temp->next)
    {
        tail = temp;
        temp = temp->next;
    }
    tail->next = NULL;
    return temp;
}

template <typename T>
NodeL<T> *List<T>::deleteatIndex(int index)
{
    int i = 0;
    NodeL<T> *temp = head;
    if (head == NULL)
    {
        cout << "List Underflow";
        return NULL;
    }
    if (index == 0)
    {
        NodeL<T> *t = head;
        head = head->next;
        return t;
    }
    NodeL<T> *tail = NULL;
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
    NodeL<T> *t = temp;
    tail->next = temp->next;
    return t;
}
#endif