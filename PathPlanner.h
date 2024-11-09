#pragma once
#include "main.cpp"

class PathPlanner
{
private:
	std::vector<std::vector<int>> grid;

	// Manhattan distance as heuristic
	int heuristic(const Position& a, const Position& b);

	std::vector<Position> getNeighbors(const Position& pos);

	bool isInBounds(const Position& pos);
	bool isObstacle(const Position& pos);

	std::vector<Position> reconstructPath(const std::unordered_map<Position, Position, PositionHash>& cameFrom, Position current);

public:

	PathPlanner(const std::vector<std::vector<int>>& grid);
	std::vector<Position> findPath(Position start, Position end, Map& map);
	std::vector<Position> findPath(Position start, Position target);
};

