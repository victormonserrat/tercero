CXXFLAGS += -Wall -std=c++11

all: getContour

clean:
	rm getContour *.o *.txt

p5_getopt.o: p5_getopt.cpp p5_getopt.hpp
	$(CXX) $(CXXFLAGS) -c p5_getopt.cpp

getContour: p5_getopt.o getContour.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ `pkg-config opencv --cflags --libs`
