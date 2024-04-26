#pragma once

#include "problem.h"

/**
 * @brief Template class representing an instance of a problem.
 *
 * @tparam Problem Type of the problem.
 */
template <class Problem>
class Instance
{
private:
    size_t machines;
    std::vector<Problem> problem_list;

public:
    /**
     * @brief Constructor to create an Instance object.
     *
     * @param amount Number of instances to create.
     */
    Instance(int amount);
    /**
     * @brief Calculates the total work time of all machines.
     *
     * @return int Total work time.
     */
    int workTime();
    /**
     * @brief Gets the number of machines.
     *
     * @return int Number of machines.
     */
    int getMachines();
    /**
     * @brief Sets a problem instance for a specific machine.
     *
     * @param problem Problem instance to set.
     * @param indx Index of the machine.
     */
    void setMachine(const Problem problem, int indx);
    /**
     * @brief Divides tasks among the machines.
     *
     * @param tasks Vector of tasks.
     * @param loaded_problem Problem instance.
     */
    void divideTasks(std::vector<int> tasks, Problem loaded_problem);
    /**
     * @brief Clears all problem instances from the instance object.
     */
    void clearInstance();
    /**
     * @brief Displays results for each machine.
     */
    void displayMachinesResult();
    /**
     * @brief Conducts a full review of the problem.
     *
     * @param loaded_problem Problem instance.
     * @param display Boolean indicating whether to display the results.
     */
    void fullReview(Problem loaded_problem, bool display);
    /**
     * @brief Determines the least burdened machine.
     *
     * @return int Index of the least burdened machine.
     */
    int lessBurdenedMachine();
    /**
     * @brief Core function for both LSA and LPT algorithms.
     *
     * @param loaded_problem Problem instance.
     */
    void LSAandLPTCore(Problem loaded_problem);
    /**
     * @brief Implements the LSA (Longest Service Activity) algorithm.
     *
     * @param loaded_problem Problem instance.
     */
    void LSA(Problem loaded_problem);
    /**
     * @brief Implements the LPT (Longest Processing Time) algorithm.
     *
     * @param loaded_problem Problem instance.
     */
    void LPT(Problem loaded_problem);
    /**
     * @brief Implements dynamic programming for two machines.
     *
     * @param loaded_problem Problem instance.
     * @param display Boolean indicating whether to display the results.
     * @param display_matrix Boolean indicating whether to display the dynamic programming matrix.
     */
    void dynamicProgramingTwoMachines(Problem loaded_problem, bool display, bool display_matrix);
    /**
     * @brief Calculates the factorial of a number.
     *
     * @param number Number to calculate the factorial of.
     * @return int Factorial of the number.
     */
    int factorial(int number);

    /**
     * @brief Calculates the binomial coefficient.
     *
     * @param n Total number of items.
     * @param k Number of items to choose.
     * @return int Binomial coefficient.
     */
    int binomialCoefficient(int n, int k);
    /**
     * @brief Generates binary combinations.
     *
     * @param N Total number of items.
     * @param K Number of items to choose.
     * @param combination Current combination.
     * @param index Current index.
     * @param combinations Vector to store generated combinations.
     */
    void generateBinaryCombinations(int N, int K, std::vector<int> &combination, int index, std::vector<std::vector<int>> &combinations);
    /**
     * @brief Implements the wrong PTAS (Polynomial-Time Approximation Scheme) algorithm.
     *
     * @param loaded_problem Problem instance.
     */
    void algorithmWrongPTAS(Problem loaded_problem);
    /**
     * @brief Implements the PTAS (Polynomial-Time Approximation Scheme) algorithm.
     *
     * @param loaded_problem Problem instance.
     */
    void algorithmPTAS(Problem loaded_problem);
    /**
     * @brief Implements the FPTAS (Fully Polynomial-Time Approximation Scheme) algorithm.
     *
     * @param loaded_problem Problem instance.
     */
    void algorithmFPTAS(Problem loaded_problem);
};