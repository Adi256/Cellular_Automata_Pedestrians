
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "pedestrian.h"
#include "floorPed.h"
#include "runs.cpp"

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

void runDiagNRuns(int p, int n, int x, int y, std::vector<std::vector<int>> doors, bool writeIterations) {
	floorPed f1 = floorPed(x, y, 1, 0, 0, 0, doors);
	ranPed(p, f1, x, y);
	f1.writeStatField2File("staticField");
	f1.writeMovements2File("initialPosition");

	if (writeIterations == 1) {
		for (int i = 0; i < n; i++) {
			f1.singleRunDiag();
			f1.writeMovements2File("iteration" + std::to_string(i));
		}
		f1.writeMovements2File("finalPosition");
	}
	else {
		for (int i = 0; i < n; i++) {
			f1.singleRunDiag();
		}
		f1.writeMovements2File("finalPosition");
	}
}

void runDiagAllSaved(int p, int n, int x, int y, std::vector<std::vector<int>> doors, bool writeIterations) {
	floorPed f1 = floorPed(x, y, 1, 0, 0.7, 0.8, doors);
	ranPed(p, f1, x, y);
	f1.writeStatField2File("staticField");
	f1.writeMovements2File("initialPosition");
	int it = 0;

	if (writeIterations == 1) {
		while (f1.numberOfSavedPed() != f1.numberOfPed()) {
			f1.singleRunDiag();
			it++;
			f1.writeMovements2File("iteration" + std::to_string(it));
		}
		f1.writeMovements2File("finalPosition");
	}
	else {
		while (f1.numberOfSavedPed() != f1.numberOfPed()) {
			f1.singleRunDiag();
			it++;
		}
		f1.writeMovements2File("finalPosition");
		std::cout << it << "\n";
	}
}

void runDiagConstPed(int p, int n, int x, int y, std::vector<std::vector<int>> doors, std::string fileName) {
	srand(time(0));
	std::vector<int> dataIterations;
	std::ofstream file;
	int it = 0;
	for (int i = 0; i < n; i++) {
		it = 0;
		floorPed f1 = floorPed(x, y, 1, 0, 0.7, 0.8, doors);
		ranPed(p, f1, x, y);
		while (f1.numberOfSavedPed() != f1.numberOfPed()) {
			f1.singleRunDiag();
			it++;
		}
		dataIterations.push_back(it);
	}

	file.open(fileName + ".txt");

	for (int i = 0; i < dataIterations.size(); i++) {
		file << i << "," << dataIterations[i] << "\n";
	}

	file.close();
}

void runDiagVarPed(int p, int x, int y, std::vector<std::vector<int>> doors, std::string fileName) {
	srand(time(0));
	std::vector<int> dataIterations;
	std::ofstream file;
	int it = 0;
	for (int i = 0; i < p; i++) {
		it = 0;
		floorPed f1 = floorPed(x, y, 1, 0, 0.7, 0.8, doors);
		ranPed(i, f1, x, y);
		while (f1.numberOfSavedPed() != f1.numberOfPed()) {
			f1.singleRunDiag();
			it++;
		}
		dataIterations.push_back(it);
	}

	file.open(fileName + ".txt");

	for (int i = 0; i < dataIterations.size(); i++) {
		file << i << "," << dataIterations[i] << "\n";
	}

	file.close();
}

int main() {

	srand(time(0));

	int n = 1000; //Number of runs
	int y = 12; //y-dimension of room
	int p = 50; //Number of pedestrians in room

	std::vector<std::vector<int>> doors;

	std::vector<int> d1 = { 0,5};

	doors.push_back(d1);

	for (int i = 0; i < 88; i++) {

		int x = 12;
		int y = 12;
		int p = 100;
		int d = 0;

		if (i % 2 == 0) {
			x += 1;
		}
		else {
			y += 1;
		}

		d = y / 2;

		std::cout << d << "\n";
		floorPed f1 = floorPed(x, y, 0.5, 0.5, 0.3, 0.2, doors);
		ranPed(p, f1, x, y);
	}

}
