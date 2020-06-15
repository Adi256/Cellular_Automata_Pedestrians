
#include "stdafx.h"
#include <iostream>
#include "pedestrian.h"
#include "floorPed.h"

void ranPed(int n, floorPed& f1, int x, int y) {

	if (n >= (x - 2)*(y - 2)) {
		std::cout << "Thats too many" << "\n";
	}
	for (int i = 0; i < n; i++) {
		pedestrian temp = pedestrian(1 + rand() % (x - 2), 1 + rand() % (y - 2));
		if (f1.addPed(temp) == 0) {
			i--;
		}
	}
}

int main() {
	int n = 5; //Number of runs
	int x = 5; //x-dimension of room
	int y = 5; //y-dimension of room
	int p = 2; //Number of pedestrians in room

	std::vector<std::vector<int>> doors;

	std::vector<int> d1 = { 0,2 };
	std::vector<int> d2 = { 0,3 };
	std::vector<int> d3 = { 0,4 };
	std::vector<int> d4 = { 0,5 };
	std::vector<int> d5 = { 0,6 };
	std::vector<int> d6 = { 0,7 };

	doors.push_back(d1);
	//doors.push_back(d2);
	//doors.push_back(d3);
	//doors.push_back(d4);
	//doors.push_back(d5);
	//doors.push_back(d6);


	floorPed f1 = floorPed(x, y, 1, 0, 0.7, 0.8, doors);
	//ranPed(p, f1, x, y);
	pedestrian p1 = pedestrian(1, 1);
	pedestrian p2 = pedestrian(1, 3);
	f1.addPed(p1);
	f1.addPed(p2);
	std::cout << "init # ped: " << f1.numberOfPed() << "\n";

	f1.writeStatField2File("statField");
	f1.writeMovements2File("initialPosition");


	f1.singleRunAllTogether();

	f1.writeMovements2File("finalPosition");
	
	std::cout << "final # ped: " << f1.numberOfPed() - f1.numberOfSavedPed() << "\n";
	

}

