#Building the program:

run ``make`` to build the program (you will need C++14). I tested it with GCC 5.4 on ubuntu 16.04.

#Running the program: 
``./ecs <number of elevators> <elevator capacity> <input file containg commands>``

Input file can have the following commands on at a line.
a) ``status`` - display the status of each elevator.
b) ``pickup <call floor> <dest floor>`` 
c) ``step`` - each non-idle elvator moves to the next floor depending on the job.

#Assumptions:
1. All elvators are identical in terms of speed and capacity.
2. Time delay for loading/unloading passerngers is same regardless of the number of passerngers.
3. All elvators can serve all floors.
4. If an elevator reaches its capacity, it does not accept more passengers.

#Design:
There are three classes in the elevator control system namely elevatorController, elevator, job.

a) Elevator Controller:
An elevator controller object controls all the elevators. It is contructed with args ``<number of elevators> <elevator capacity>``. It then constructs ``<number of elevators>`` elevators and stores them in a vector.

Upon receiving a ``pickup`` command, it calculates a score for each elevator and assign the pickup job to the elevator with lowest score. For score calculation, please see ``pickUp`` function in ``elevatorController.cc``.

When it receives a ``step`` command, it asks each elevator to perform a step which corresponds to moving to the next floor for non-idle elevators.


b) Elevator:
An elevator object controls an elevator. At any moment in time, it can be in any of the four states; IDLE, ON_WAY(empty elvator responding to a call), UP(carrying passengers to upper floors), DOWN(carring passengers to lower floors).

When an elevator receives a ``pickup`` request, it will add the pickup to its current job if the elevator is going in the direction of the call and the call floor. Otherwise, it will construct a new job and adds it to job Queue.

c) Job:
A job is an abstract class from which two classes are inherited; upJob and downJob. These jobs have two map (floor: passengers) member varibles, a callFloors map and a destFloors map. For a pickup request, a callFloor is added to callFloors and a destFloor is added to destFloors. If a callFloor or a destFloor is already in the map then only passenger count is increased by one, otherwise a new entry (floor: 1) is added. 

When an elevator reaches a floor, it checks if the topCall or topDest is current floor. It then removes the topCall or topDest from the map and updates the passengerCount. When passengerCount is zero, it moves to IDLE state and stays on the same floor.

#Data Structures used:
1. A vector of size ``elevatorCount`` in elevatorController to store all the elevator objects.
2. A queue of jobs in elevator to queue up jobs assigned by elevatorController.
3. A map callFloors of (floors : passengers) in jobUp to store the key-value pair of floors and number of passengers. Entries are stored in _increasing_ order of floors, so that the first entry in the map is the next callFloor. Upon reaching the next callFloor, top Entry is removed from the map and passengerCount is incremented.
4. A map destFloors of (floors : passengers) in jobUp to store the key-value pair of floors and number of passengers. Entries are stored in _increasing_ order of floors, so that the first entry in the map is the next destFloor. Upon reaching the next destFloor, top Entry is removed from the map and passengerCount is decremented.
5. A map callFloors of (floors : passengers) in jobDown to store the key-value pair of floors and number of passengers. Entries are stored in _decreasing_ order of floors, so that the first entry in the map is the next callFloor. Upon reaching the next callFloor, top Entry is removed from the map and passengerCount is incremented.
6. A map destFloors of (floors : passengers) in jobDown to store the key-value pair of floors and number of passengers. Entries are stored in _decreasing_ order of floors, so that the first entry in the map is the next destFloor. Upon reaching the next destFloor, top Entry is removed from the map and passengerCount is decremented.
