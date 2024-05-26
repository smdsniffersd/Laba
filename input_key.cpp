#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include "input_key.h"

using std::pair;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


bool isInteger(double number) {
    return number == static_cast<int>(number);
}
  
    
/// <summary>
/// Считывает точки из консоли.
/// </summary>
/// <returns>Возвращает вектор пар целых чисел, представляющих координаты точек.</returns>
vector<pair<int, int>> input_from_console() {
    double n_double;
    cout << "Введите общее количество точек:" << endl;
    cin >> n_double;
    // Проверка на выход за пределы диапазона int
    if (n_double >= static_cast<double>(INT_MAX)) {
        cout << "Ошибка: введенное число слишком велико. Пожалуйста, введите число меньше 2147483647." << endl;
        return {}; // Возвращаем пустой вектор в случае ошибки
    }
    else if (n_double <= static_cast<double>(INT_MIN)) {
        cout << "Ошибка: введенное число слишком мало. Пожалуйста, введите число больше " << INT_MIN << "." << endl;
        return {}; // Возвращаем пустой вектор в случае ошибки
    }


    if (!isInteger(n_double)) {
        cout << "Ошибка: введено нецелое число. Пожалуйста, введите целое число." << endl;
        return {}; // Возвращаем пустой вектор в случае ошибки
    }
    
    int n = static_cast<int>(n_double);
    if (n < 2) {
        cout << "Невозможно провести ни одного отрезка в таком количестве точек." << endl;
        return {};
    }

    vector<pair<int, int>> points;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cout << "Введите x-координату для точки " << i + 1 << ": ";
        cin >> x;
        cout << "Введите y-координату для точки " << i + 1 << ": ";
        cin >> y;
        /*points.emplace_back(x, y);*/ // Добавляем точку в конец вектора
        points[i] = std::make_pair(static_cast<int>(x), static_cast<int>(y));
    }
    return points;
}