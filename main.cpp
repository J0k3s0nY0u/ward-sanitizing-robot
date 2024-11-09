#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

#include "Map.h"
#include "Sensor.h"
#include "Actuator.h"
#include "PathPlanner.h"
#include "Robot.h"

struct Position
{
	int x, y;
	bool operator == (const Position& other) const {
		return x == other.x && y == other.y;
	}
};

struct PositionHash
{
	size_t operator()(const Position& pos) const {
		return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
	};
};

struct Node
{
	Position pos;
	int g;
	int h;
	int f;
	Position parent;
};

struct CompareNode
{
	bool operator()(const Node& a, const Node& b) {
		return a.f > b.f;
	}
};

int main() {
	Robot sanitizingRobot(20, 20);
	sanitizingRobot.initialize();
	sanitizingRobot.exploreAndSanitize();
	sanitizingRobot.returnToBase();

	return 0;
}