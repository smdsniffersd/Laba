#include <iostream>

#include "Menu.h"
#include "config.h"
#include "input_key.h"
#include "input_txt.h"

using namespace std;

int main(){

    setlocale(LC_ALL, "RU");
    std::vector<std::pair<int, int>> points;
    int choise = menu();

    while (choise != 0) {
        switch (choise) {
        case 1: points = input_from_txt(); break;
        case 2: points = input_from_console(); break;
        case 3:
            if (!points.empty()) {

                search_min_points(points);
            }
            break;
        }

        choise = menu(); 
    }

    cout << "Thanks for using our program!";
    return 0;
}
