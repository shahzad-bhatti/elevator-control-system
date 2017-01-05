#pragma once

#include "job.h"

#include <cstdint>
#include <memory>
#include <queue>
#include <memory>

/*
 * status of an elevator
 * IDLE     : elevator is at rest.
 * ON_WAY   : elevator is moving towards the calling floor.
 * UP       : elevator is taking passengers to higher floors.
 * DOWN     : elevator is takeing passengers to lower floors.
 *
 */
enum class status {IDLE, ON_WAY, UP, DOWN};

/*
 * elevator class to describe an elevator
 *
 */

class elevator {
public:
        
    elevator(int id, int capacity);

    elevator(int id, int capacity, int currFloor);
    
    void addPickUp(int callFloor, int destFloor);
    
    int surplus();
    void step();
    void printStatus();

    status getStatus();
    
    int getId();
    
    int getCurrFloor();
    
    int qSize();
private:
    void addJob(int callFloor, int destFloor);
    void nextFloor();
    void takeStep();
    string getStatusStr();

    int id_;
    int capacity_;
    int currFloor_;
    status currStatus_;
    int passengerCount_;
    queue<unique_ptr<job>> jobQ_;
    unique_ptr<job> currJob_;
};
