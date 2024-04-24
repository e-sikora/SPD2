// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>

#include "instance.h"

using namespace std;


int main(int argc, char *argv[]) {
  if(argc!=2){
    std::cout << "Błędne wywołanie programu! Program kończy działanie!" << std::endl;
    exit(EXIT_FAILURE);
  }

  Problem<Item<int>> problem;
  problem.loadFromFile(argv[1]);

  Instance<Problem<Item<int>>> instance(problem.getMachines());

  // instance.LSA(problem);
  // instance.LPT(problem);
  instance.fullReview(problem, true);
  if(problem.getMachines()==2) {
  //  instance.dynamicProgramingTwoMachines(problem, true, true);
      instance.algorithmFPTAS(problem);
  }
  // instance.algorithmWrongPTAS(problem);
  //instance.algorithmPTAS(problem);
  

  return 0;
}
