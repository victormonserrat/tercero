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
    /*std::cout << "\E[34mVUELTA " << i << ".\e[0m" << std::endl;
    std::cout << "\t_t: " << _t;
    std::cout << "\t\t\t\t\t\t\t\t_t0: " << _t0 << std::endl;
    std::cout << "\t\E[33mcurrentSolution: " << instance.profit(current) << std::endl;
    std::cout << "\t\E[32mbestSolution: " << instance.profit(bestSolution) << std::endl;
    fflush(stdout);*/
    std::cout << i << std::endl;
    std::cout <<  _t << std::endl;
    std::cout << instance.profit(current) << std::endl;
    std::cout << instance.profit(bestSolution) << std::endl;
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

  /*GUARRO*/
  unsigned int nObjects = 0;
  for (size_t i = 0; i < bestSolution.objects().size(); i++) {
    if (bestSolution.objects()[i]){
      nObjects ++;
    }
  }
  unsigned int weight = 0;
  for (size_t i = 0 ; i < bestSolution.problem().objects().size() ; i++) {
    if (bestSolution.objects()[i]){
      weight += bestSolution.problem().objects()[i].weight();
    }
  }
  std::cout << "nObjects: " << nObjects << " and weight: " << weight << " of " << bestSolution.problem().knacksack().capacity();
  /*GUARRO*/
}

void KP::SimulatedAnnealing::cool (int const &it){
  _t = _t0 / (1 + log(1+it) );
}

bool KP::SimulatedAnnealing::accept (double const &t, double const &deltaE){
  double random = ((double)(rand()%1000)/1000);
  /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/
  //std::cout << "exp :" << exp (-deltaE/t) << std::endl;
  /***********PARTE GUARRÍSIMA (A LO YIZZUS Y MORA ) ***********/

  if ( exp (-deltaE/t) > random){
      return true;
  }
  else return false;
}
