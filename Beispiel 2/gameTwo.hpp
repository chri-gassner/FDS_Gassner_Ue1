//
//  game.hpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 03.09.22.
//

#ifndef gameTwo_hpp
#define gameTwo_hpp

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include <stdlib.h>
#include <filesystem>

using std::string;

class gameTwo {
public:
    //function to start the game
    void static start_game(std::string const & filename = "none");
    

private:
    //struct for player
    struct player_t {
        string username;
        size_t moves = 0;
        int current_choice;
        int amount_per_heap;
    };
    
    string filename;
    
    //player agaist computer
    player_t * playerA;
    player_t * playerB;
    
    player_t * computer = this->create_player("Computer");
    
    //heaps of the game
    std::vector<size_t> * heaps = new std::vector<size_t>(0);
    
    //winner of the game
    player_t * winner;
    
    //winner of the game
    player_t * loser;
    
    //for evaluting end of the game
    bool finish = false;
    
    //set by file or console?
    bool set_from_file = false;
    
    //turn on/off console for settings
    bool console = false;
    
    //current player
    player_t * current_player;
    
    //autoset of lenght of each heap (3 - 20)
    bool auto_set = false;
    
    //for playing against computer
    bool singleplayer = true;
    
    //returns pointer to a object from type player with "username" set
    player_t static * create_player(string const & username);
    
    //print current player to the console
    void print_current_player() const;
    
    //prints a heap with "size_of_heap"
    //if end_of_line is set to true it will also prints std::endl
    void print_heap(size_t const size_of_heap, bool const end_of_line = true) const;
    
    //prints all heaps
    void print_all_heaps() const;
    
    //asks current player for his choise
    void get_choice();
    
    //evalutes choice of current user
    void evaluate_choice();
    
    //checks is "player" is winner or not
    bool is_winner(player_t const * player) const;
    
    //sets player to nexr in row
    void next_player();
    
    //check is console is good otherwise reset and clear console
    void static check_console();
    
    //reading settings from file
    bool read_settings(string const & filename);
    
    //returns random number
    int static get_random_number(int const lower_bound = 3, int const upper_bound = 20);
    
    //print settings
    void print_settings() const;
    
    void read_settings_cin();
    
    void ask_for_settings();
    
    void make_move();
    
};




#endif /* game_hpp */
