
#include "elevatorController.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>



using namespace std;

int main(int argc, char *argv[]) {
    
    if (argc < 5) {
        cout << "USAGE: " << argv[0] << " <floor count>" << " <elevator count>" 
        	 << " <capacity>" << " <input_file>" << endl;
        exit(1);
    }

    int floorCount = atoi(argv[1]);
    int elevatorCount = atoi(argv[2]);
    int capacity = atoi(argv[3]);
    string filename = argv[4];

    elevatorController ec(floorCount, elevatorCount, capacity);

    ec.readInput(filename);

    return 0;
}
