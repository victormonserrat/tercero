#include "TSP_Instance.hpp"
#include "TSP_Problem.hpp"
#include "TSP_Solution.hpp"
#include "TSP_LocalSearch.hpp"
#include "TSP_BestNeighExplorator.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main(int argc, char const *argv[]) {
  if (argc != 4){
    std::cout << "\E[31mUssage: ./TSPBest fileName numberOfProblemOfTheObject numberOfLocalOptimizationSolutions\e[0m" << std::endl;
    return -1;
  }
  srand(time(NULL));
  std::string fileName = argv[1];
  int nProblem = atoi(argv[2]);
  int nLocalOptimizationSolutions = atoi(argv[3]);
  int nRandomSearchSolutions = 10; /*se especifica en la práctica */

  std::vector<double> randomSearchDistances;
  std::vector<double> localOptimizationDistances;
  std::vector<unsigned int> tamLocalOptimizationVector;

  std::string fileNameWithoutExtension = fileName.substr(0, fileName.size()-4);
  std::string fileNameWithoutExtensionOutput =  "Best_" + fileNameWithoutExtension + "-" +
                                                std::to_string(nProblem) + "-" +
                                                std::to_string(nLocalOptimizationSolutions) + "-";


  std::ofstream randomSearchSolutionsFile, localOptimizationSolutionsFile, nSolutionsFile;


  TSP::Instance instance(fileName.c_str());
  TSP::Problem problem = instance.problems()[nProblem];

  for (unsigned int i = 0; i < nRandomSearchSolutions; i++) {
    TSP::Solution solution(problem);
    TSP::BestNeighExplorator b(nLocalOptimizationSolutions);
    TSP::LocalSearch l(b);
    l.search(solution);
    std::vector<double> localOptimizationDistancesAux = l.distances();

    for (unsigned int j = 0 ; j < localOptimizationDistancesAux.size() ; j ++){
      localOptimizationDistances.push_back(localOptimizationDistancesAux[j]);
      tamLocalOptimizationVector.push_back(localOptimizationDistancesAux.size());
    }
    localOptimizationDistances.push_back(instance.distance(solution)); //meter el randomSearch solution en el localOptimization
    tamLocalOptimizationVector.push_back(localOptimizationDistancesAux.size());
    randomSearchDistances.push_back(instance.distance(solution));
    std::cout << "\E[32mSolución " << i << ".\e[0m" << std::endl;
  }

  int k = 0;
  int aumento = 0;
  int m = 0;
  for (auto it = std::begin(localOptimizationDistances) ; it + randomSearchDistances.size() <= std::end(localOptimizationDistances); it += aumento){
    aumento = tamLocalOptimizationVector[k]+1;
    std::sort( it, it + aumento );
    if (randomSearchDistances[m] > randomSearchDistances[m+1]){
      std::reverse(it, it + aumento );
    }
    m++;
    k += aumento;
  }

  randomSearchSolutionsFile.open((fileNameWithoutExtensionOutput + "RandomSearch.txt").c_str(),
                          std::ios::trunc);
  localOptimizationSolutionsFile.open((fileNameWithoutExtensionOutput + "LocalOptimization.txt").c_str(),
                          std::ios::trunc);
  nSolutionsFile.open((fileNameWithoutExtensionOutput + "nSolutions.txt").c_str(),
                          std::ios::trunc);

  k = 0;
  for (unsigned int i = 0 ; i < localOptimizationDistances.size() ; i ++){
    if (k < randomSearchDistances.size()){
      if ( abs (localOptimizationDistances[i] - randomSearchDistances[k]) < 0.01){
        randomSearchSolutionsFile << randomSearchDistances[k] << std::endl;
        k++;
      }
      else{
        randomSearchSolutionsFile << std::endl;
      }
    }
    else{
      randomSearchSolutionsFile << std::endl;
    }
    localOptimizationSolutionsFile << localOptimizationDistances[i] << std::endl;
    nSolutionsFile << i+1 << std::endl;
  }

  randomSearchSolutionsFile.close();
  localOptimizationSolutionsFile.close();
  nSolutionsFile.close();

  return 0;
}
