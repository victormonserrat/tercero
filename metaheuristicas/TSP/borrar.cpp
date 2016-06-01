#include "TSP_SimulatedAnnealing.hpp"
#include "TSP_Instance.hpp"
#include "TSP_Solution.hpp"
#include "TSP_Problem.hpp"
#include <ctime>
#include <cstdlib>

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  TSP::Instance instance ("berlin52.tsp");
  TSP::Problem problem = instance.problems()[0];
  TSP::Solution solution (problem);
  TSP::SimulatedAnnealing s (solution, 3000, 0.95, 100000);
  return 0;
}
