//
//  substructure.hpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 05.09.22.
//

#ifndef substructure_hpp
#define substructure_hpp

#include <iostream>

//save important informations in struct for generating a substring
struct sub {
    //parameters of substring
    size_t start_pos;
    size_t end_pos;
    size_t len;
    
    //parenthesis count
    size_t open_p = 0;
    size_t close_p = 0;
    
    //substring for return
    char * sub;
};

//return size of p_in
size_t size(char const * p_in);

//returns substring starting at index i in p_in in dot-bracket-notation
char * sub_structure (char const * p_in, int i);

void test_sub();



#endif /* substructure_hpp */
