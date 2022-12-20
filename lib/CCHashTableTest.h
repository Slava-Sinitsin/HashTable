#pragma once

#include <random>
#include "CCHashTable.h"

using namespace std;

int ccRandom(int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

void ccHashTableTest(int capacity, double alpha) {
    CCHashTable<int> ccHashTable(capacity);
    int rem_capacity = (int) (capacity * alpha);
    int key;
    vector<unsigned long long> keyArr;
    double ins = 0, fin = 0, del = 0;
    for (int i = 0; i < rem_capacity; ++i) {
        key = ccRandom(0, 1000000000);
        keyArr.push_back(key);
        ccHashTable.insert(keyArr.back(), 1);
    }
    for (int i = 0; i < capacity; ++i) {
        key = ccRandom(0, 1000000000);
        keyArr.push_back(key);
        ccHashTable.insert(keyArr.back(), 1);
        ins += 1.0 / capacity;
    }
    cout << "Вставка: " << 1 + alpha << endl;
    cout << "Удаление: " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    cout << "Поиск: " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
}