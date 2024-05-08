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
void Instance<Problem>::fullReview(Problem loaded_problem, bool display){
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
    if(display){
        std::cout << "------------------Full review--------------------" << std::endl;
        this->displayMachinesResult();
        this->clearInstance();
    }
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
void Instance<Problem>::dynamicProgramingTwoMachines(Problem loaded_problem, bool display, bool display_matrix){
    int one_machine_work_time = loaded_problem.workTime();
    int columns = floor(one_machine_work_time/2)+1;
    int rows = loaded_problem.getSize()+1; 
    std::vector<std::vector<int>> divide_matrix(rows, std::vector<int>(columns)); 
    std::vector<int> divided_tasks (int(loaded_problem.getSize()), 1);
    int counter = columns - 1;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(j == 0){
                divide_matrix[i][j] = 1;
            }
            else{
                divide_matrix[i][j] = 0;
            }
        }
    }

    for(int i = 1; i < rows; i++) {
        for(int j = 1; j < columns; j++) {
            if(divide_matrix[i-1][j] == 1 || ((j >= loaded_problem.getItem(i-1).getWorkTime()) 
            && divide_matrix[i-1][j-loaded_problem.getItem(i-1).getWorkTime()] == 1)){
                divide_matrix[i][j] = 1;
            }
        }
    }

    while(counter != 0){
        int taken_row = 0;
        while(divide_matrix[taken_row][counter] != 1){
            taken_row ++;
        }

        counter -= loaded_problem.getItem(taken_row-1).getWorkTime();
        divided_tasks[taken_row-1] = 0;
    
    }

    this->divideTasks(divided_tasks, loaded_problem); 

    if(display){   
        std::cout << "--------Dynamic programing (2 machines)----------" << std::endl;
        this->displayMachinesResult();
        this->clearInstance();
    }
    
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
}

template<class Problem>
int Instance<Problem>::factorial(int number) {
    int result = 1;

    if(number < 0) {
        std::cerr << "Error! Can't calculate factorial from negative number!" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(number > 0) {
        for(int i = 1; i <= number; i++) {
            result = result * i;
        }        
    }

    return result;
}

template<class Problem>
int Instance<Problem>::binomialCoefficient(int n, int k) {

    int numerator = this->factorial(n);
    int denumerator = this->factorial(k) * this->factorial(n-k);
    int result = numerator/denumerator;

    return result;
}

template<class Problem>
void Instance<Problem>::generateBinaryCombinations(int N, int K, std::vector<int>& combination, int index, std::vector<std::vector<int>>& combinations) {
    if (K == 0) {
        combinations.push_back(combination);
        return;
    }

    if (index >= N)
        return;

    combination[index] = 1;
    generateBinaryCombinations(N, K - 1, combination, index + 1, combinations);

    combination[index] = 0;
    generateBinaryCombinations(N, K, combination, index + 1, combinations);
}


template<class Problem>
void Instance<Problem>::algorithmWrongPTAS(Problem loaded_problem) { //jednak źle zrozumiałem XD
    loaded_problem.workTimeSort();
    int problem_amount = loaded_problem.getSize();
    int best_work_time = 0, current_work_time = 0, machine_number = 0;
    std::vector<int> best_combination(problem_amount, 0);

    int combinations_amount = this->binomialCoefficient(problem_amount, machines-1);

    std::vector<std::vector<int>> combinations;
    std::vector<int> start_combination(problem_amount, 0);

    generateBinaryCombinations(problem_amount, machines-1, start_combination, 0, combinations);

    if(int(combinations.size()) != combinations_amount){
        std::cerr << "Missmatch in generated combination amount!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    for(const auto& combination : combinations) {
        for(int i = 0; i < problem_amount; i++){
            this->problem_list[machine_number].pushBack(loaded_problem.getItem(i));
            this->problem_list[machine_number].listSizeIncrement();
            if(combination[i] == 1){
               machine_number++;
            }
        }

        current_work_time = this->workTime();
        if(best_work_time > current_work_time || best_work_time == 0){
            best_work_time = current_work_time;
            best_combination = combination;
        }
        this->clearInstance();

        machine_number = 0;
    }

    for(int i = 0; i < problem_amount; i++){
        this->problem_list[machine_number].pushBack(loaded_problem.getItem(i));
        this->problem_list[machine_number].listSizeIncrement();
        if(best_combination[i] == 1){
            machine_number++;
        }
    }
    std::cout << "---------PTAS algorithm (wrong methode)----------" << std::endl;
    this->displayMachinesResult();
    this->clearInstance();
}

template<class Problem>
void Instance<Problem>::algorithmPTAS(Problem loaded_problem){
    loaded_problem.workTimeSort();
    int problem_amount = loaded_problem.getSize(), first_divide = 0;

    //Choose PTAS parametr
    float divider = 0.5;
    first_divide = floor(problem_amount * divider);

    Problem first_divide_list;
    Problem second_divide_list;

    for(int j = 0; j < first_divide; j++){
        first_divide_list.pushBack(loaded_problem.getItem(j));
        first_divide_list.listSizeIncrement();
    }
    for(int k = 0; k < problem_amount - first_divide; k++){
        second_divide_list.pushBack(loaded_problem.getItem(k+first_divide));
        second_divide_list.listSizeIncrement();
    }

    this->fullReview(first_divide_list, false);
    this->LSAandLPTCore(second_divide_list);

    std::cout << "-----------------PTAS algorithm------------------" << std::endl;
    this->displayMachinesResult();
    this->clearInstance();
}


template<class Problem>
void Instance<Problem>::algorithmFPTAS(Problem loaded_problem){
    int problem_amount = loaded_problem.getSize();
    Problem helper = loaded_problem;

    //Chose FPTAS parametr
    int divider = 2;

    helper.divideElement(divider);

    this->dynamicProgramingTwoMachines(helper, false, false);

    for(size_t j = 0; j < this->machines; j++){
        for(size_t k = 0; k < this->problem_list[j].getSize(); k++){
            for(size_t n = 0; n < size_t(problem_amount); n++){
                if(loaded_problem.getItem(n).getId() == this->problem_list[j].getItem(k).getId()){
                    this->problem_list[j].getItem(k).setWorkTime(loaded_problem.getItem(n).getWorkTime());
                }
            }
        }
    }

    std::cout << "----------------FPTAS algorithm------------------" << std::endl;
    this->displayMachinesResult();
    this->clearInstance();
}

template<class Problem>
void Instance<Problem>::timeMeasure(std::function<void()> callback) {
    auto start = std::chrono::high_resolution_clock::now();

    callback();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Powyższy algorytm wykonywał się: " << duration.count() << "ms" 
              << std::endl << std::endl;
}

template class Instance<Problem<Item<int>>>;