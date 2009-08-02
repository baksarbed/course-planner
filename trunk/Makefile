OBJS1= planner.o main.o utils.o 
TARGETS= planner
GFLAGS= -g -Wall
COMPILER=g++


all:  $(TARGETS)

planner: $(OBJS1)
	$(COMPILER) $(GFLAGS) $^ -o planner

planner.o:	planner.cpp planner.h
	$(COMPILER) $(GFLAGS) -c planner.cpp

main.o:		main.cpp
	$(COMPILER) $(GFLAGS) -c main.cpp	

utils.o:	utils.cpp utils.h
	$(COMPILER) $(GFLAGS) -c utils.cpp

clean:	
	rm -rf *~ *.o $(TARGETS)

