CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: main

clean:
	rm Election.o main

main: Election.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Election.o -o main

Election.o: Election.cpp
	$(CXX) $(CXXFLAGS) -c Election.cpp
