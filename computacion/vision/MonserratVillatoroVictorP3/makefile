CXXFLAGS += -Wall -std=c++11

all: unsharp

clean:
	rm unsharp *.o *.png

p3_getopt.o: p3_getopt.cpp p3_getopt.hpp
	$(CXX) $(CXXFLAGS) -c p3_getopt.cpp

unsharp_mask.o: unsharp_mask.cpp unsharp_mask.hpp
	$(CXX) $(CXXFLAGS) -c unsharp_mask.cpp

unsharp: p3_getopt.o unsharp_mask.o unsharp.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ `pkg-config opencv --cflags --libs`
