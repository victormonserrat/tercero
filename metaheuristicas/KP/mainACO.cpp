#include "KP_ACO.hpp"
#include "KP_Instance.hpp"
#include "KP_Problem.hpp"

int main(int argc, char const *argv[]) {
  KP::Instance instance ("knapPI_1_200_10000.csv");
  KP::Problem problem;
  problem = instance.problems()[50];
  KP::ACO ACO (problem, 1000);
  return 0;
}
