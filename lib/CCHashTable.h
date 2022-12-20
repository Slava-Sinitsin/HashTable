#pragma once

#include "CCnode.h"
#include <iostream>
#include "cmath"
#include <vector>

template<typename T>
class CCHashTable {
public:
    explicit CCHashTable(int capacity);

    ~CCHashTable();

    bool insert(unsigned long long k, T data);

    bool remove(unsigned long long k);

    T find(unsigned long long k);

    bool isEmpty();

    [[nodiscard]] int getSize() const;

    [[nodiscard]] int getCapacity() const;

    int getNodeCounter() const;

    void print();

public:
    class CCIterator {
    public:
        CCHashTable<T> *ccHashTable;
        int current;
        std::vector<CCNode<T> *> vector;

        explicit CCIterator(CCHashTable<T> *ccHashTable_) {
            ccHashTable = ccHashTable_;
            for (int i = 0; i < ccHashTable->capacity; i++) {
                if (ccHashTable->nodeArr[i] != nullptr) {
                    vector.push_back(ccHashTable->nodeArr[i]);
                    CCNode<T> *t = ccHashTable->nodeArr[i]->getNext();
                    while (t != nullptr) {
                        vector.push_back(t);
                        t = t->getNext();
                    }
                }
            }
        }

        CCNode<T> begin() {
            current = 0;
            return *vector[0];
        }

        CCNode<T> end() {
            current = vector.size() - 1;
            return *vector[vector.size() - 1];
        }

        CCNode<T> operator*() {
            return *vector[current];
        }

        CCNode<T> operator++(int) {
            CCNode<T> ccNode;
            try {
                if (current > -1 && current < vector.size() - 1) {
                    current++;
                    ccNode = *vector[current];
                    return ccNode;
                }
                throw "\nИтератор перешёл в состояние 'не установлен'";
            } catch (const char *msg) {
                std::cout << msg;
            }
        }

        CCNode<T> operator--(int) {
            CCNode<T> ccNode;
            try {
                if (current > 0 && current < vector.size()) {
                    current--;
                    ccNode = *vector[current];
                    return ccNode;
                }
                throw "\nИтератор перешёл в состояние 'не установлен'";
            } catch (const char *msg) {
                std::cout << msg;
            }
        }
    };

private:
    CCNode<T> **nodeArr;
    int size{};
    int capacity{};
    int nodeCounter;

    int hashFunction(unsigned long long key);
};

template<typename T>
int CCHashTable<T>::getNodeCounter() const {
    return nodeCounter;
}

template<typename T>
CCHashTable<T>::CCHashTable(int capacity) {
    this->capacity = capacity;
    size = 0;
    nodeCounter = 0;
    nodeArr = new CCNode<T> *[this->capacity];
    for (int i = 0; i < this->capacity; ++i) {
        nodeArr[i] = nullptr;
    }
}

template<typename T>
CCHashTable<T>::~CCHashTable() {
    for (int i = 0; i < this->capacity; i++) {
        if (nodeArr[i] != nullptr) {
            delete nodeArr[i];
        }
        nodeArr[i] = nullptr;
    }
}


template<typename T>
bool CCHashTable<T>::insert(unsigned long long k, T data) {
    nodeCounter = 0;
    int j = hashFunction(k);
    if (nodeArr[j] == nullptr) {
        nodeCounter++;
        nodeArr[j] = new CCNode<T>();
        nodeArr[j]->setValue(data);
        nodeArr[j]->setKey(k);
    } else {
        nodeCounter++;
        CCNode<T> *p = this->nodeArr[j];
        if (p->getKey() == k) {
            return false;
        }
        while (p->getNext() != nullptr) {
            nodeCounter++;
            p = p->getNext();
            if (p->getKey() == k) {
                return false;
            }
        }
        p->setNext(new CCNode<T>());
        p->getNext()->setNext(nullptr);
        p->getNext()->setKey(k);
        p->getNext()->setValue(data);
    }
    this->size++;
    return true;
}

template<typename T>
bool CCHashTable<T>::remove(unsigned long long k) {
    nodeCounter = 0;
    int j = hashFunction(k);
    CCNode<T> *p = this->nodeArr[j];
    nodeCounter++;
    if (p == nullptr) {
        return false;
    }
    if (p->getKey() == k) {
        this->nodeArr[j] = this->nodeArr[j]->getNext();
        delete p;
        this->size--;
        return true;
    }
    while (p->getNext() != nullptr) {
        nodeCounter++;
        if (p->getNext()->getKey() == k)
            break;
        p = p->getNext();
    }
    if (p->getNext() == nullptr) {
        return false;
    }
    CCNode<T> *t = p->getNext();
    p->setNext(p->getNext()->getNext());
    delete t;
    this->size--;
    return true;
}

template<typename T>
T CCHashTable<T>::find(unsigned long long k) {
    nodeCounter = 0;
    int j = hashFunction(k);
    CCNode<T> *t = this->nodeArr[j];
    while (t != nullptr) {
        nodeCounter++;
        if (t->getKey() == k) {
            break;
        }
        t = t->getNext();
    }
    if (t == nullptr)
        throw "Не найдено!";
    return t->getValue();
}


template<typename T>
int CCHashTable<T>::hashFunction(unsigned long long key) {
    unsigned long long hash = key * key;
    unsigned long long tmpHash = hash;
    int count = 1;
    while (tmpHash > 0) {
        tmpHash /= 10;
        count++;
    }
    unsigned long long hashArr[count];
    for (int i = count - 1; i > -1; --i) {
        hashArr[i] = hash % 10;
        hash /= 10;
    }
    int middle = count / 2;
    if (count == 1) {
        hash = hashArr[0];
    } else if (count == 2) {
        for (int i = 0; i < count; ++i) {
            hash = hash * 10 + hashArr[i];
        }
    } else if (count > 2) {
        hash = ((hashArr[middle - 1] * 10 + hashArr[middle]) * 10 + hashArr[middle + 1]);
    }
    return (int) hash % capacity;
}

template<typename T>
bool CCHashTable<T>::isEmpty() {
    for (int i = 0; i < this->capacity; i++)
        if (nodeArr[i]) return false;
    return true;
}

template<typename T>
int CCHashTable<T>::getCapacity() const {
    return capacity;
}

template<typename T>
int CCHashTable<T>::getSize() const {
    return size;
}

template<typename T>
void CCHashTable<T>::print() {
    for (int i = 0; i < this->capacity; i++) {
        if (this->nodeArr[i] != nullptr) {
            std::cout << i << " - " << this->nodeArr[i]->getKey() << " " << "[" << nodeArr[i]->getValue() << "]";
            CCNode<T> *t = this->nodeArr[i]->getNext();
            while (t != nullptr) {
                std::cout << ", " << t->getKey() << " " << "[" << t->getValue() << "]";
                t = t->getNext();
            }
            std::cout << std::endl;
        } else
            std::cout << i << " - Empty" << std::endl;
    }
}