#include "TSP_GRASP.hpp"
#include "TSP_Node.hpp"
#include "TSP_Instance.hpp"
#include "TSP_Problem.hpp"
#include "TSP_SolGenerator.hpp"
#include "TSP_LocalSearch.hpp"
#include "TSP_FirstNeighExplorator.hpp"

#include <algorithm>
#include <vector>
#include <limits>

/*GUARRO*/
#include <iostream>
/*GUARRO*/


#define LIMIT 200

TSP::GRASP::GRASP (TSP::Problem const &problem,
                  double const &nIt){

  double bestDistance;

  TSP::Instance instance;
  TSP::Node currentNode;
  TSP::Node bestNode;
  int bestOrder;
  std::vector<unsigned int> order;
  std::vector<double> distances;
  std::vector<TSP::Node> nodes = problem.nodes();
  unsigned int random = rand()%nodes.size();
  TSP::Solution solution;

  solution.problem(problem);



  order.push_back(random);
  currentNode = nodes[random];
  nodes.erase(nodes.begin()+random);

  while (order.size() != problem.nodes().size() ) {
    double bestDistance = std::numeric_limits<double>::infinity();
    int i;
    for (i = 0; i < nodes.size() ; i++) {
      double currentDistance =
      sqrt(
          pow(currentNode.x() - nodes[i].x(), 2)
          +
          pow(currentNode.y() - nodes[i].y(), 2)
      );

      std::cout << "(" << currentNode.x() << ", " << currentNode.y() << ") (" << nodes[i].x() << ", " << nodes[i].y() << ") = " << currentDistance << std::endl;

      if (currentDistance < bestDistance){
        bestDistance = currentDistance;
        bestOrder = i;
        bestNode = nodes[i];
      }
    }
    order.push_back (bestOrder);
    currentNode = bestNode;
    nodes.erase (nodes.begin()+bestOrder);
    //std::cout << "BORRO EL NODO (" << (nodes.begin()+bestOrder).x() << ", " << (nodes.begin()+bestOrder).y() << ")\n";
    distances.push_back(bestDistance);
    std::cout << "BEST: " << bestDistance << std::endl;
    std::cout << "Distances: " << distances.size() << std::endl;

  }

  distances.push_back (
    sqrt(
      pow(currentNode.x() - problem.nodes()[random].x(), 2)
      +
      pow(currentNode.y() - problem.nodes()[random].y(), 2)
  ));

  solution.order(order);
  solution.distances(distances);





  TSP::FirstNeighExplorator firstNeighExplorator (LIMIT);
  TSP::LocalSearch localSearch (firstNeighExplorator);
  double bestSolutiondistance = instance.distance(solution);
  _solution = solution;

  /*GUARRO*/
  std::cout << "bestSolutiondistance: " << bestSolutiondistance << std::endl;
  /*GUARRO*/
  for (size_t i = 0; i < nIt ; i++) {
    TSP::Solution currentSolution = localSearch.search(solution);
    double currentSolutiondistance = instance.distance(currentSolution);
    if (currentSolutiondistance < bestSolutiondistance ){
      _solution = currentSolution;
      bestSolutiondistance = currentSolutiondistance;
      /*GUARRO*/
      std::cout << bestSolutiondistance << std::endl;
      /*GUARRO*/
    }
    /*GUARRO*/
    else{
      std::cout << currentSolutiondistance << "-" << std::endl;
      fflush (stdout);
    }
    /*GUARRO*/
  }

  //std::cout << "\n\n\t\t\t\E[32mbestSolutiondistance: " << bestSolutiondistance << "\e[0m" << std::endl;
  //std::cout << std::endl;
  for (size_t i = 0; i < distances.size(); i++) {
    std::cout << distances[i] << std::endl;
  }
}
