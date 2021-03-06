
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "pedestrian.h"
#include "floorPed.h"
#include "runs.h"


int main() {

	srand(time(0));

	int n = 10; //Number of runs
	int x = 12; //x-dimension of room
	int y = 12; //y-dimension of room
	int p = 30; //Number of pedestrians in room

	std::vector<std::vector<int>> door;
	door.push_back({ 0,5 });

	floorPed f1 = floorPed(x, y, 1, 0.5, 0.5, 0.1, door);
	f1.writeStatField2File("statFieldTest");
	f1.ranPed(p);

	f1.writeMovements2File("initialPosition");

	for (int i = 0; i < n; i++) {

		f1.singleRunDynField();
		
		f1.writeDynField2File("dynField_at" + std::to_string(i));
		f1.writeMovements2File("position_at" + std::to_string(i));

	}

	f1.writeMovements2File("finalPosition");

	runDiagConstPed(2, 10, 10, 10, door, "test");
}
