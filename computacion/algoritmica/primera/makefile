CXXFLAGS += -Wall -Wextra -std=c++11 -O3

all: aP1

clean:
	rm aP1 *.o bubbleGraphic heapGraphic methodsGraphic

aP1_error.o: aP1_error.cpp aP1_error.hpp
	$(CXX) $(CXXFLAGS) -c aP1_error.cpp

aP1_vector.o: aP1_vector.cpp aP1_vector.hpp
	$(CXX) $(CXXFLAGS) -c aP1_vector.cpp

aP1_timing.o: aP1_timing.cpp aP1_timing.hpp
	$(CXX) $(CXXFLAGS) -c aP1_timing.cpp

aP1_file.o: aP1_file.cpp aP1_file.hpp
	$(CXX) $(CXXFLAGS) -c aP1_file.cpp

aP1: aP1_error.o aP1_timing.o aP1_vector.o aP1_file.o aP1.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
