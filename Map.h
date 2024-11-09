#pragma once
#include "main.cpp"
class Map
{
private:

	std::vector<std::vector<int>> grid;

public:

	Map(int width, int height);
	void updateMap(Position pos, int status);
	bool isObstacle(Position pos);
	void displayMap();
};

