#include "Map.h"

Map::Map(int width, int height) : grid(width, std::vector<int>(height, 0))
{
}

void Map::updateMap(Position pos, int status)
{
    grid[pos.x][pos.y] = status;
}

bool Map::isObstacle(Position pos)
{
    return grid[pos.x][pos.y] == 1;
}

void Map::displayMap()
{
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell == 1 ? "#" : ".") << " ";
        }
        std::cout << std::endl;
    }
}
