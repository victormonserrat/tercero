#include "TSP_SimulatedAnnealing.hpp"
#include "TSP_Instance.hpp"
#include "TSP_Solution.hpp"
#include "TSP_SolGenerator.hpp"


#include <cmath>
#include <cstdlib>

/***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/
#include <iostream>
#include <unistd.h>
/***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/

TSP::SimulatedAnnealing::SimulatedAnnealing (TSP::Solution const &solution,
                                            double const &deltaE0,
                                            double const &probability0,
                                            double const &nIt){

  TSP::Instance instance;

  _t0 = -deltaE0/log(probability0);
  _t = _t0;
  TSP::Solution current = solution;
  TSP::Solution bestSolution = solution;

  for (unsigned int i = 1 ;  i <= nIt ; i ++){

    /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA) ***********/
    /*std::cout << "\E[34m\t\tVUELTA " << i << ".\e[0m" << std::endl;
    std::cout << "_t0: " << _t0 << std::endl;
    std::cout << "_t: " << _t << std::endl;
    std::cout << "bestSolution: " << instance.distance(bestSolution);
    fflush(stdout);*/
    std::cout << i << std::endl;
    std::cout <<  _t << std::endl;
    std::cout << instance.distance(current) << std::endl;
    std::cout << instance.distance(bestSolution) << std::endl;
    fflush(stdout);
    /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/


    TSP::SolGenerator neighbour (current);
    TSP::Solution s = neighbour.generate (1)[0];


    if (instance.distance(s) < instance.distance(bestSolution)){
      bestSolution = s;
    }
    if ( accept (_t, abs(instance.distance(s) -
                         instance.distance(current)
                        )
                )
       ){
       current = s;
    }

    cool (i);

  }
  _bestSolution = bestSolution;
}

void TSP::SimulatedAnnealing::cool (int const &it){
  _t = _t0 / (1 + log(1+it) );
}

bool TSP::SimulatedAnnealing::accept (double const &t, double const &deltaE){
  double random = ((double)(rand()%1000)/1000);
  /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/
  /*std::cout << "random: " << random << std::endl;
  std::cout << "-deltaE: " << -deltaE << std::endl;
  std::cout << "exp :" << exp (-deltaE/t) << std::endl;
  std::cout << "entra: ";
  if ( exp (-deltaE/t) > random){
      std::cout << "\E[32mtrue\e[0m";
  }
  else {std::cout << "\E[31mfalse\e[0m"; fflush(stdout);}
  std::cout << std::endl;*/

  /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/

  if ( exp (-deltaE/t) > random){
      return true;
  }
  else return false;
}
