#include "instance.h"

template<class Problem>
Instance<Problem>::Instance(int amount) : machines(amount), problem_list(amount) {}

template<class Problem>
int Instance<Problem>::workTime(){
    std::vector<int> work_time(machines, 0);
    for(size_t i = 0; i < machines; i++) {
            for(size_t j = 0; j < problem_list[i].getSize(); j++) {
                work_time[i] += problem_list[i].getItem(j).getWorkTime();
            }   
        }

    int total_work_time = *std::max_element(work_time.begin(), work_time.end());

    return total_work_time;
}

template<class Problem>
int Instance<Problem>::getMachines(){
    return int(this->machines);
}

template<class Problem>
void Instance<Problem>::setMachine(const Problem problem, int indx){
    problem_list[indx] = problem;
}

template class Instance<Problem<Item<int>>>;