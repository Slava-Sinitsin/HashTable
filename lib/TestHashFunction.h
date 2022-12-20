#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include "OAHashTable.h"
#include "CCHashTable.h"
#include <random>

using namespace std;

static int random(int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int hashFunction(unsigned long long key, int size) {
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
    return (int) hash % size;
}

void testHashFunction(int size) {
    double allSum = 0;
    int testCount = 100;
    for (int j = 0; j < testCount; ++j) {
        int *arr = new int[size];
        for (int i = 0; i < size; i++)
            arr[i] = 0;
        unsigned long long key;
        for (int i = 0; i < 20 * size; i++) {
            key = random(0, 1000000000);
            unsigned k = hashFunction(key, size);
            arr[k]++;
        }
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += (arr[i] - 20) * (arr[i] - 20);
        }
        delete[] arr;
        sum /= 20.0;
        allSum += sum;
    }
    allSum /= testCount;
    auto a = (double) (size - sqrt((double) size));
    auto b = (double) (size + sqrt((double) size));
    cout << a << " < " << allSum << " < " << b << endl;
}