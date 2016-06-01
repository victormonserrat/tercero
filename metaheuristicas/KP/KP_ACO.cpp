#include "KP_ACO.hpp"
#include "KP_Problem.hpp"
#include "KP_Solution.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>

#include <iostream> //BORRAR
#include <cstdio>

double sum (std::vector <unsigned int> const &trails,
            std::vector <double> const &ratios){
  double returnValue = 0.0;
  for (unsigned int i = 0 ; i < trails.size() ; i ++) {
    returnValue += trails[i]*ratios[i];
  }

  return returnValue;
}

KP::ACO::ACO(KP::Problem const &problem, int const &nIt){
  _problem = problem;


  for (unsigned int i = 0 ; i < problem.objects().size() ; i ++){
    _trails.push_back(1);
  }

  for (unsigned int i = 0 ; i < problem.objects().size() ; i ++){
    _ratios.push_back(
                    (double)problem.objects()[i].profit()
                    /
                    (double)problem.objects()[i].weight()
    );
  }

  for (unsigned int i = 0 ; i < nIt ; i ++){
    KP::Solution solution;
    std::vector <bool> objects (problem.objects().size(), false);
    std::vector <unsigned int>  trails = _trails;
    std::vector <double>        ratios = _ratios;
    std::vector <unsigned int>  n;
    for (unsigned int i = 0 ; i < _problem.objects().size() ; i ++){
      n.push_back(i);
    }

    while (_problem.objects().size() != 0){
      unsigned int weight = 0;
      std::vector <double> probabilities;
      for (unsigned int j = 0 ; j < _problem.objects().size() ; j ++){
        probabilities.push_back(trails[j]*ratios[j]/sum(trails, ratios));
      }

      double random = ((double)(rand()%1000000000)/1000000000);
      double tmp = 0.0;
      unsigned int object = 0;
      while (tmp <= random){
        tmp += probabilities[object];
        object ++;
      }

      if (weight < problem.knacksack().capacity()){
        objects[n[object]] = true;
        std::cout << "borra el... " << object;
        std::cout << ":) --> " << n[object] << "\t" << solution.objects()[n[object]];
        fflush(stdout);
      }
      n.erase(n.begin()+object);
      std::cout << "1" << std::endl;
      fflush(stdout);
      trails.erase(trails.begin()+object);
      std::cout << "2" << std::endl;
      fflush(stdout);
      ratios.erase(ratios.begin()+object);
      std::cout << "3" << std::endl;
      fflush(stdout);
      probabilities.erase(probabilities.begin()+object);
      std::cout << "4" << std::endl;
      fflush(stdout);
      objects.erase(objects.begin()+object);
      std::cout << "5" << std::endl;
      fflush(stdout);
    }


  }
/*  for (unsigned int i = 0 ; i < nIt ; i ++){
    std::vector <unsigned int> n;
    for (unsigned int i = 0 ; i < n.size() ; i ++){
      n.push_back(i);
    }
    while (problem_.objects().size() != 0){
      unsigned int weight = 0;
      std::vector <double> probabilities;
      double a = 0.0;//borrar
      for (unsigned int j = 0 ; j < problem_.objects().size() ; j ++){
        probabilities.push_back(trails[j]*ratios[j]/sum(trails, ratios));
        //std::cout << "probabilities[" << j << "]: " << probabilities[j] << "\t" << ratios[j] << "\t" << trails[j] << std::endl;
      }
    //  std::cout << "\E[31m" << a << "\e[0m" << std::endl;

      double random = ((double)(rand()%1000000000)/1000000000);
      double tmp = 0.0;
      unsigned int object = 0;
      while (tmp <= random){
        tmp += probabilities[object];
        object ++;
      }
      if (weight < problem.knacksack().capacity()){

      }
      trails.erase(trails.begin()+object);
      ratios.erase(ratios.begin()+object)
      probabilities.erase(probabilities.begin()+object);
      problem_.objects().erase(problem_.objects().begin()+object))
    }
  }*/

}








//unsigned int random = rand()%problem_.objects().size();
