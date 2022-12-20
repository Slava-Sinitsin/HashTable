#pragma once

#include "OATest.h"
#include "CCTest.h"

using namespace std;

double ccTheoretical(int n, int m) {
    return 1 + ((double) n / (double) m) / 2;
}

double oaUnSucTheoretical(int n, int m) {
    double a = (double) n / (double) m;
    return (1 + 1 / pow((1 - a), 2)) / 2;
}

void PerformanceTest() {
    int n, m = 1000;
    int step = m / 20;
    vector<unsigned long long> keys;
    vector<double> alphas;
    vector<double> insert_c;
    vector<double> search_c;
    vector<double> remove_c;
    vector<double> theoretical;
    for (int i = 0; i < 1.5 * m / step; i++) {
        insert_c.push_back(0);
        search_c.push_back(0);
        remove_c.push_back(0);
    }
    cout << "step = " << step << "\n";
    for (int j = 0; j < 10; j++) {
        CCHashTable<int> ccHashTable(m);
        for (int k = 0; ccHashTable.getSize() <= 1.5 * (double) m; k++) {
            n = ccHashTable.getSize();
            if (alphas.size() <= 1.5 * m / step)
                alphas.push_back((double) n / (double) m);
            unsigned long long key = random(0, 1000000000);
            ccHashTable.insert(key, 1);
            insert_c[k] += ccHashTable.getNodeCounter();
            ccHashTable.find(key);
            search_c[k] += ccHashTable.getNodeCounter();
            ccHashTable.remove(key);
            remove_c[k] += ccHashTable.getNodeCounter();
            if (theoretical.size() <= 1.5 * m / step)
                theoretical.push_back(ccTheoretical(n, m));
            for (int i = 0; i < step; i++) {
                unsigned long long str = random(0, 1000000000);
                keys.push_back(str);
                ccHashTable.insert(str, 0);
            }
        }
    }
    cout << "ccHashTable, m = " << m << "\n";
    cout << "alpha: ";
    for (int i = 0; i < alphas.size() - 1; i++)
        cout << alphas[i] << ", ";
    cout << "\ninsert: ";
    for (double i: insert_c)
        cout << i / 10 << ", ";
    cout << "\nsearch: ";
    for (double i: search_c)
        cout << i / 10 << ", ";
    cout << "\nremove: ";
    for (double i: remove_c)
        cout << i / 10 << ", ";
    cout << "\ntheoretical: ";
    for (int i = 0; i < theoretical.size() - 1; i++)
        cout << theoretical[i] << ", ";
    alphas.clear();
    insert_c.clear();
    search_c.clear();
    remove_c.clear();
    for (int i = 0; i < m / step; i++) {
        insert_c.push_back(0);
        search_c.push_back(0);
        remove_c.push_back(0);
    }
    theoretical.clear();
    for (int j = 0; j < 10; j++) {
        OAHashTable<int> oaHashTable(m);
        for (int k = 0; oaHashTable.getBusyCount() < m; k++) {
            n = oaHashTable.getBusyCount();
            if (alphas.size() <= m / step)
                alphas.push_back((double) n / (double) m);
            unsigned long long key = random(0, 1000000000);
            oaHashTable.insert(key, 1);
            insert_c[k] += oaHashTable.getNodeCounter();
            oaHashTable.find(key);
            search_c[k] += oaHashTable.getNodeCounter();
            oaHashTable.remove(key);
            remove_c[k] += oaHashTable.getNodeCounter();
            if (theoretical.size() <= m / step)
                theoretical.push_back(oaUnSucTheoretical(n, m));
            for (int i = 0; i < step; i++) {
                unsigned long long str = random(0, 1000000000);
                keys.push_back(str);
                oaHashTable.insert(str, 0);
            }
        }
    }
    cout << "\n\noaHashTable, m = " << m << "\n";
    cout << "alpha: ";
    for (int i = 0; i < alphas.size() - 1; i++)
        cout << alphas[i] << ", ";
    cout << "\ninsert: ";
    for (double i: insert_c)
        cout << i / 10 << ", ";
    cout << "\nsearch: ";
    for (double i: search_c)
        cout << i / 10 << ", ";
    cout << "\nremove: ";
    for (double i: remove_c)
        cout << i / 10 << ", ";
    cout << "\ntheoretical: ";
    for (int i = 0; i < theoretical.size() - 1; i++)
        cout << theoretical[i] << ", ";
}