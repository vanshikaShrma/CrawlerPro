#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include "./stringHeader.h"
using namespace std;

template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node* next;

    Node(K k, V v) {
        key = k;
        value = v;
        next = NULL;
    }
};

template <typename K, typename V>
class HashTable {
private:
    Node<K, V>** table;  
    int tableSize;       
    int elementCount; 
    double loadFactorThreshold;
     int getIndex(K key); 
    void resize();       
    void rehash(); 

public:
    HashTable(int initialSize = 10, double threshold = 0.75);
    ~HashTable();

    void insert(K key, V value);
    bool search(K key, V& outVal); 
    void remove(K key);
    void display();
    void traverse();
     double getLoadFactor() const;
    int getSize() const;
    int getElementCount() const;
};

// Constructor: set all to NULL
template <typename K, typename V>
HashTable<K, V>::HashTable(int initialSize, double threshold) {
    tableSize = initialSize;
    elementCount = 0;
    loadFactorThreshold = threshold;
    
    // Allocate dynamic array
    table = new Node<K, V>*[tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = NULL;
}

// Destructor: free memory
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    for (int i = 0; i < tableSize; i++) {
        Node<K, V>* temp = table[i];
        while (temp) {
            Node<K, V>* del = temp;
            temp = temp->next;
            delete del;
        }
    }
    delete[] table;
}
template <typename K, typename V>
void HashTable<K, V>::resize() {
    cout << "Resizing hash table from " << tableSize << " to " << (tableSize * 2) << endl;
    
    // Store old table
    Node<K, V>** oldTable = table;
    int oldSize = tableSize;
    
    // Create new table with double size
    tableSize *= 2;
    table = new Node<K, V>*[tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = NULL;
    elementCount = 0;
    
    for (int i = 0; i < oldSize; i++) {
        Node<K, V>* temp = oldTable[i];
        while (temp) {
            Node<K, V>* next = temp->next;
            
            int newIndex = getIndex(temp->key);
            temp->next = table[newIndex];
            table[newIndex] = temp;
            elementCount++;
            
            temp = next;
        }
    }
    
    delete[] oldTable;
}

// General getIndex function
template <typename K, typename V>
int HashTable<K, V>::getIndex(K key) {
    return static_cast<int>(key) % 10;
}

// General insert function
template <typename K, typename V>
void HashTable<K, V>::insert(K key, V value) {
    int index = getIndex(key);
    if (getLoadFactor() >= loadFactorThreshold) {
        resize();
    }
    Node<K, V>* newNode = new Node<K, V>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
     elementCount++;
}

// General search function
template <typename K, typename V>
bool HashTable<K, V>::search(K key, V& outVal) {
    int index = getIndex(key);
    Node<K, V>* temp = table[index];
    while (temp) {
        if (temp->key == key) {
            outVal = temp->value;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// General remove function
template <typename K, typename V>
void HashTable<K, V>::remove(K key) {
    int index = getIndex(key);
    Node<K, V>* temp = table[index];
    Node<K, V>* prev = NULL;

    while (temp) {
        if (temp->key == key) {
            if (prev == NULL) {
                // deleting head
                table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            elementCount--;
            cout << "Deleted key: " << key << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Key not found: " << key << endl;
}

// Display function
template <typename K, typename V>
void HashTable<K, V>::display() {
    for (int i = 0; i < tableSize; i++) {
        cout << "Index " << i << ": ";
        Node<K, V>* temp = table[i];
        while (temp) {
            cout << "[" << temp->key << ":" << temp->value << "] -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}
template <typename K, typename V>
void HashTable<K, V>::traverse() {
    for (int i = 0; i < tableSize; i++) {
        Node<K*, V*>* temp = table[i];
        while (temp) {
            cout << "[" << temp->key << ":" << temp->value << "]"<<endl;
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

template <typename K, typename V>
double HashTable<K, V>::getLoadFactor() const {
    return static_cast<double>(elementCount) / tableSize;
}

template <typename K, typename V>
int HashTable<K, V>::getSize() const {
    return tableSize;
}

template <typename K, typename V>
int HashTable<K, V>::getElementCount() const {
    return elementCount;
}
// Forward declarations for char* specializations
template <>
int HashTable<char*, char*>::getIndex(char* key);

template <>
void HashTable<char*, char*>::insert(char* key, char* value);

template <>
bool HashTable<char*, char*>::search(char* key, char*& outVal);

template <>
void HashTable<char*, char*>::remove(char* key);

template <>
void HashTable<char*, char*>::traverse();

template <>
void HashTable<char*, int>::insert(char* key, int value);

template <>
int HashTable<char*, int>::getIndex(char* key);

template <>
bool HashTable<char*, int>::search(char* key, int& outVal);

#endif