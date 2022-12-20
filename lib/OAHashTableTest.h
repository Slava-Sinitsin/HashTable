#pragma once

#include <random>
#include "OAHashTable.h"

using namespace std;

int oaRandom(int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

void oaHashTableTest(int capacity, double alpha) {
    OAHashTable<int> oaHashTable(capacity);
    int rem_capacity = (int) (capacity * alpha);
    int key;
    vector<unsigned long long> keyArr;
    double ins = 0, fin = 0, del = 0;
    for (int i = 0; i < rem_capacity; ++i) {
        key = oaRandom(0, 1000000000);
        keyArr.push_back(key);
        oaHashTable.insert(keyArr.back(), 1);
    }
    for (int i = 0; i < capacity; ++i) {
        key = oaRandom(0, 1000000000);
        keyArr.push_back(key);
        oaHashTable.insert(keyArr.back(), 1);
        ins += 1.0 / capacity;
    }
    cout << "Вставка: " << 0.1 * (-log(1 - alpha) / alpha) + 0.9 * (1 / (1 - alpha)) << endl;
    cout << "Удаление: " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Поиск: " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
}