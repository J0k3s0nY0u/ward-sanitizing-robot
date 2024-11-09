#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <queue>

#include "Map.h"
#include "Sensor.h"
#include "Actuator.h"
#include "PathPlanner.h"
#include "Robot.h"

struct Position
{
	int x;
	int y;
};

int main() {
	Robot sanitizingRobot(20, 20);
	sanitizingRobot.initialize();
	sanitizingRobot.exploreAndSanitize();
	sanitizingRobot.returnToBase();

	return 0;
}