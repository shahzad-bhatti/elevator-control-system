CXX = g++
CXXFLAGS = -std=c++14 -g -O0 -c -Wall -Wextra
LDFLAGS = -std=c++14 -o

.PHONY: all clean tidy

ifdef SANITIZE
		CXXFLAGS += -fsanitize=$(SANITIZE)
		LDFLAGS += -fsanitize=$(SANITIZE)
endif

EXENAME = ecs
OBJECTS = elevatorController.o elevator.o job.o main.o

all : $(EXENAME)

ecs : main.o elevatorController.o elevator.o job.o
		$(CXX) main.o elevatorController.o elevator.o job.o $(LDFLAGS) ecs

main.o : main.cc elevatorController.o elevator.o job.o
		$(CXX) main.cc $(CXXFLAGS)
		   
elevatorController.o : elevatorController.cc elevator.o job.o
		$(CXX) $(CXXFLAGS) elevatorController.cc

elevator.o : elevator.cc job.o
		$(CXX) $(CXXFLAGS) elevator.cc

job.o : job.cc
		$(CXX) $(CXXFLAGS) job.cc

clean:
		rm -f $(EXENAME) *.o 2>/dev/null

tidy:
		rm -rf doc

