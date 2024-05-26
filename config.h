#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <utility> 
#include <algorithm> 
#include <limits> 

int search_points(std::pair<int, int> point1, std::pair<int, int> point2, const std::vector<std::pair<int, int>>& points);

std::pair<std::pair<int, int>, std::pair<int, int>> search_min_points(const std::vector<std::pair<int, int>>& points);



#endif 
