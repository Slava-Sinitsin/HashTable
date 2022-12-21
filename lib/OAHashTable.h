#pragma once

#include <algorithm>
#include <cmath>
#include "OANode.h"


template<typename T>
class OAHashTable {
public:

    explicit OAHashTable(int capacity);

    ~OAHashTable();

    bool insert(unsigned long long key, T data);

    bool remove(unsigned long long key);

    T find(unsigned long long key);

    [[nodiscard]] int getBusyCount() const;

    [[nodiscard]] int getCapacity() const;

    int getNodeCounter() const;

    bool isEmpty();

    bool clear();

    void print();

    class OAIterator {
    public:
        OAHashTable<T> *oaHashTable;
        int current;

        explicit OAIterator(OAHashTable<T> *oaHashTable_) {
            oaHashTable = oaHashTable_;
        }

        OANode<T> begin() {
            for (int i = 0; i < oaHashTable->capacity; ++i) {
                if (oaHashTable->isBusy(i)) {
                    current = i;
                    return *oaHashTable->nodeArr[i];
                }
            }
        }

        OANode<T> end() {
            for (int i = oaHashTable->capacity - 1; i > -1; --i) {
                if (oaHashTable->isBusy(i)) {
                    current = i;
                    return *oaHashTable->nodeArr[i];
                }
            }
        }

        OANode<T> operator*() {
            return *oaHashTable->nodeArr[current];
        }

        OANode<T> operator++(int) {
            try {
                for (int i = current + 1; i < oaHashTable->capacity; ++i) {
                    if (oaHashTable->isBusy(i)) {
                        current = i;
                        return *oaHashTable->nodeArr[current];
                    }
                    throw "\nИтератор перешёл в состояние 'не установлен'";
                }
            } catch (const char *msg) {
                std::cout << msg;
            }
        }

        OANode<T> operator--(int) {
            try {
                for (int i = current - 1; i > -1; --i) {
                    if (oaHashTable->isBusy(i)) {
                        current = i;
                        return *oaHashTable->nodeArr[current];
                    }
                }
                throw "\nИтератор перешёл в состояние 'не установлен'";
            }
            catch (const char *msg) {
                std::cout << msg;
            }
        }
    };

private:
    int capacity{};
    int busyCount{};
    int nodeCounter;
    OANode<T> **nodeArr;

    [[nodiscard]] bool isDeleted(int j) const;

    [[nodiscard]] bool isBusy(int j) const;

    [[nodiscard]] bool isFree(int j) const;

    int moduleHashing(unsigned long long key, int i);

    int hashFunction(unsigned long long key);
};

template<typename T>
int OAHashTable<T>::getNodeCounter() const {
    return nodeCounter;
}

template<typename T>
int OAHashTable<T>::getBusyCount() const {
    return busyCount;
}

template<typename T>
OAHashTable<T>::OAHashTable(int capacity) {
    this->capacity = capacity;
    busyCount = 0;
    nodeCounter = 0;
    nodeArr = new OANode<T> *[this->capacity];
    for (int i = 0; i < this->capacity; ++i) {
        nodeArr[i] = new OANode<T>();
    }
}


template<typename T>
OAHashTable<T>::~OAHashTable() {
    for (int i = 0; i < this->capacity; i++) {
        if (nodeArr[i] != nullptr) {
            delete nodeArr[i];
        }
        nodeArr[i] = nullptr;
    }

}


template<typename T>
bool OAHashTable<T>::insert(unsigned long long key, T data) {
    nodeCounter = 0;
    int i = 0;
    int pos = -1;
    int j = moduleHashing(key, i);
    while (i != this->capacity && !isFree(j)) {
        nodeCounter++;
        j = moduleHashing(key, i);
        if (pos == -1 && isDeleted(j)) {
            pos = j;
        }
        if (isBusy(j) && this->nodeArr[j]->getKey() == key) {
            return false;
        }
        i++;
    }
    if (i == this->capacity && pos == -1) {
        return false;
    }
    if (pos == -1) {
        pos = j;
    }
    nodeCounter++;
    this->nodeArr[pos]->setKey(key);
    this->nodeArr[pos]->setValue(data);
    this->nodeArr[pos]->setState(states::busy_);
    this->busyCount++;
    return true;
}

template<typename T>
T OAHashTable<T>::find(unsigned long long key) {
    nodeCounter = 0;
    int i = 0;
    int j;
    do {
        nodeCounter++;
        j = moduleHashing(key, i);
        if (isBusy(j) && this->nodeArr[j]->getKey() == key) {
            return this->nodeArr[j]->getValue();
        }
        i++;
    } while (i != this->capacity || !isFree(j));
    throw "Не найдено!";
}

template<typename T>
bool OAHashTable<T>::remove(unsigned long long key) {
    nodeCounter = 0;
    int i = 0;
    int j;
    do {
        nodeCounter++;
        j = moduleHashing(key, i);
        if (isBusy(j) && this->nodeArr[j]->getKey() == key) {
            nodeArr[j]->setState(states::deleted_);
            busyCount--;
            return true;
        }
        i++;
    } while (i != this->capacity || !isFree(j));
    return false;
}


template<typename T>
int OAHashTable<T>::moduleHashing(unsigned long long key, int i) {
    return (hashFunction(key) + i) % this->capacity;
}

template<typename T>
int OAHashTable<T>::hashFunction(unsigned long long key) {
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
    return (int) hash;
}


template<typename T>
bool OAHashTable<T>::isDeleted(int j) const {
    return this->nodeArr[j]->getState() == states::deleted_;
}

template<typename T>
bool OAHashTable<T>::isBusy(int j) const {
    return this->nodeArr[j]->getState() == states::busy_;
}

template<typename T>
bool OAHashTable<T>::isFree(int j) const {
    return this->nodeArr[j]->getState() == states::free_;
}

template<typename T>
int OAHashTable<T>::getCapacity() const {
    return capacity;
}

template<typename T>
bool OAHashTable<T>::isEmpty() {
    return busyCount == 0;
}

template<typename T>
bool OAHashTable<T>::clear() {
    for (int i = 0; i < this->capacity; ++i) {
        this->nodeArr[i]->setState(states::deleted_);
    }
    return true;
}


template<typename T>
void OAHashTable<T>::print() {
    for (int i = 0; i < this->capacity; ++i) {
        if (isBusy(i)) {
            std::cout << i << " - " << this->nodeArr[i]->getKey() << " [" << nodeArr[i]->getValue() << "] ("
                      << (char) this->nodeArr[i]->getState() << ")\n";
        } else {
            std::cout << i << " - (" << (char) this->nodeArr[i]->getState() << ")" << std::endl;
        }
    }
}