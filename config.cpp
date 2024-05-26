#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "config.h"
#include <climits>

using std::cout;
using std::pair;
using std::vector;
using std::min;

/// <summary>
/// Эта функция подсчитывает точки по обе стороны от линии, определенной точками 1 и 2.
/// </summary>
/// <param name="point1">Первая точка, определяющая линию.</param>
/// <param name="point2">Вторая точка, определяющая линию.</param>
/// <param name="points">Вектор точек, подлежащих проверке.</param>
/// <returns>Минимальное количество точек по обе стороны от линии.</returns>
int search_points(pair<int, int> point1, pair<int, int> point2, const vector<pair<int, int>>& points) {

	int counter1 = 0, counter2 = 0;

	for (const auto& point : points) {
		int vector_multi = (point.second - point1.second) * (point2.first - point1.first) -
			(point.first - point1.first) * (point2.second - point1.second);

		if (vector_multi > 0) {
			counter1++;
		}
		else if (vector_multi < 0) {
			counter2++;
		}
	}
	return min(counter1, counter2);
}
	
	/// <summary>
	/// Эта функция находит пару точек, которые удовлетвояют условию.
	/// </summary>
	/// <param name="points">Вектор точек, подлежащих проверке.</param>
	/// <returns>Пара точек, которые сводят дисбаланс к минимуму.</returns>
	pair<pair<int, int>, pair<int, int>> search_min_points(const vector<pair<int, int>>&points) {

		int min_meaning = INT_MAX;
		pair<pair<int, int>, pair<int, int>> optimal_points;
		for (size_t i = 0; i < points.size(); ++i) {
			for (size_t j = i + 1; j < points.size(); ++j) {
				int difference = abs(search_points(points[i], points[j], points));
				if (difference < min_meaning) {
					min_meaning = difference;
					optimal_points = { points[i], points[j] };
					cout << "Optimal points: (" << optimal_points.first.first << ", " << optimal_points.first.second << ") and ("
						<< optimal_points.second.first << ", " << optimal_points.second.second << ")" << std::endl;
					
				}
			}
		}
		return optimal_points;
	}