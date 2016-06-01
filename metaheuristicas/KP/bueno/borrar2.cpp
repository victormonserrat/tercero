#include "KP_GRASP.hpp"
#include "KP_Problem.hpp"
#include "KP_Instance.hpp"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  KP::Instance instance ("knapPI_1_200_10000.csv");
  KP::Problem problem = instance.problems()[50];
  KP::GRASP (problem, 10000);
  return 0;
}
