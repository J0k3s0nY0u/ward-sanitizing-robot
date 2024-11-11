#pragma once
#include "main.cpp"

class PathPlanner
{
private:

	// Node structure for A* algorithm
	struct Node
	{
		Position pos;
		int g; // cost from start to current node
		int h; // heuristic cost from current node to target
		int f; // total cost
		Position parent; // parent node in the path
	};

	// Comparator for priority queue based on f cost
	struct CompareNode {
		bool operator()(const Node& a, const Node& b) { return a.f > b.f; }
	};

	std::vector<std::vector<int>> grid;

	// Manhattan distance as heuristic
	int heuristic(const Position& a, const Position& b);

	std::vector<Position> getNeighbors(const Position& pos);

	bool isInBounds(const Position& pos);
	bool isObstacle(const Position& pos);

	std::vector<Position> reconstructPath(const std::unordered_map<Position, Position, PositionHash>& cameFrom, Position current);

public:

	PathPlanner(const std::vector<std::vector<int>>& grid);
	std::vector<Position> findPath(Position start, Position target);
};

