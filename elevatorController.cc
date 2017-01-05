

#include "elevatorController.h"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <cstdlib>
#include <climits>


elevatorController::elevatorController(int floorCount, int elevatorCount, int capacity)
	: floorCount_{floorCount}, elevatorCount_{elevatorCount}, capacity_{capacity} {
	for (int i = 0; i < elevatorCount_; ++i) {
		elevators_.emplace_back(elevator(i, capacity_));
	}
}

void elevatorController::readInput(string filename) {
	ifstream file(filename);
	string line;
	while (file >> line) {
		if (line.compare("status") == 0) {
			printStatus();
		} else if (line.compare("step") == 0) {
			cout << "step:" << endl;
			step();
		} else if (line.compare("pickup") == 0) {
			int call, dest;
			file >> call >> dest;
			cout << "pickup " << call << " -> " << dest;
			pickUp(call, dest);
		} else {
			cout << "invalid command " << line << endl;
			exit(2); 
		}
	}
}

void elevatorController::printStatus() {
	cout << "id" << "\t" << "currFloor" << "\t" << "status" << "\t\t" << "passengerCount" << endl; 
	for (auto &e : elevators_) {
		e.printStatus();
	}
}

void elevatorController::step() {
	for (auto &e : elevators_) {
		e.step();
	}
}

void elevatorController::pickUp(int callFloor, int destFloor) {
	int distance = 0;
	int minScore = INT_MAX;
	int score = 0;
	int idealElevator = 0;
	for (auto &e : elevators_) {
		auto cStatus = e.getStatus();
		auto currFloor = e.getCurrFloor();
		distance = abs(currFloor - callFloor);
		score = floorCount_ * e.qSize();
		if (cStatus == status::ON_WAY) {
			score += floorCount_;
		} else if ((cStatus == status::UP && destFloor > callFloor && callFloor > currFloor) ||
					(cStatus == status::DOWN && destFloor < callFloor && callFloor < currFloor)) { // moving in the direction of call
			score += distance - e.surplus() - 2;
		} else if (cStatus == status::IDLE) { // elevator is idle
			score += distance - e.surplus() - 1;
		} else {	// elevator is moving in opposite direction of this job 
			score += distance - e.surplus();
		}
		if (score < minScore) {
			minScore = score;
			idealElevator = e.getId();
		}
	}
	cout << " allocated to " << idealElevator << ":" << endl;
	elevators_[idealElevator].addPickUp(callFloor, destFloor);
}

