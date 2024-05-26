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
/// ��������� ����� �� �������.
/// </summary>
/// <returns>���������� ������ ��� ����� �����, �������������� ���������� �����.</returns>
vector<pair<int, int>> input_from_console() {
    double n_double;
    cout << "������� ����� ���������� �����:" << endl;
    cin >> n_double;
    // �������� �� ����� �� ������� ��������� int
    if (n_double >= static_cast<double>(INT_MAX)) {
        cout << "������: ��������� ����� ������� ������. ����������, ������� ����� ������ 2147483647." << endl;
        return {}; // ���������� ������ ������ � ������ ������
    }
    else if (n_double <= static_cast<double>(INT_MIN)) {
        cout << "������: ��������� ����� ������� ����. ����������, ������� ����� ������ " << INT_MIN << "." << endl;
        return {}; // ���������� ������ ������ � ������ ������
    }


    if (!isInteger(n_double)) {
        cout << "������: ������� ������� �����. ����������, ������� ����� �����." << endl;
        return {}; // ���������� ������ ������ � ������ ������
    }
    
    int n = static_cast<int>(n_double);
    if (n < 2) {
        cout << "���������� �������� �� ������ ������� � ����� ���������� �����." << endl;
        return {};
    }

    vector<pair<int, int>> points;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cout << "������� x-���������� ��� ����� " << i + 1 << ": ";
        cin >> x;
        cout << "������� y-���������� ��� ����� " << i + 1 << ": ";
        cin >> y;
        /*points.emplace_back(x, y);*/ // ��������� ����� � ����� �������
        points[i] = std::make_pair(static_cast<int>(x), static_cast<int>(y));
    }
    return points;
}