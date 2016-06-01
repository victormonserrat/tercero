<<<<<<< HEAD
CXXFLAGS += -Wall -Wextra -std=c++14 -O3
=======
CXXFLAGS += -Wall -Wextra -std=c++14
>>>>>>> 4784328875945354f7c4ea47b2c8c70f9610015b

all: KP_Best KP_First borrar borrar2
	rm *.o

clean:
	rm KP_First KP_Best *.o *.txt *.eps

cleanObj:
	rm KP_First KP_Best *.o

cleanTxt:
	rm *.txt

cleanImg:
	rm *.eps

KP_Knacksack.o: KP_Knacksack.cpp KP_Knacksack.hpp
	$(CXX) $(CXXFLAGS) -c KP_Knacksack.cpp

KP_Object.o: KP_Object.cpp KP_Object.hpp
	$(CXX) $(CXXFLAGS) -c KP_Object.cpp

KP_Problem.o: KP_Knacksack.cpp KP_Knacksack.hpp KP_Object.cpp KP_Object.hpp KP_Problem.cpp KP_Problem.hpp
	$(CXX) $(CXXFLAGS) -c KP_Problem.cpp

KP_Instance.o: KP_Problem.cpp KP_Problem.hpp KP_Instance.cpp KP_Instance.hpp
	$(CXX) $(CXXFLAGS) -c KP_Instance.cpp

KP_Solution.o: KP_Problem.cpp KP_Problem.hpp KP_Solution.cpp KP_Solution.hpp
	$(CXX) $(CXXFLAGS) -c KP_Solution.cpp

KP_SolGenerator.o: KP_Solution.cpp KP_Solution.hpp KP_SolGenerator.cpp KP_SolGenerator.hpp
	$(CXX) $(CXXFLAGS) -c KP_SolGenerator.cpp

KP_FirstNeighExplorator.o: KP_Solution.cpp KP_Solution.hpp KP_SolGenerator.cpp KP_SolGenerator.hpp KP_Instance.cpp KP_Instance.hpp KP_FirstNeighExplorator.cpp KP_FirstNeighExplorator.hpp
	$(CXX) $(CXXFLAGS) -c KP_FirstNeighExplorator.cpp

KP_BestNeighExplorator.o: KP_Solution.cpp KP_Solution.hpp KP_SolGenerator.cpp KP_SolGenerator.hpp KP_Instance.cpp KP_Instance.hpp KP_BestNeighExplorator.cpp KP_BestNeighExplorator.hpp
	$(CXX) $(CXXFLAGS) -c KP_BestNeighExplorator.cpp

KP_LocalSearch.o: KP_Solution.cpp KP_Solution.hpp KP_FirstNeighExplorator.o KP_BestNeighExplorator.o KP_LocalSearch.cpp KP_LocalSearch.hpp
	$(CXX) $(CXXFLAGS) -c KP_LocalSearch.cpp

KP_SimulatedAnnealing.o: KP_Instance.o KP_Solution.o KP_SolGenerator.o KP_SimulatedAnnealing.cpp KP_SimulatedAnnealing.hpp
	$(CXX) $(CXXFLAGS) -c KP_SimulatedAnnealing.cpp

KP_GRASP.o: KP_Instance.o KP_Problem.o KP_Object.o KP_GRASP.cpp KP_GRASP.hpp
	$(CXX) $(CXXFLAGS) -c KP_GRASP.cpp

KP_First: KP_Knacksack.o KP_Object.o KP_Problem.o KP_Instance.o KP_Solution.o KP_SolGenerator.o KP_FirstNeighExplorator.o KP_BestNeighExplorator.o KP_LocalSearch.o KPFirst.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

KP_Best: KP_Knacksack.o KP_Object.o KP_Problem.o KP_Instance.o KP_Solution.o KP_SolGenerator.o KP_FirstNeighExplorator.o KP_BestNeighExplorator.o KP_LocalSearch.o KPBest.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

borrar: KP_Knacksack.o KP_Object.o KP_Problem.o KP_Instance.o KP_Solution.o KP_SolGenerator.o KP_FirstNeighExplorator.o KP_BestNeighExplorator.o KP_LocalSearch.o KP_SimulatedAnnealing.o borrar.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

borrar2: KP_LocalSearch.o KP_SolGenerator.o KP_BestNeighExplorator.o KP_FirstNeighExplorator.o KP_LocalSearch.o KP_Knacksack.o KP_Solution.o KP_Instance.o KP_Problem.o KP_Object.o KP_GRASP.o borrar2.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
