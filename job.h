#pragma once

#include <cstdint>
#include <map> 
#include <memory>   

using namespace std;

enum class jobType {UP, DOWN};

struct greaterComp {
    bool operator() (const int& lhs, const int& rhs) const {
        return lhs > rhs;
    }
};

class job {
public:
    job();
    virtual ~job() = default;
    /*
     * add and remove destination floors
     */
    virtual int topDest() = 0;
    virtual int removeDest(int dest) = 0;
    virtual void addDest(int floor) = 0;
    virtual bool emptyDest() = 0;   
    
    /*
     * add and remove call floors
     */
    virtual int topCall() = 0;
    virtual int removeCall(int dest) = 0;
    virtual void addCall(int floor) = 0;
    virtual bool emptyCall() = 0;
    jobType type;
};

class jobUp : public job {
public:
    jobUp(int cfloor, int dfloor);
    
    void addCall(int floor);
    int topCall();
    int removeCall(int floor);
    bool emptyCall();

    void addDest(int floor);
    int topDest();
    int removeDest(int floor);
    bool emptyDest();
    
private:
    map<int, int> callFloors_;
    map<int, int> destFloors_;
};

class jobDown : public job {
public:
    jobDown(int sfloor, int dfloor);

    void addCall(int floor);
    int topCall();
    int removeCall(int floor);
    bool emptyCall();

    void addDest(int floor);
    int topDest();
    int removeDest(int floor);
    bool emptyDest();
    
private:
    map<int, int, greaterComp> callFloors_;
    map<int, int, greaterComp> destFloors_;
};



inline unique_ptr<job> make_job(int cFloor, int dFloor) {
    if (cFloor < dFloor) {
        unique_ptr<jobUp> j(new jobUp{cFloor, dFloor});
        return j;
    } else {
        unique_ptr<jobDown> j(new jobDown{cFloor, dFloor});
        return j;
    }
}



