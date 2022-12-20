#include <iostream>
#include "OATest.h"
#include "CCTest.h"
#include "TestHashFunction.h"
#include "PerformanceTest.h"

using namespace std;

static bool isNumber(const string &str) {
    return all_of(str.begin(), str.end(), [](const char &ch) { return isdigit(ch); });
}

class MainMenu {
public:
    static void mainMenu();
};

void MainMenu::mainMenu() {
    system("chcp 65001");
    cout << endl;
    while (true) {
        cout << "MAIN MENU" << endl;
        cout << "Выберите форму представления хеш таблицы:" << endl;
        cout << "1. Хеш-таблица с открытой адресацией" << endl;
        cout << "2. Хеш-таблица с цепочками коллизий" << endl;
        cout << "3. Тестирование хеш-функции" << endl;
        cout << "4. Тестирование трудоёмкости операций" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите опцию:" << endl;
        string option;
        cin >> option;
        if (isNumber(option) && stoi(option) > -1 && stoi(option) < 5) {
            switch (stoi(option)) {
                case 1: {
                    cout << endl;
                    OATest oaTest;
                    oaTest.menu();
                    cout << endl;
                    break;
                }
                case 2: {
                    cout << endl;
                    CCTest ccTest;
                    ccTest.menu();
                    cout << endl;
                    break;
                }
                case 3: {
                    cout << "Введите желаемый размер хеш-таблицы:" << endl;
                    string size;
                    cin >> size;
                    if (isNumber(size) && stoi(size) > 0) {
                        testHashFunction(stoi(size));
                        cout << endl;
                    } else {
                        cout << "Введите коректное значение!" << endl << endl;
                    }
                    break;
                }
                case 4: {
                    PerformanceTest();
                    cout << endl << endl;
                    break;
                }
                case 0: {
                    return;
                }
                default:
                    return;
            }
        } else {
            cout << "Введите коректное значение!" << endl << endl;
        }
    }
}