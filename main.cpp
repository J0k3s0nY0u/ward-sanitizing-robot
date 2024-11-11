#include <iostream>

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#include "Sensor.h"
#include "PathPlanner.h"
#include "MotorController.h"
#include "SanitizerController.h"

// Constants for grid cell colors
const sf::Color COLOR_OBSTACLE = sf::Color::Black;
const sf::Color COLOR_FREE = sf::Color::White;
const sf::Color COLOR_START = sf::Color::Green;
const sf::Color COLOR_TARGET = sf::Color::Red;
const sf::Color COLOR_PATH = sf::Color::Blue;

struct Position
{
    int x, y;
    bool operator == (const Position& other) const {return x == other.x && y == other.y;}
};

// Hash Functions Unordered Map
struct PositionHash
{
    size_t operator()(const Position& pos) const {
        return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y) << 1;
    };
};//////

// Display grid with path in SFML (for simulation)
void displayGridWithPath(const std::vector<std::vector<int>>& grid, const std::vector<Position>& path, Position start, Position target) {
    const int cellSize = 50; // Size of each cell in pixels
    const int gridWidth = grid[0].size();
    const int gridHeight = grid.size();

    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "A* Pathfinding Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < gridHeight; ++i) {
            for (int j = 0; j < gridWidth; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(j * cellSize, i * cellSize);

                // Determine color based on grid cell content
                if (grid[i][j] == 1) {
                    cell.setFillColor(COLOR_OBSTACLE); // Obstacle
                }
                else {
                    cell.setFillColor(COLOR_FREE); // Free space
                }

                // Mark start and end points
                if (Position{ i, j } == start) {
                    cell.setFillColor(COLOR_START);
                }
                else if (Position{ i, j } == target) {
                    cell.setFillColor(COLOR_TARGET);
                }

                window.draw(cell);
            }
        }

        // Draw the path
        for (const auto& pos : path) {
            if (pos == start || pos == target) continue;
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition(pos.y * cellSize, pos.x * cellSize);
            cell.setFillColor(COLOR_PATH);
            window.draw(cell);
        }

        window.display();
    }
}

int main() {
    // Example grid: 0 = free space, 1 = obstacle
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0}
    };

    PathPlanner planner(grid);
    Position start = { 0, 0 };
    Position target = { 4, 4 };
    Sensor sensor;
    MotorController motor;
    SanitizerController sanitizer;

    // Find path using A*
    std::vector<Position> path = planner.findPath(start, target);

    if (!path.empty()) {
        displayGridWithPath(grid, path, start, target); // Visualize the path

        // Simulated movement along the path (to be replaced with actual hardware control)
        for (const auto& pos : path) {
            if (sensor.detectObstacle(pos)) {
                std::cout << "Obstacle detected at (" << pos.x << ", " << pos.y << ")\n";
                break; // If obstacle detected, stop and recalibrate
            }
            motor.moveTo(pos); // Simulate moving to the position
            sanitizer.activate(); // Simulate spraying sanitizer
        }
    }
    else {
        std::cout << "No path found.\n";
    }

    return 0;
}