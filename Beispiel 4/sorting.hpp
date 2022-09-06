//
//  sorting.hpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 05.09.22.
//

#ifndef sorting_hpp
#define sorting_hpp

#include <vector>
#include <string>
#include <iostream>


//swaps i with j in vector
void swap(std::vector<std::string *> & vec, size_t const i, size_t const j);

//sorts vec from a-z
void sort_alpha(std::vector<std::string *> & vec);

//function for testing
bool test_sort(std::vector<std::string *> & to_sort, std::vector<std::string *> & to_check);
void test_cases();



#endif /* sorting_hpp */
