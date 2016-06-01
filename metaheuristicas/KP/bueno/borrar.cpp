#include "KP_SimulatedAnnealing.hpp"
#include "KP_Instance.hpp"
#include "KP_Solution.hpp"
#include "KP_Problem.hpp"
#include <ctime>
#include <cstdlib>

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  KP::Instance instance ("knapPI_1_200_10000.csv");
  KP::Problem problem = instance.problems()[50];
  KP::Solution solution (problem);
  KP::SimulatedAnnealing s (solution, 3000, 0.95, 100000);
  return 0;
}
