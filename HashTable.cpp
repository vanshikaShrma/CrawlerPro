#include <iostream>
#include "./HashTable.h"
#include "./stringHeader.h"

using namespace std;

template <>
int HashTable<char*, char*>::getIndex(char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % 10;
}

template <>
void HashTable<char*, char*>::insert(char* key, char* value) {
    int index = getIndex(key);
     if (getLoadFactor() >= loadFactorThreshold) {
        resize();
    }
    int keyLen = my_strlen(key);
    int valueLen = my_strlen(value);
    
    char* keyCopy = new char[keyLen + 1];
    char* valueCopy = new char[valueLen + 1];
    
    my_strcpy(keyCopy, key);
    my_strcpy(valueCopy, value);
    
    Node<char*, char*>* newNode = new Node<char*, char*>(keyCopy, valueCopy);
    newNode->next = table[index];
    table[index] = newNode;
    elementCount++;
}


template <>
bool HashTable<char*, char*>::search(char* key, char*& outVal) {
    int index = getIndex(key);
    Node<char*, char*>* temp = table[index];
    while (temp) {
        if (my_strcmp(temp->key, key) == 0) {
            outVal = temp->value;
            return true;
        }
        temp = temp->next;
    }
    return false;
}


template <>
void HashTable<char*, char*>::remove(char* key) {
    int index = getIndex(key);
    Node<char*, char*>* temp = table[index];
    Node<char*, char*>* prev = NULL;

    while (temp) {
        if (my_strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
                table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            
            delete[] temp->key;
            delete[] temp->value;
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