CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: main

clean:
	rm District.o ElectoralMap.o TextUI.o main

main: District.o ElectoralMap.o TextUI.o Election.hpp main.cpp
	$(CXX) $(CXXFLAGS) main.cpp District.o ElectoralMap.o TextUI.o -o main

District.o: District.cpp
	$(CXX) $(CXXFLAGS) -c District.cpp
	
ElectoralMap.o: ElectoralMap.cpp
	$(CXX) $(CXXFLAGS) -c ElectoralMap.cpp
	
TextUI.o: TextUI.cpp
	$(CXX) $(CXXFLAGS) -c TextUI.cpp