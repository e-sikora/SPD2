#pragma once 

#include <cmath>

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

void divideTasks(std::vector<int> tasks, Problem loaded_problem);

void clearInstance();

void displayMachinesResult();

void fullReview(Problem loaded_problem);
};