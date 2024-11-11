#include "PathPlanner.h"

int PathPlanner::heuristic(const Position& a, const Position& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);;
}

std::vector<Position> PathPlanner::getNeighbors(const Position& pos)
{
    std::vector<Position> neighbors;
    std::vector<Position> possibleMoves = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // Right, Down, Left, Up

    for (const auto& move : possibleMoves) {
        Position neighbor = { pos.x + move.x, pos.y + move.y };
        if (isInBounds(neighbor)) {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

bool PathPlanner::isInBounds(const Position& pos)
{
    return pos.x >= 0 && pos.x < grid.size() && pos.y >= 0 && pos.y < grid[0].size();
}

bool PathPlanner::isObstacle(const Position& pos)
{
    return grid[pos.x][pos.y] == 1;
}

std::vector<Position> PathPlanner::reconstructPath(const std::unordered_map<Position, Position, PositionHash>& cameFrom, Position current)
{
    std::vector<Position> path;
    while (cameFrom.find(current) != cameFrom.end()) {
        path.push_back(current);
        current = cameFrom.at(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

PathPlanner::PathPlanner(const std::vector<std::vector<int>> &grid) : grid(grid)
{
}

std::vector<Position> PathPlanner::findPath(Position start, Position target)
{
    std::priority_queue<Node, std::vector<Node>, CompareNode> openList;
    std::unordered_map<Position, int, PositionHash> gCost;
    std::unordered_map<Position, Position, PositionHash> cameFrom;

    gCost[start] = 0;

    openList.push({ start, 0, heuristic(start, target), heuristic(start, target), {} });

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (current.pos == target) {
            return reconstructPath(cameFrom, current.pos);
        }

        for (const Position& neighbor : getNeighbors(current.pos)) {
            if (isObstacle(neighbor)) continue;

            int tentative_gCost = current.g + 1;
            if (tentative_gCost < gCost[neighbor] || gCost.find(neighbor) == gCost.end()) {
                cameFrom[neighbor] = current.pos;
                gCost[neighbor] = tentative_gCost;
                int h = heuristic(neighbor, target);
                openList.push({ neighbor, tentative_gCost, h, tentative_gCost + h, current.pos });
            }
        }
    }

    return {};
}
