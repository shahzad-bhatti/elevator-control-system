#pragma once

#include "elevator.h"

#include <cstdint>
#include <vector>

using namespace std;

class elevatorController {
public:
	elevatorController( int floorCount, int elevatorCount, int capacity);
	
	void readInput(string filename);
	void printStatus();

	void step();
	void pickUp(int callFloor, int destFloor);

private:
	int floorCount_;
	int	elevatorCount_;
	int capacity_;
	vector<elevator> elevators_;
};