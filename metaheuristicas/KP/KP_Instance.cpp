#include "KP_Instance.hpp"
#include "KP_Problem.hpp"

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>

std::vector<KP::Object> KP::Instance::read_objects(
  std::ifstream      &file,
  unsigned int const &n
) {
  std::vector<KP::Object> objects;
  std::string             tmp;
  unsigned int            number,
                          profit,
                          weight,
                          isOptimal;
  for( unsigned int i = 0; i < n; i++ ) {
    file >> tmp;
    std::stringstream tmpStream( tmp );

    std::getline( tmpStream, tmp, ',' );
    number = atoi( tmp.c_str() );

    std::getline( tmpStream, tmp, ',' );
    profit = atoi( tmp.c_str() );

    std::getline( tmpStream, tmp, ',' );
    weight = atoi( tmp.c_str() );

    std::getline( tmpStream, tmp, '\n' );
    isOptimal = atoi( tmp.c_str() );

    KP::Object object( profit, weight );
    objects.push_back( object );
  }
  return objects;
}

KP::Instance::Instance( std::string const &fileName ) {
  std::ifstream file( fileName.c_str() );
  assert( file );

  std::string name;
  while( file >> name ) {
    std::string tmp;

    unsigned long long int n;
    file >> tmp >> n;

    unsigned long long int c;
    file >> tmp >> c;
    KP::Knacksack knacksack( c );

    unsigned long long int z;
    file >> tmp >> z;

    float t;
    file >> tmp >> t;

    std::vector<KP::Object> objects = read_objects( file, n );

    KP::Problem problem( knacksack, objects );
    _problems.push_back( problem );

    file >> tmp; /* Read "-----" (KP separator) */
  }
  file.close();
}

std::vector<KP::Problem> KP::Instance::problems() const {
  return _problems;
}

unsigned long long int KP::Instance::profit( KP::Solution const &solution ) const {
  unsigned long long int profit = 0;

  for( unsigned int i = 0; i < solution.objects().size(); i++ ) {
    if( solution.objects()[i] ) {
      profit += solution.problem().objects()[i].profit();
    }
  }

  return profit;
}
