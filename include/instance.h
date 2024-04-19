#pragma once 

#include "problem.h"


template<class Problem>
class Instance {
private:
size_t machines;
std::vector<Problem> problem_list;


public:

Instance(int amount);

int workTime();

int getMachines();

void setMachine(const Problem problem, int indx);
};