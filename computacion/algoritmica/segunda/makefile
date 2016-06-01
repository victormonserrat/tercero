CXXFLAGS += -std=c++11 -O3

all: aP2

clean:
	rm aP2 *.o iterativeGraphic recursiveGraphic methodsGraphic

#aP2_error.o: aP2_error.cpp aP2_error.hpp
#	$(CXX) $(CXXFLAGS) -c aP2_error.cpp

#aP2_matrix.o: aP2_matrix.cpp aP2_matrix.hpp matriz.hpp
#	$(CXX) $(CXXFLAGS) -c aP2_matrix.o

#aP2_det.o:

#aP2_timing.o: aP2_matrix.o time.hpp aP2_det.o aP2_timing.cpp aP2_timing.hpp

#aP2_fit.o:

#aP2_cubic.o:

#aP2_factorial.o:

#aP2_file.o:

#aP2: aP2_error.o aP2_timing.o aP2_cubic.o aP2_factorial.o aP2_file.o
#	$(CXX) $(CXXFLAGS) $^ -o $@

aP2: aP2.cpp
	$(CXX) $(CXXFLAGS) *.cpp -o $@
