// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>

#include "instance.h"


int main(int argc, char *argv[]) {
  if(argc!=2){
    std::cout << "Błędne wywołanie programu! Program kończy działanie!" << std::endl;
    exit(EXIT_FAILURE);
  }

  Problem<Item<int>> problem;
  problem.loadFromFile(argv[1]);

  //std::cout << problem.getMachines() << std::endl;

  Instance<Problem<Item<int>>> instance(problem.getMachines());
 
  //std::cout << "jestem" << std::endl;
  //std::cout << instance.getMachines() << std::endl;

  //instance.setMachine(problem, 0);

  // int work_time = instance.workTime();
  // std::cout << work_time << std::endl << std::endl;

  instance.LSA(problem);
  instance.LPT(problem);
  instance.fullReview(problem);
  if(problem.getMachines()==2) {
    instance.dynamicProgramingTwoMachines(problem);
  }
  



  return 0;
}
