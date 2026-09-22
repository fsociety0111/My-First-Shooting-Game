#pragma once
#include <vector>
#include <string>

class Map {
public:
    std::vector<std::string> grid =
    {
        "11111111111111111111",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000111000111",
        "10000000000000000001",
        "10000000000000000001",
        "11111111100000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000011111111111",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "10000000000000000001",
        "11111111111111111111"
    };

    int width() const {
        return static_cast<int>(grid[0].size());
    }

    int height() const {
        return static_cast<int>(grid.size());
    }

    bool isWall(float x, float y) const {
        int mx = static_cast<int>(x);
        int my = static_cast<int>(y);

        if (my < 0 || my >= height() ||
            mx < 0 || mx >= width())
            return true;

        return grid[my][mx] == '1';
    }
};
