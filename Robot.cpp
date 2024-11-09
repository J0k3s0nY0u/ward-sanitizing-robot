#include "Robot.h"

Robot::Robot(int mapWidth, int mapHeight) : map(mapWidth, mapHeight), startPosition({0, 0}), currentPosition(startPosition)
{
}

void Robot::initialize()
{
	std::cout << "Initializing at Start Position. \n";
	map.updateMap(startPosition, 0);
}

void Robot::exploreAndSanitize()
{
	Position nextPosition = currentPosition;
	while (true)
	{
		if (sensor.detectObstacle(nextPosition)) {
			map.updateMap(nextPosition, 1);
			continue;
		}
		// Move & Sanitize
		actuator.moveTo(nextPosition);
		actuator.spraySanitizer();

		// Update Map & Current Position
		map.updateMap(nextPosition, 0);
		currentPosition = nextPosition;
	}
}

void Robot::returnToBase()
{
}

void Robot::updateMapIfNeeded(Position newPos)
{
}
