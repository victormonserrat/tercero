CXXFLAGS += -Wall -Wextra -std=c++14

all: TSP_Best TSP_First borrar borrar2
	rm *.o

clean:
	rm TSP_First TSP_Best *.o *.txt *.eps

cleanObj:
	rm TSP_First TSP_Best *.o

cleanTxt:
	rm *.txt

cleanImg:
	rm *.eps

TSP_Node.o: TSP_Node.cpp TSP_Node.hpp
	$(CXX) $(CXXFLAGS) -c TSP_Node.cpp

TSP_Problem.o: TSP_Node.cpp TSP_Node.hpp TSP_Problem.cpp TSP_Problem.hpp
	$(CXX) $(CXXFLAGS) -c TSP_Problem.cpp

TSP_Instance.o: TSP_Problem.cpp TSP_Problem.hpp TSP_Instance.cpp TSP_Instance.hpp
	$(CXX) $(CXXFLAGS) -c TSP_Instance.cpp

TSP_Solution.o: TSP_Problem.cpp TSP_Problem.hpp TSP_Solution.cpp TSP_Solution.hpp
	$(CXX) $(CXXFLAGS) -c TSP_Solution.cpp

TSP_SolGenerator.o: TSP_Solution.cpp TSP_Solution.hpp TSP_SolGenerator.cpp TSP_SolGenerator.hpp
	$(CXX) $(CXXFLAGS) -c TSP_SolGenerator.cpp

TSP_FirstNeighExplorator.o: TSP_Solution.cpp TSP_Solution.hpp TSP_SolGenerator.cpp TSP_SolGenerator.hpp TSP_Instance.cpp TSP_Instance.hpp TSP_FirstNeighExplorator.cpp TSP_FirstNeighExplorator.hpp
	$(CXX) $(CXXFLAGS) -c TSP_FirstNeighExplorator.cpp

TSP_BestNeighExplorator.o: TSP_Solution.cpp TSP_Solution.hpp TSP_SolGenerator.cpp TSP_SolGenerator.hpp TSP_Instance.cpp TSP_Instance.hpp TSP_BestNeighExplorator.cpp TSP_BestNeighExplorator.hpp
	$(CXX) $(CXXFLAGS) -c TSP_BestNeighExplorator.cpp

TSP_LocalSearch.o: TSP_Solution.cpp TSP_Solution.hpp TSP_FirstNeighExplorator.o TSP_BestNeighExplorator.o TSP_LocalSearch.cpp TSP_LocalSearch.hpp
		$(CXX) $(CXXFLAGS) -c TSP_LocalSearch.cpp

TSP_SimulatedAnnealing.o: TSP_Instance.o TSP_Solution.o TSP_SolGenerator.o TSP_FirstNeighExplorator.o TSP_SimulatedAnnealing.cpp TSP_SimulatedAnnealing.hpp
	$(CXX) $(CXXFLAGS) -c TSP_SimulatedAnnealing.cpp

TSP_GRASP.o: TSP_Node.o TSP_Problem.o TSP_Instance.o TSP_Solution.o TSP_SolGenerator.o TSP_GRASP.cpp TSP_GRASP.hpp
	$(CXX) $(CXXFLAGS) -c TSP_GRASP.cpp

TSP_First: TSP_Node.o TSP_Problem.o TSP_Instance.o  TSP_Solution.o TSP_SolGenerator.o TSP_FirstNeighExplorator.o TSP_BestNeighExplorator.o TSP_LocalSearch.o TSPFirst.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

TSP_Best: TSP_Node.o TSP_Problem.o TSP_Instance.o  TSP_Solution.o TSP_SolGenerator.o TSP_FirstNeighExplorator.o TSP_BestNeighExplorator.o TSP_LocalSearch.o TSPBest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

borrar: TSP_Node.o TSP_Problem.o TSP_Instance.o  TSP_Solution.o TSP_SolGenerator.o TSP_FirstNeighExplorator.o TSP_BestNeighExplorator.o TSP_LocalSearch.o TSP_SimulatedAnnealing.o borrar.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

borrar2: TSP_Node.o TSP_Problem.o TSP_Instance.o  TSP_Solution.o TSP_SolGenerator.o TSP_FirstNeighExplorator.o TSP_BestNeighExplorator.o TSP_LocalSearch.o TSP_GRASP.o borrar2.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
