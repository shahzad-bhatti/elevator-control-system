#include "job.h"
#include <iostream>

job::job() {
}
    
    
jobUp::jobUp(int cFloor, int dFloor) 
    : job() {
    addCall(cFloor);
    addDest(dFloor);
}

void jobUp::addCall(int floor) {
    auto it = callFloors_.find(floor);
    if (it != callFloors_.end()) {
        it->second++;
    } else {
        callFloors_[floor] = 1;
    }
}
    
int jobUp::topCall() {
    if (emptyCall()) {
        return -1;
    }
    return callFloors_.begin()->first;
}
    
int jobUp::removeCall(int floor) {
    auto ret = callFloors_[floor];
    callFloors_.erase(floor);
    return ret;
}
    
bool jobUp::emptyCall() {
    return callFloors_.empty();
}

void jobUp::addDest(int floor) {
    auto it = destFloors_.find(floor);
    if (it != destFloors_.end()) {
        it->second++;
    } else {
        destFloors_[floor] = 1;
    }
}
    
int jobUp::topDest() {
    if (emptyDest()) {
        return -1;
    }
    return destFloors_.begin()->first;
}
    
int jobUp::removeDest(int floor) {
    auto ret = destFloors_[floor];
    destFloors_.erase(floor);
    return ret;
}
    
bool jobUp::emptyDest() {
    return destFloors_.empty();
}


jobDown::jobDown(int cFloor, int dFloor) 
    : job{} {
    type = jobType::DOWN;
    addCall(cFloor);
    addDest(dFloor);
}

void jobDown::addCall(int floor) {
    auto it = callFloors_.find(floor);
    if (it != callFloors_.end()) {
        it->second++;
    } else {
        callFloors_[floor] = 1;
    }
}
    
int jobDown::topCall() {
    if (emptyCall()) {
        return -1;
    }
    return callFloors_.begin()->first;
}
    
int jobDown::removeCall(int floor) {
    auto ret = callFloors_[floor];
    callFloors_.erase(floor);
    return ret;
}
    
bool jobDown::emptyCall() {
    return callFloors_.empty();
}

void jobDown::addDest(int floor) {
    auto it = destFloors_.find(floor);
    if (it != destFloors_.end()) {
        it->second++;
    } else {
        destFloors_[floor] = 1;
    }
}
    
int jobDown::topDest() {
    if (emptyDest()) {
        return -1;
    }
    return destFloors_.begin()->first;
}
    
int jobDown::removeDest(int floor) {
    auto ret = destFloors_[floor];
    destFloors_.erase(floor);
    return ret;
}
    
bool jobDown::emptyDest() {
    return destFloors_.empty();
}


