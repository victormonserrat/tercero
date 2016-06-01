#include "KP_Instance.hpp"
#include "KP_Problem.hpp"
#include "KP_Solution.hpp"
#include "KP_LocalSearch.hpp"
#include "KP_FirstNeighExplorator.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main(int argc, char const *argv[]) {
  if (argc != 4){
    std::cout << "\E[31mUssage: ./KPFirst fileName numberOfProblemOfTheObject numberOfLocalOptimizationSolutions\e[0m" << std::endl;
    return -1;
  }
  srand(time(NULL));
  std::string fileName = argv[1];
  int nProblem = atoi(argv[2]);
  int nLocalOptimizationSolutions = atoi(argv[3]);
  int nRandomSearchSolutions = 10; /*se especifica en la práctica */

  std::vector<unsigned long long int> randomSearchProfits;
  std::vector<unsigned long long int> localOptimizationProfits;
  std::vector<unsigned int> tamLocalOptimizationVector;
  int bestProfitOfSolutions = 0;
  int nObjectsBestSolution = 0;
  int sumWeightObjectsBestSolution = 0;

  KP::Solution bestSolution;


  std::string fileNameWithoutExtension = fileName.substr(0, fileName.size()-4);
  std::string fileNameWithoutExtensionOutput =  "First_" + fileNameWithoutExtension + "-" +
                                                std::to_string(nProblem) + "-" +
                                                std::to_string(nLocalOptimizationSolutions) + "-";



  std::ofstream randomSearchSolutionsFile, localOptimizationSolutionsFile,
                nSolutionsFile, bestSolutionFile;

  KP::Instance instance(fileName.c_str());
  KP::Problem problem = instance.problems()[nProblem];

  for (unsigned int i = 0; i < nRandomSearchSolutions; i++) {
    KP::Solution solution(problem);
    KP::FirstNeighExplorator b(nLocalOptimizationSolutions);
    KP::LocalSearch l(b);
    l.search(solution);
    std::vector<unsigned long long int> localOptimizationProfitsAux = l.profits();

    for (unsigned int j = 0 ; j < localOptimizationProfitsAux.size() ; j ++){
      localOptimizationProfits.push_back(localOptimizationProfitsAux[j]);
      tamLocalOptimizationVector.push_back(localOptimizationProfitsAux.size());
    }
    tamLocalOptimizationVector.push_back(localOptimizationProfitsAux.size());
    localOptimizationProfits.push_back(instance.profit(solution)); /*meter el randomSearch solution en el localOptimization */
    randomSearchProfits.push_back(instance.profit(solution));
    if (instance.profit(solution) > bestProfitOfSolutions){
      bestSolution = solution;
    }
    std::cout << "\E[32mSolución " << i << ".\e[0m" << std::endl;
  }

  int k = 0;
  int aumento = 0;
  int m = 0;
  for (auto it = std::begin(localOptimizationProfits) ; it + randomSearchProfits.size() <= std::end(localOptimizationProfits); it += aumento ){
    aumento =  tamLocalOptimizationVector[k]+1;
    std::sort( it, it + aumento );
    if (randomSearchProfits[m] > randomSearchProfits[m+1]){
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
  bestSolutionFile.open((fileNameWithoutExtensionOutput + "bestSolution.txt").c_str(),
                          std::ios::trunc);

  k = 0;
  for (unsigned int i = 0 ; i < localOptimizationProfits.size() ; i ++){
    if (localOptimizationProfits[i] == randomSearchProfits[k]){
      randomSearchSolutionsFile << randomSearchProfits[k] << std::endl;
      k++;
    }
    else{
      randomSearchSolutionsFile << std::endl;
    }
    localOptimizationSolutionsFile << localOptimizationProfits[i] << std::endl;
    nSolutionsFile << i+1 << std::endl;
  }
  for (unsigned int i = 0 ; i < bestSolution.objects().size() ; i++){
    nObjectsBestSolution += bestSolution.problem().objects()[i].weight();
    if (bestSolution.objects()[i])
      sumWeightObjectsBestSolution ++;
  }

  bestSolutionFile << nObjectsBestSolution << " " << sumWeightObjectsBestSolution;

  randomSearchSolutionsFile.close();
  localOptimizationSolutionsFile.close();
  nSolutionsFile.close();
  bestSolutionFile.close();

  return 0;
}
