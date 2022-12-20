#pragma once

#include "CCHashTableTest.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

class CCTest {
public:
    static void menuText();

    static void menu();

    static void iteratorMenuText();

    static bool isNumber(const string &str) {
        return all_of(str.begin(), str.end(), [](const char &ch) { return isdigit(ch); });
    }

    static int random(int low, int high) {
        random_device rd;
        mt19937 gen(rd());
        std::uniform_int_distribution<> dist(low, high);
        return dist(gen);
    }
};

void CCTest::menuText() {
    cout << "Меню хеш-таблицы с цепочками коллизий" << endl;
    cout << "1. Вставить 10 случайных значений" << endl;
    cout << "2. Вывести таблицу" << endl;
    cout << "3. Вставить по ключу" << endl;
    cout << "4. Найти по ключу" << endl;
    cout << "5. Удалить по ключу" << endl;
    cout << "6. Меню итератора" << endl;
    cout << "7. Трудоёмкость" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию:" << endl;
}

void CCTest::iteratorMenuText() {
    cout << "Меню итератора хеш-таблицы с цепочками коллизий" << endl;
    cout << "1. Вывести таблицу" << endl;
    cout << "2. Запрос прямого итератора begin()" << endl;
    cout << "3. Запрос «неустановленного» прямого итератора end()" << endl;
    cout << "4. Получить значение итератора" << endl;
    cout << "5. Операция инкремента" << endl;
    cout << "6. Операция декремента" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию:" << endl;
}

void CCTest::menu() {
    CCHashTable<int> ccHashTable(50);
    while (true) {
        menuText();
        string option;
        cin >> option;
        if (!isNumber(option) || stoi(option) > 7 || stoi(option) < 0) {
            cout << "Введите коректное значение!" << endl << endl;
            continue;
        } else {
            switch (stoi(option)) {
                case 1: {
                    for (int i = 0; i < 10; ++i) {
                        ccHashTable.insert(random(0, 1000000000), random(0, 1000));
                    }
                    cout << endl;
                    break;
                }
                case 2: {
                    ccHashTable.print();
                    cout << endl;
                    break;
                }
                case 3: {
                    while (true) {
                        string key;
                        int value;
                        cout << "Введите ключ:" << endl;
                        cin >> key;
                        if (!isNumber(key) || stoi(key) > 1000000000) {
                            cout << "Введите коректное значение ключа" << endl;
                            continue;
                        } else {
                            cout << "Введите значение:" << endl;
                            cin >> value;
                            ccHashTable.insert(stoi(key), value);
                            cout << endl;
                            break;
                        }
                    }
                    break;
                }
                case 4: {
                    while (true) {
                        string key;
                        cout << "Введите ключ:" << endl;
                        cin >> key;
                        if (!isNumber(key) || stoi(key) > 1000000000) {
                            cout << "Введите коректное значение ключа" << endl;
                            continue;
                        } else {
                            try {
                                cout << "Value: " << ccHashTable.find(stoi(key)) << endl << endl;
                            } catch (const char *msg) {
                                cout << msg << endl << endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 5: {
                    while (true) {
                        string key;
                        cout << "Введите ключ:" << endl;
                        cin >> key;
                        if (!isNumber(key) || stoi(key) > 1000000000) {
                            cout << "Введите коректное значение ключа" << endl;
                            continue;
                        } else {
                            cout << ccHashTable.remove(stoi(key)) << endl;
                            break;
                        }
                    }
                    break;
                }
                case 6: {
                    cout << endl;
                    bool running = true;
                    while (running) {
                        iteratorMenuText();
                        string iteratorOption;
                        cin >> iteratorOption;
                        if (!isNumber(iteratorOption) || stoi(iteratorOption) > 6 || stoi(iteratorOption) < 0) {
                            cout << "Введите коректное значение!" << endl << endl;
                            continue;
                        } else {
                            CCHashTable<int>::CCIterator ccIterator(&ccHashTable);
                            ccIterator.begin();
                            switch (stoi(iteratorOption)) {
                                case 1: {
                                    ccHashTable.print();
                                    cout << endl;
                                    break;
                                }
                                case 2: {
                                    ccIterator.begin();
                                    cout << endl;
                                    break;
                                }
                                case 3: {
                                    ccIterator.end();
                                    cout << endl;
                                    break;
                                }
                                case 4: {
                                    cout << (*ccIterator).getKey() << endl << endl;
                                    break;
                                }
                                case 5: {
                                    ccIterator++;
                                    break;
                                }
                                case 6: {
                                    ccIterator--;
                                    break;
                                }
                                case 0: {
                                    running = false;
                                    cout << endl;
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                    }
                    break;
                }
                case 7: {
                    cout << "Capacity = 100, alpha = 0.5" << endl;
                    ccHashTableTest(100, 0.5);
                    cout << endl;
                    break;
                }
                case 0: {
                    return;
                }
                default:
                    return;
            }
        }
    }
}