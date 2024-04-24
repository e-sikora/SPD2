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

void divideTasks(std::vector<int> tasks, Problem loaded_problem);

void clearInstance();

void displayMachinesResult();

void fullReview(Problem loaded_problem, bool display);

int lessBurdenedMachine();

void LSAandLPTCore(Problem loaded_problem);

void LSA(Problem loaded_problem);

void LPT(Problem loaded_problem);

void dynamicProgramingTwoMachines(Problem loaded_problem, bool display, bool display_matrix);

int factorial(int number);

int binomialCoefficient(int n, int k);

void generateBinaryCombinations(int N, int K, std::vector<int>& combination, int index, std::vector<std::vector<int>>& combinations);

void algorithmWrongPTAS(Problem loaded_problem);

void algorithmPTAS(Problem loaded_problem);

void algorithmFPTAS(Problem loaded_problem);
};