CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
main: main.o amatrix.o
	$(CXX) $(CXXFLAGS) -o $@ $^
