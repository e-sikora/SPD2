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

template<class Problem>
void Instance<Problem>::divideTasks(std::vector<int> tasks, Problem loaded_problem){
    int problem_amount = int(loaded_problem.getSize());

    for(int i = 0; i < problem_amount; i++){
        for(int j = 0; j < int(this->machines); j++){
            if(tasks[i] == j){
                this->problem_list[j].pushBack(loaded_problem.getItem(i));
                this->problem_list[j].listSizeIncrement();
            }
        }
    }

}

template<class Problem>
void Instance<Problem>::clearInstance(){
    for(size_t i = 0; i < this->machines; i++) {
        this->problem_list[i].mainListClear();
        this->problem_list[i].listSizeZero();
    }
}

template<class Problem>
void Instance<Problem>::displayMachinesResult(){
    std::cout << "Best task allocation beetwen avaliable machines is:" << std::endl;
    for(size_t i = 0; i < this->machines; i++){
        std::cout << "Machine " << i+1 << " got following tasks:" << std::endl;
        for(size_t j = 0; j < this->problem_list[i].getSize(); j++){
            std::cout << this->problem_list[i].getItem(int(j)).getId() << " ";
        
        }
        std::cout << std::endl;
    }

    std::cout << "Best work time in this order is: " << this->workTime() 
    << std::endl << std::endl;

}

template<class Problem>
void Instance<Problem>::fullReview(Problem loaded_problem){
    int problem_amount = int(loaded_problem.getSize()), counter = 0, best_work_time = 0, current_work_time = 0;

    std::vector<int> modulo(problem_amount, 0);
    std::vector<int> current_combination(problem_amount, 0);
    std::vector<int> best_combination(problem_amount, 0);

    for(int i = 0; i < problem_amount; i++) {
        modulo[i] = std::pow(loaded_problem.getMachines(), i+1);
    }

    for(int j = 0; j < std::pow(loaded_problem.getMachines(), problem_amount); j++) {
        for(int k = 0; k < problem_amount; k++) {
            if(counter%modulo[k] == 0 && current_combination[k] > 0) {
                current_combination[k+1]++;
                current_combination[k] = 0;
            }
        }
        
        this->divideTasks(current_combination, loaded_problem);
        current_work_time = this->workTime();
        if(best_work_time > current_work_time || best_work_time == 0){
            best_work_time = current_work_time;
            best_combination = current_combination;
        }

        this->clearInstance();

        counter++;
        current_combination[0]++;
    }

    this->clearInstance();
    this->divideTasks(best_combination, loaded_problem);
    std::cout << "------------------Full review--------------------" << std::endl;
    this->displayMachinesResult();
    this->clearInstance();
}

template<class Problem>
int Instance<Problem>::lessBurdenedMachine(){
    std::vector<int> current_work_time(machines, 0);
    int machine_number = 0, min_work_amount = problem_list[0].workTime();

    for(size_t i = 0; i < machines; i++){
        current_work_time[i] = problem_list[i].workTime();

        if(current_work_time[i] < min_work_amount) {
            machine_number = int(i);
            min_work_amount = current_work_time[i];
        }
    }

    return machine_number;
}

template<class Problem>
void Instance<Problem>::LSAandLPTCore(Problem loaded_problem){
    size_t problem_amount = loaded_problem.getSize();
    int less_burdened;


    for(size_t i = 0; i < problem_amount; i++){
        less_burdened = this->lessBurdenedMachine();
        this->problem_list[less_burdened].pushBack(loaded_problem.getItem(i));
        this->problem_list[less_burdened].listSizeIncrement();
    }
}

template<class Problem>
void Instance<Problem>::LSA(Problem loaded_problem){
    LSAandLPTCore(loaded_problem);

    std::cout << "------------------LSA algorithm------------------" << std::endl;
    this->displayMachinesResult();
    this->clearInstance();
}

template<class Problem>
void Instance<Problem>::LPT(Problem loaded_problem){
    loaded_problem.workTimeSort();
    LSAandLPTCore(loaded_problem);

    std::cout << "------------------LPT algorithm------------------" << std::endl;
    this->displayMachinesResult();
    this->clearInstance();
}

template<class Problem>
void Instance<Problem>::dynamicProgramingTwoMachines(Problem loaded_problem, bool display_matrix){
    int one_machine_work_time = loaded_problem.workTime();
    int columns = floor(one_machine_work_time/2)+1;
    int rows = loaded_problem.getSize()+1; 
    int last_row_with_one = rows;
    std::vector<std::vector<int>> divide_matrix(rows, std::vector<int>(columns)); 
    std::vector<int> divided_tasks (int(loaded_problem.getSize()), machines);
    bool first_iteration = true;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(j == 0)
                divide_matrix[i][j] = 1;
            else
                divide_matrix[i][j] = 0;
            
        }
    }

    // for(int i = 0; i < rows; i++) {
    //     std::cout << "|";
    //     for(int j = 0; j < columns; j++) {
    //         std::cout << divide_matrix[i][j] << "|";
            
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    for(int i = 1; i < rows; i++) {
        for(int j = 1; j < columns; j++) {
            if(divide_matrix[i-1][j]||((j >= loaded_problem.getItem(i-1).getWorkTime()) 
            && divide_matrix[i-1][j-loaded_problem.getItem(i-1).getWorkTime()] == 1)){
                divide_matrix[i][j] = 1;
            }
            
        }
    }

    for(int j = columns-1; j >= 1; j--) {
        if(first_iteration){
            for(int i = 1; i < rows; i++) {
                if(divide_matrix[i][j] == 1){
                    divided_tasks[i-1] = 0;
                    last_row_with_one = i;
                    first_iteration = false;
                    break;
                }
            }
        }

        else{
            for(int i = 1; i < rows; i++) {
                if(divide_matrix[i][j] == 1 && last_row_with_one > i){
                    divided_tasks[i-1] = 0;
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < divided_tasks.size(); ++i) {
        if(divided_tasks[i] == int(machines)){
            divided_tasks[i] = 1;
        }
    }

    // for(size_t k = 0; k < divided_tasks.size(); k++){
    //     std::cout << divided_tasks[k] << " ";
    // }
    // std::cout << std::endl;


    this->divideTasks(divided_tasks, loaded_problem);    
    std::cout << "--------Dynamic programing (2 machines)----------" << std::endl;
    this->displayMachinesResult();
    
    if(display_matrix) {
        std::cout << "Resul matrix created during picking task for first machine:" << std::endl;
        for(int i = 0; i < rows; i++) {
            std::cout << "|";
            for(int j = 0; j < columns; j++) {
                std::cout << divide_matrix[i][j] << "|";
                
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    this->clearInstance();

}

template class Instance<Problem<Item<int>>>;