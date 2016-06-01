CXXFLAGS += -Wall -std=c++11

all: vseg

clean:
	rm vseg *.o *.png *.avi

p4_getopt.o: p4_getopt.cpp p4_getopt.hpp
	$(CXX) $(CXXFLAGS) -c p4_getopt.cpp

vseg: p4_getopt.o vseg.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ `pkg-config opencv --cflags --libs`
