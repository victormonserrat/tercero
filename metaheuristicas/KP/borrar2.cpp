#include "KP_GRASP.hpp"
#include "KP_Problem.hpp"
#include "KP_Instance.hpp"

#include <iostream>

/*int main(int argc, char const *argv[]) {
  srand(time(NULL));
  for (int i = 0 ; i < 100 ; i ++){
    if (i == 0 || i == 13 || i == 16 || i == 20 || i == 22 || i == 23 || i == 24 ||
        i == 27 || i == 28 || i == 33 || i == 36 || i == 38 || i == 40 || i == 47 ||
        i == 51 || i == 53 || i == 55 || i == 56 || i == 57 || i == 59 || i == 60 ||
        i == 61 || i == 62 || i == 64 || i == 66 || i == 67 || i == 68 || i == 72 ||
        i == 76 || i == 78 || i == 80 || i == 82 || i == 84 || i == 85 || i == 91 ||
        i == 93 || i == 96 || i == 97 || i == 98){
          KP::Instance instance ("knapPI_1_200_10000.csv");
          std::cout << "\E[33mProblema " << i << std::endl;
          KP::Problem problem = instance.problems()[i];
          KP::GRASP (problem, 30);
    }
  }
  return 0;
}*/

/*int main(int argc, char const *argv[]) {
  srand(time(NULL));
  for (int i = 0 ; i < 100 ; i ++){
    if (i == 13 || i == 16 || i == 22 || i == 23 || i == 24 ||
        i == 28 || i == 40 || i == 47 || i == 51 || i == 53 ||
        i == 56 || i == 59 || i == 60 || i == 61 || i == 62 ||
        i == 64 || i == 67 || i == 68 || i == 72 || i == 76 ||
        i == 78 || i == 85 || i == 91){
          KP::Instance instance ("knapPI_1_200_10000.csv");
          std::cout << "\E[33mProblema " << i << std::endl;
          KP::Problem problem = instance.problems()[i];
          KP::GRASP (problem, 35);
    }
  }
  return 0;
}*/

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  for (size_t i = 0; i < 100; i++) {
    KP::Instance instance ("knapPI_1_200_10000.csv");
    KP::Problem problem = instance.problems()[56];
    KP::GRASP (problem, 50);
  }

  return 0;
}
