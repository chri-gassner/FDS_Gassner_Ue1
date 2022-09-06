//
//  game.hpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 03.09.22.
//

#ifndef gameOne_hpp
#define gameOne_hpp

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

using std::string;

class gameOne {
public:
    //struct for player
    struct player_t {
        string username;
        size_t moves = 0;
        char current_choice;
    };
    
    //player agaist computer
    player_t * player;
    
    //heaps of the game
    size_t heap_lhs = 0;
    size_t heap_rhs = 0;
    
    //winner of the game
    player_t * winner;
    
    //computer
    player_t * computer = create_player("Computer");
    
    //for evaluting end of the game
    bool finish = false;
    
    //current player
    player_t * current_player;
    
    
    //function to start the game
    void static start_game();
    

private:
    //returns pointer to a object from type player with "username" set
    player_t static * create_player(string const & username);
    
    //print current player to the console
    void print_current_player();
    
    //prints a heap with "size_of_heap"
    //if end_of_line is set to true it will also prints std::endl
    void print_heap(size_t const size_of_heap, bool const end_of_line = true);
    
    //asks current player for his choise
    void get_choice();
    
    //computer makes move
    void make_move();
    
    //evalutes choice of current user
    void evaluate_choice();
    
    //checks is "player" is winner or not
    bool is_winner(player_t const * player);
    
    //sets player to nexr in row
    void next_player();
    
    //check is console is good otherwise reset and clear console
    void static check_console();

    
    
    
    
};






#endif /* game_hpp */
