CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: main

clean:
	rm District.o ElectoralMap.o main

main: District.o ElectoralMap.o Election.hpp main.cpp
	$(CXX) $(CXXFLAGS) main.cpp District.o ElectoralMap.o -o main

District.o: District.cpp
	$(CXX) $(CXXFLAGS) -c District.cpp
	
ElectoralMap.o: ElectoralMap.cpp
	$(CXX) $(CXXFLAGS) -c ElectoralMap.cpp