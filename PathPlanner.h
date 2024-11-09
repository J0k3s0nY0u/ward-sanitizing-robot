#pragma once
#include "main.cpp"

class PathPlanner
{
public:

	std::vector<Position> findPath(Position start, Position end, Map& map);
};

