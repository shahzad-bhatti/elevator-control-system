

#include "elevator.h"

#include <iostream>
#include <stdexcept>

elevator::elevator(int id, int capacity) 
    : id_{id}, capacity_{capacity} {
    currFloor_ = 0;
    currStatus_ = status::IDLE;
    passengerCount_ = 0;
}

elevator::elevator(int id, int capacity, int currFloor) 
    : id_{id}, capacity_{capacity}, currFloor_{currFloor} {
    currStatus_ = status::IDLE;
    passengerCount_ = 0; 
}
     
void elevator::addPickUp(int callFloor, int destFloor) {
    if ((currStatus_ == status::UP && destFloor > callFloor && callFloor > currFloor_)  ||
        (currStatus_ == status::DOWN && destFloor < callFloor && callFloor < currFloor_)) {
        currJob_->addCall(callFloor);
        currJob_->addDest(destFloor);
    } else if (!currJob_) {
        currJob_ = make_job(callFloor, destFloor);
        currStatus_ = status::ON_WAY;
    } else {
        addJob(callFloor, destFloor);
    }
}

void elevator::addJob(int callFloor, int destFloor) {
    auto j = make_job(callFloor, destFloor);
    
    jobQ_.push(move(j));
}

int elevator::surplus() {
    return capacity_ - passengerCount_;
}

void elevator::step() {
    if (currJob_) {
        takeStep();
    } else if (!jobQ_.empty()) {
        currJob_ = move(jobQ_.front());
        jobQ_.pop();
        currStatus_ = status::ON_WAY;
        takeStep();
    }
}

void elevator::nextFloor() {
    if (currStatus_ == status::UP) {
        ++currFloor_;
    } else if (currStatus_ == status::DOWN) {
        --currFloor_;
    } else if (currStatus_ == status::ON_WAY) {
        if (currJob_->topCall() > currFloor_) {
            ++currFloor_; 
        } else {
           --currFloor_;
        }
    }
}
void elevator::takeStep() {
    if (currStatus_ == status::ON_WAY) {
        if (currFloor_ != currJob_->topCall()) {
            nextFloor();
        } else {
            if (currJob_->type == jobType::UP) {
                currStatus_ = status::UP;
            } else {
                currStatus_ = status::DOWN;
            }
            takeStep();
        }
        
        if (currFloor_ == currJob_->topCall()) {
            passengerCount_ += currJob_->removeCall(currFloor_);
            passengerCount_ = min(passengerCount_, capacity_);
            if (currJob_->type == jobType::UP) {
                currStatus_ = status::UP;
            } else {
                currStatus_ = status::DOWN;
            }
        }

    } else {
        nextFloor();
        if (currFloor_ == currJob_->topDest() && currFloor_ == currJob_->topCall()) {
            passengerCount_ -= currJob_->removeDest(currFloor_);
            passengerCount_ += currJob_->removeCall(currFloor_);
            passengerCount_ = min(passengerCount_, capacity_);
    
        } else if (currFloor_ == currJob_->topDest()) {
            passengerCount_ -= currJob_->removeDest(currFloor_);
            if (passengerCount_ == 0) {
                currStatus_ = status::IDLE;
                currJob_.reset();
            }
            
        } else if (currFloor_ == currJob_->topCall()) {
            passengerCount_ += currJob_->removeCall(currFloor_);
            passengerCount_ = min(passengerCount_, capacity_);
        }
    }
}

status elevator::getStatus() {
    return currStatus_;
}

int elevator::getId() {
    return id_;
}

int elevator::getCurrFloor() {
    return currFloor_;
}

int elevator::qSize() {
    return jobQ_.size();
}

string elevator::getStatusStr() {
    switch(currStatus_) {
        case status::IDLE :
            return "idle";
        case status::ON_WAY :
            return "on way";
        case status::UP :
            return "up";
        case status::DOWN :
            return "down";
        default :
            throw runtime_error("invalid elevator status");            
    }
}
    
void elevator::printStatus() {
    cout << getId() << "\t" << getCurrFloor() 
        << "\t\t" << getStatusStr() << "\t\t" << passengerCount_ << endl; 
}

