#include "pch.h"
#include "input_txt.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <limits>


using std::vector;
using std::pair;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;


vector<pair<int, int>> input_from_txt() {
    vector<pair<int, int>> points;
    ifstream file("numbers.txt");
    if (!file) {
        cout << "Не удалось открыть текстовый файл" << endl;
        return points;
    }

    string line;
    int line_number = 1;
    bool invalid_coordinates = false; // Флаг для отслеживания некорректных координат
    while (getline(file, line)) {
        std::istringstream iss(line);
        int x, y;

        if (!(iss >> x >> y)) {
            cout << "Ошибка при считывании строки " << line_number << endl;
        }
        else {
            // Проверяем, не превышают ли координаты максимально допустимые значения
            if (x > std::numeric_limits<int>::max() || y > std::numeric_limits<int>::max()) {
                cout << "Слишком большие числа на строке " << line_number << endl;
                invalid_coordinates = true;
            }
            else {
                points.push_back({ x, y });
            }
        }
        line_number++;
    }

    file.close();

    if (invalid_coordinates) {
        points.clear();
    }

    return points;
}

