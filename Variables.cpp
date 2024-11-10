#include "main.cpp"

// Constants for grid cell colors
const sf::Color COLOR_OBSTACLE = sf::Color::Black;
const sf::Color COLOR_FREE = sf::Color::White;
const sf::Color COLOR_START = sf::Color::Green;
const sf::Color COLOR_TARGET = sf::Color::Red;
const sf::Color COLOR_PATH = sf::Color::Blue;

struct Position
{
	int x, y;
	bool operator == (const Position& other) const {
		return x == other.x && y == other.y;
	}
};

// Hash Functions Unordered Map
struct PositionHash
{
	size_t operator()(const Position& pos) const {
		return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
	};
};

// Node structure for A* algorithm
struct Node {
	Position pos;
	int g; // cost from start to current node
	int h; // heuristic cost from current node to target
	int f; // total cost
	Position parent; // parent node in the path
};

// Comparator for priority queue based on f cost
struct CompareNode {
	bool operator()(const Node& a, const Node& b) {
		return a.f > b.f;
	}
};