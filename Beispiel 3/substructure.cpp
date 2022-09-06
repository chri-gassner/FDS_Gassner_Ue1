//
//  substructure.cpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 05.09.22.
// +9h

#include "substructure.hpp"

char * sub_structure (char const * p_in, int i) {
    //save size
    size_t p_in_size = size(p_in);
    
    //chek if index is valid
    if (i < 0 || i >= p_in_size) {
        return "invalid index! \n";
    }
    
    //check if string is empty
    if (p_in_size == 0) return "This string is empty \n";
    
    //char at index i
    char const at_i = p_in[i];
    
    //num for iterating through string without changing user_input
    int num = i;
    
    //struct for saving data for evaluation and returnment of substring
    sub * sol = new sub;
    
    //check where to start
    //check . starting
    if (at_i == '.') {
        //go left
        while (num > 0) {
            --num;
            if (p_in[num] == ')') {
                ++sol->close_p;
            } else if (p_in[num] == '(') {
                ++sol->open_p;
                if (sol->open_p == (sol->close_p+1)) {
                    break;
                }
            }
        }
        //save position found on left
        sol->start_pos = num;
        num = i; //restore num
        
        //check right
        while (num < p_in_size) {
            ++num;
            //check if ( starting
            if (p_in[num] == '(') {
                
                if (sol->open_p == 0) {
                    --num;
                    break;
                } else {
                    ++sol->open_p;
                }
            } else if (p_in[num] == ')') {
                ++sol->close_p;
                if (sol->open_p == sol->close_p) {
                    break;
                }
            }
        }
        //warn user paranthesis are not equal
        if (sol->open_p != sol->close_p) {
            std::cout << "missing parenthesis! \n";
        }
        //save end position
        sol->end_pos = num;
        num = i; //restore i
        //check ) starting
    } else if (at_i == ')') {
        sol->end_pos = num;
        ++sol->close_p;
        //only go left
        while (num > 0) {
            --num;
            //check )
            if (p_in[num] == ')') {
                ++sol->close_p;
                //check (
            } else if (p_in[num] == '(') {
                ++sol->open_p;
                if (sol->open_p == (sol->close_p)) {
                    break;
                }
            }
        }
        //warn user paranthesis are not equal
        if (sol->open_p != sol->close_p) {
            std::cout << "missing parenthesis! \n";
        }
        sol->start_pos = num;
        num = i;
        
    } else if (at_i == '(') {
        ++sol->open_p;
        sol->start_pos = num;
        while (num < p_in_size) {
            ++num;
            if (p_in[num] == '(') {
                ++sol->open_p;
            } else if (p_in[num] == ')') {
                ++sol->close_p;
                if (sol->open_p == sol->close_p) {
                    break;
                }
            }
        }
        //warn user paranthesis are not equal
        if (sol->open_p != sol->close_p) {
            std::cout << "missing parenthesis! \n";
        }
        sol->end_pos = num;
        num = i;
    } else {
        return (char *) "Invalid Character found! \n";
    }
    
    sol->sub = new char [(sol->end_pos-sol->start_pos)+2];
    
    sol->len = (sol->end_pos-sol->start_pos);
    
    
    for (size_t ji = 0; ji <= sol->len ; ++ji) {
        sol->sub[ji] = p_in[sol->start_pos];
        ++sol->start_pos;
    }
    
    return sol->sub;
}


size_t size(char const * p_in) {
    int i = 0;
    while (p_in[i] != '\0') {
        ++i;
    }
    return i;
}


void test_sub() {
    char * valid_c_string = (char *) "((((.(()(..(.(.....)..)))))))";
    char * empty_c_string = (char *) "";
    char * fail_c_string = (char *) ".((((((.)(..(.(.....)..))";
    char * invalid_c_string = (char *) "What do I do here?";
    
    //test invalid index
    std::cout << "Testing invalid index.. OUTPUT: " << sub_structure(valid_c_string, -1) << std::endl;
    
    //test valid string at pos 4 (= '.') should return (.(()(..(.(.....)..))))
    std::cout << "Testing valid string with valid index on '.'" << std::endl;
    std::cout << "Output should be: (.(()(..(.(.....)..))))" << std::endl;
    std::cout << "Output is: " << sub_structure(valid_c_string, 4) << std::endl;
    
    std::string sol = sub_structure(valid_c_string, 4);
    
    if (sol == "(.(()(..(.(.....)..))))") {
        std::cout << "Output Matches" << std::endl << std::endl;
    } else {
        std::cout << "Output NOT Matches" << std::endl << std::endl;
    }
    
    //test valid string with valid position on opening parenthesis
    std::cout << "Testing valid string with valid index on '('" << std::endl;
    std::cout << "Output should be: ()" << std::endl;
    std::cout << "Output is: " << sub_structure(valid_c_string, 6) << std::endl;
    
    sol = sub_structure(valid_c_string, 6);
    
    if (sol == "()") {
        std::cout << "Output Matches" << std::endl << std::endl;
    } else {
        std::cout << "Output NOT Matches" << std::endl << std::endl;
    }
    
    //test valid string with valid position on closing parenthesis
    std::cout << "Testing valid string with valid index on ')'" << std::endl;
    std::cout << "Output should be: (.(.....)..)" << std::endl;
    std::cout << "Output is: " << sub_structure(valid_c_string, 22) << std::endl;
    
    sol = sub_structure(valid_c_string, 22);
    
    if (sol == "(.(.....)..)") {
        std::cout << "Output Matches" << std::endl << std::endl;
    } else {
        std::cout << "Output NOT Matches" << std::endl << std::endl;
    }
    
    //test empty string with non-valid position
    std::cout << "Testing empty string with non-valid index" << std::endl;
    std::cout << "Output should be: invalid index!" << std::endl;
    std::cout << "Output is: " << sub_structure(empty_c_string, 22) << std::endl;
    
    sol = sub_structure(empty_c_string, 22);
    
    if (sol == "invalid index! \n") {
        std::cout << "Output Matches" << std::endl << std::endl;
    } else {
        std::cout << "Output NOT Matches" << std::endl << std::endl;
    }
    
    //test string with non-valid text and valid index
    std::cout << "Testing non-valid string with valid index" << std::endl;
    std::cout << "Output should be: Invalid Character found!" << std::endl;
    std::cout << "Output is: " << sub_structure(invalid_c_string, 5) << std::endl;
    
    sol = sub_structure(invalid_c_string, 5);
    
    if (sol == "Invalid Character found! \n") {
        std::cout << "Output Matches" << std::endl << std::endl;
    } else {
        std::cout << "Output NOT Matches" << std::endl << std::endl;
    }
    
    //test string with non-valid structure and valid index
    std::cout << "Testing non-valid structure with valid index" << std::endl;
    std::cout << "Output should be: missing parenthesis! \n(((((.)(..(.(.....)..))\nmissing parenthesis!" << std::endl;
    std::cout << "Output is: " << sub_structure(fail_c_string, 2) << std::endl;
    
    sol = sub_structure(fail_c_string, 2);
    
    if (sol == "(((((.)(..(.(.....)..))") {
        std::cout << "Output Matches" << std::endl << std::endl;
    } else {
        std::cout << "Output NOT Matches" << std::endl << std::endl;
    }
    
}
