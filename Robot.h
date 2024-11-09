#pragma once
#include "main.cpp"

class Robot
{
private:

	Position currentPosition;
	Position startPosition;
	Map map;
	Sensor sensor;
	Actuator actuator;
	PathPlanner pathPlanner;

public:

	Robot(int mapWidth, int mapHeight);
	void initialize();
	void exploreAndSanitize();
	void returnToBase();
	void updateMapIfNeeded(Position newPos);
};

