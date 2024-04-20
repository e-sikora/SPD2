#include "problem.h"

template<class Item>
Problem<Item>::Problem() : list_size(0), machine_amount(0) {}

template<class Item>
size_t Problem<Item>::getSize() { return list_size; }

template<class Item>
size_t Problem<Item>::getMachines() { return machine_amount; }

template<class Item>
Item &Problem<Item>::getItem(size_t index) { return main_list[index]; }

template<class Item>
void Problem<Item>::loadFromFile(const std::string &file_name) {
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku: " << file_name << "!\n";
        exit(EXIT_FAILURE);
    }

    std::string temp;

    if (!std::getline(input_file, temp)) {
        std::cerr << "Plik " << file_name << " jest pusty!\n";
        exit(EXIT_FAILURE);
    } else {
        std::istringstream divide(temp);
        if(!(divide >> list_size >> machine_amount)) {
            std::cerr << "Dane zostały źle podzielone!\n";
            exit(EXIT_FAILURE);
        }
    }

    Item new_item;
    int counter = 0, o_time, w_time, i_time;
    while (std::getline(input_file, temp)) {
        counter++;
        std::istringstream divide(temp);
        if (divide >> o_time >> w_time >> i_time) {
            new_item = Item(counter, o_time, w_time, i_time);
        } else {
            std::cerr << "Dane zostały źle podzielone!\n";
            exit(EXIT_FAILURE);
        }
        main_list.push_back(new_item);
    }
    if (counter != list_size) {
        std::cerr << "Liczba wczytanych zadań nie zgadza się z zadeklarowaną ilośćią!\n";
        exit(EXIT_FAILURE);
    }
    input_file.close();
}

template<class Item>
int Problem<Item>::workTime() {
    int total_work_time = 0;

    for(int i = 0; i < this->list_size; i++){
        total_work_time += this->main_list[i].getWorkTime();
    }

    return total_work_time;
}

template<class Item>
void Problem<Item>::createOrClearFile(const std::string file_name) {
    std::ofstream output_file(file_name);

    if (output_file.is_open()) {
        output_file.close();
        output_file.open(file_name, std::ios::out | std::ios::trunc);
    } else {
        std::ofstream file(file_name);
        if (!file.is_open()) {
            std::cout << "Plik nie został poprawnie utworzony!\n";
            exit(EXIT_FAILURE);
        }
    }
    output_file.close();
}

template<class Item>
void Problem<Item>::displayResult(std::vector<Item> order, int time){
    std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
    for (Item &item: order) {
        std::cout << item.getId() << " ";
    }
    std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << time
              << std::endl;
}

template<class Item>
void Problem<Item>::eraseChosenVectorElement(std::vector<Item>& list, int serial){
    auto it = list.begin();
    while (it != list.end()) {
        if (it->getId() == serial) {
            list.erase(it);
            break;
        } else {
            ++it; 
        }
    }
}

template<class Item>
void Problem<Item>::timeMeasure(std::function<void()> callback) {
    auto start = std::chrono::high_resolution_clock::now();

    callback();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Powyższy algorytm wykonywał się: " << duration.count() << "ms" 
              << std::endl << std::endl;
}

template<class Item>
void Problem<Item>::workTimeSort() {
    std::sort(main_list.begin(), main_list.end(), [](const Item &a, const Item &b) { return a.compareByWorkTime(b); });
}


template class Problem<Item<int>>;