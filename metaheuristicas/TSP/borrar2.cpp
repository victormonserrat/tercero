#include "TSP_GRASP.hpp"
#include "TSP_Problem.hpp"
#include "TSP_Instance.hpp"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  TSP::Instance instance ("berlin52.tsp");
  TSP::Problem problem = instance.problems()[0];
  TSP::GRASP (problem, 100000);
  return 0;
}
