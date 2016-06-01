#include "KP_SimulatedAnnealing.hpp"
#include "KP_Instance.hpp"
#include "KP_Solution.hpp"
#include "KP_SolGenerator.hpp"


#include <cmath>
#include <cstdlib>

/***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/
#include <iostream>
#include <unistd.h>
/***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/

KP::SimulatedAnnealing::SimulatedAnnealing (KP::Solution const &solution,
                                            double const &deltaE0,
                                            double const &probability0,
                                            double const &nIt){

  KP::Instance instance;

  _t0 = -deltaE0/log(probability0);
  _t = _t0;
  KP::Solution current = solution;
  KP::Solution bestSolution = solution;

  for (unsigned int i = 1 ;  i <= nIt ; i ++){

    /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA) ***********/
    std::cout << "\E[34m\t\tVUELTA " << i << ".\e[0m" << std::endl;
    std::cout << "_t0: " << _t0 << std::endl;
    std::cout << "_t: " << _t << std::endl;
    std::cout << "bestSolution: " << instance.profit(bestSolution);
    fflush(stdout);



    /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/


    KP::SolGenerator neighbour (current);
    KP::Solution s = neighbour.generate (1)[0];


    if (instance.profit(s) > instance.profit(bestSolution)){
      bestSolution = s;
    }
    if ( accept (_t, abs(instance.profit(s) -
                         instance.profit(current)
                        )
                )
       ){
       current = s;
    }

    cool (i);

  }
  _bestSolution = bestSolution;
}

void KP::SimulatedAnnealing::cool (int const &it){
  _t = _t0 / (1 + log(1+it) );
}

bool KP::SimulatedAnnealing::accept (double const &t, double const &deltaE){
  double random = ((double)(rand()%1000)/1000);
  /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/
  std::cout << "random: " << random << std::endl;
  std::cout << "-deltaE: " << -deltaE << std::endl;
  std::cout << "exp :" << exp (-deltaE/t) << std::endl;
  std::cout << "entra: ";
  if ( exp (-deltaE/t) >= random){
      std::cout << "\E[32mtrue\e[0m";
  }
  else {std::cout << "\E[31mfalse\e[0m"; fflush(stdout);}
  std::cout << std::endl;

  /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/

  if ( exp (-deltaE/t) > random){
      return true;
  }
  else return false;
}
