//
//  sorting.cpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 05.09.22.
//

#include "sorting.hpp"

void sort_alpha(std::vector<std::string *> & vec) {
    //if vec is empty or just size 1 return bc it cant be sorted
    if (vec.size() == 0 || vec.size() == 1) {
        return;
    }
    
    //check empty vec
    for (int i = 0; i < vec.size();++i) {
        if (vec[i] == nullptr ||vec[i] == NULL) {
            std::cout << "nullpointer found! Can't sort, please enter a valid vector!" << std::endl;
            return;
        }
    }
    
    
    //check element with all elements behinds
    //swap smaller elements
    for (int i = 0; i < vec.size()-1; ++i) {
        for (int j = i+1; j < vec.size(); ++j) {
            if ((*vec[i]) > (*vec[j])) {
                swap(vec, i, j);
            }
        }
    }
}

//changes element at pos i with element at pos j in vector vec
void swap(std::vector<std::string *> & vec, size_t const i, size_t const j) {
    std::string * tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
}

//function for testing
//to_sort is vec to sort
//to check is vec for compare if it worked.
bool test_sort(std::vector<std::string *> & to_sort, std::vector<std::string *> & to_check) {
    sort_alpha(to_sort);
    
    //if size is not equal in both vectors
    //they cant be same
    if (to_sort.size() != to_check.size()) return false;
    
    //check empty vec
    for (int i = 0; i < to_sort.size();++i) {
        if (to_sort[i] == nullptr ||to_sort[i] == NULL) {
            //std::cout << "Nullpointer found! Can't sort, please enter a valid vector!" << std::endl;
            return false;
        }
    }
    
    //check empty vec
    for (int i = 0; i < to_check.size();++i) {
        if (to_check[i] == nullptr ||to_check[i] == NULL) {
            //std::cout << "Nullpointer found! Can't sort, please enter a valid vector!" << std::endl;
            return false;
        }
    }
    
    //check every element
    for (int i = 0; i < to_sort.size(); ++i) {
        if ((*to_sort[i]) != (*to_check[i])) return false;
    }
    return true;
}

void test_cases() {
    std::vector<std::string *> my_data;
    std::vector<std::string *> sol(5);
    
    my_data.resize(5);
    my_data[0] = new std::string("Zenzi");
    my_data[1] = new std::string("Hubert");
    my_data[2] = new std::string("Franziska");
    my_data[3] = new std::string("Anna mag Heidelbeeren");
    my_data[4] = new std::string("Anna mag Himbeeren");
    
    sol[0] = new std::string("Anna mag Heidelbeeren");
    sol[1] = new std::string("Anna mag Himbeeren");
    sol[2] = new std::string("Franziska");
    sol[3] = new std::string("Hubert");
    sol[4] = new std::string("Zenzi");
    
    std::cout << "Testing valid vector" << std::endl;
    std::cout << std::boolalpha << test_sort(my_data, sol) << std::endl << std::endl;
    
    std::vector<std::string *> check(4);
    
    check[0] = new std::string("Zebras sind schön.");
    check[1] = new std::string("Lamas sind eigenartig.");
    check[2] = new std::string("Hasen sind süß.");
    check[3] = new std::string("Kühe sind nicht lila.");
    
    sol.resize(4);
    
    sol[3] = new std::string("Zebras sind schön.");
    sol[2] = new std::string("Lamas sind eigenartig.");
    sol[0] = new std::string("Hasen sind süß.");
    sol[1] = new std::string("Kühe sind nicht lila.");
    
    std::cout << "Testing valid vector" << std::endl;
    std::cout << std::boolalpha << test_sort(check, sol) << std::endl << std::endl;
    
    check[0] = new std::string("Position 8");
    check[1] = new std::string("");
    check[2] = new std::string("Position am Berg");
    check[3] = new std::string("Kinder mögen Milka, oder doch eher Kinder?");
    
    sol[0] = new std::string("");
    sol[1] = new std::string("Kinder mögen Milka, oder doch eher Kinder?");
    sol[2] = new std::string("Position 8");
    sol[3] = new std::string("Position am Berg");
    
    std::cout << "Testing vector with empty position" << std::endl ;
    std::cout << std::boolalpha << test_sort(check, sol) << std::endl << std::endl;
    
    std::vector<std::string *> empty_v(5);
    
    std::cout << "Testing empty vec" << std::endl;
    std::cout << std::boolalpha << test_sort(empty_v, empty_v) << std::endl << std::endl;
    
}
