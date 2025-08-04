#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
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
    Node<K, V>* table[10];

    int getIndex(K key); 

public:
    HashTable();
    ~HashTable();

    void insert(K key, V value);
    bool search(K key, V& outVal); 
    void remove(K key);
    void display();
};
// Constructor: set all to NULL
template <typename K, typename V>
HashTable<K, V>::HashTable() {
    for (int i = 0; i < 10; i++)
        table[i] = NULL;
}
// Destructor: free memory
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    for (int i = 0; i < 10; i++) {
        Node<K, V>* temp = table[i];
        while (temp) {
            Node<K, V>* del = temp;
            temp = temp->next;
            delete del;
        }
    }
}
template <typename K, typename V>
int HashTable<K, V>::getIndex(K key) {
    return static_cast<int>(key) % 10;
}
template <>
int HashTable<string, string>::getIndex(string key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % 10;
}
template <>
int HashTable<string, int>::getIndex(string key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % 10;
}
template <>
int HashTable<string, float>::getIndex(string key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % 10;
}
// Insert function
template <typename K, typename V>
void HashTable<K, V>::insert(K key, V value) {
    int index = getIndex(key);
    Node<K, V>* newNode = new Node<K, V>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}
//search
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
    for (int i = 0; i < 10; i++) {
        cout << "Index " << i << ": ";
        Node<K, V>* temp = table[i];
        while (temp) {
            cout << "[" << temp->key << ":" << temp->value << "] -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}
#endif