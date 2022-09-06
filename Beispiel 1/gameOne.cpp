//
//  game.cpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on
//  03.09.22 18:21 -
//  03.09.22 21:08
//
//  Zeit: ca 2 - 2.5 h


#include "gameOne.hpp"

//set true if using xcodes built in command line tool
bool const USING_XCODE = true;
//variable for setting time to wait between moves easy
size_t const WAIT_MS = 2000;

//returns an object player_t named username
gameOne::player_t * gameOne::create_player(string const & username) {
    //creating player object
    gameOne::player_t * player = new gameOne::player_t;
    //set username
    player->username = username;
    
    return player;
}

void gameOne::start_game() {
    //create game
    gameOne * current_game = new gameOne;
    
    //greet player and ask for username
    std::cout << "Welcome to the Game!" << std::endl
    << "Please enter your username: " << std::endl;;
    
    string username = "";
    std::cin >> username;
    
    gameOne::check_console();
    
    //create player
    current_game->player = create_player(username);
    
    //check who is starting
    std::cout << current_game->player->username << ", do you wanna start? (y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    
    gameOne::check_console();
    
    //set beginner
    if ('y' == tolower(choice)) {
        current_game->current_player = current_game->player;
    } else if ('n' == tolower(choice)) {
        current_game->current_player = current_game->computer;
    } else {
        //Every Person who is not able to enter a simple 'y'/'n' is not allowed to beginn...
        std::cout << "Sorry, I didn't get that... Computer beginns!" << std::endl;
        current_game->current_player = current_game->computer;
    }
    
    //ask for size of heaps
    while (current_game->heap_lhs < 2 || current_game->heap_rhs < 2) {
        std::cout << "Please enter the size of heap on left-hand-side (min. 2): " << std::endl;
        std::cin >> current_game->heap_lhs;
        gameOne::gameOne::check_console();
        
        std::cout << "Please enter the size of heap on right-hand-side (min. 2): " << std::endl;
        std::cin >> current_game->heap_rhs;
        gameOne::check_console();
    }
    
    //print all settings again
    std::cout << std::endl << "Your settings: " << std::endl;
    std::cout << "Beginner: " << current_game->current_player->username << std::endl;
    std::cout << "Size of lhs heap: " << current_game->heap_lhs << std::endl
    << "Size of rhs heap: " << current_game->heap_rhs << std::endl << std::endl;
    
    //start game
    std::cout << "Lets start the Game!" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
    
    while (!current_game->finish) {
        //clear console
        if (!USING_XCODE) {
            system("clear");
        } else {
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
        }
        //print current player
        current_game->print_current_player();
        
        //increase moves
        ++current_game->current_player->moves;
        //print heap
        std::cout << "Heap on left-hand-side : ";
        current_game->print_heap(current_game->heap_lhs);
        
        //print heap
        std::cout << "Heap on right-hand-side : ";
        current_game->print_heap(current_game->heap_rhs);
        
        //check if playser is current player
        if (current_game->current_player == current_game->player) {
            current_game->get_choice();
        } else {
            current_game->make_move();
        }
        
        //evaluate
        current_game->evaluate_choice();
        //is winner?
        
        if (!current_game->is_winner(current_game->current_player)) {
            current_game->next_player();
        }
        
        std::cout << std::endl;
        
        //wait for comfort reasons
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));

        
    }
    
    if (current_game->winner == current_game->player) {
        std::cout << "Congrats, you have beaten the Computer!" << std::endl << "You took "
        << current_game->player->moves << " moves to win!" << std::endl;
    } else {
        std::cout << "You have lost against the Computer" << std::endl << "Computer took "
        << current_game->computer->moves << " moves to beat you!" << std::endl;
    }
    
    
}

//print current player to the console
void gameOne::print_current_player() {
    std::cout << "current user: " << this->current_player->username << std::endl;
    
}

//prints a heap with "size_of_heap"
//if end_of_line is set to true it will also prints std::endl
void gameOne::print_heap(size_t const size_of_heap, bool const end_of_line) {
    for (size_t i = 0; i < size_of_heap; ++i) {
        std::cout << "*";
    }
    
    if (end_of_line) {
        std::cout << std::endl;
    }
}

//asks current player for his choise
void gameOne::get_choice() {
    char cur_choice = '0';
    
    //while for error handling
    while (cur_choice != 'l' && cur_choice != 'r') {
        //ask for choice
        std::cout << "Please choose a heap (l/r): " << std::endl;
        std::cin >> cur_choice;
        gameOne::check_console();
        
        //evaluete choice
        if (cur_choice == 'l') {
            this->current_player->current_choice = 'l';
        } else if (cur_choice == 'r') {
            this->current_player->current_choice = 'r';
        }
    }
}


//evalutes choice of current user
void gameOne::evaluate_choice() {
    char const choice = this->current_player->current_choice;
    
    if (choice == 'l') {
        std::cout << this->current_player->username <<" took 1 item from the left hand side heap!" << std::endl;
        if (--this->heap_lhs == 0) {
            this->winner = this->current_player;
            this->finish = true;
        }
    } else if (choice == 'r') {
        std::cout << this->current_player->username <<  " took 1 item from the right hand side heap!" << std::endl;
        if (--this->heap_rhs == 0) {
            this->winner = this->current_player;
            this->finish = true;
        }
    }
    
}

//checks is "player" is winner or not
bool gameOne::is_winner(player_t const * player) {
    return (player == this->winner) ? true : false;
}

//sets player to next in row
void gameOne::next_player() {
    (this->current_player == this->player) ? this->current_player = this->computer : this->current_player = this->player;
}

//computer makes move
void gameOne::make_move() {
    
    //take 1 from the smaller heap
    //if equal take one from the rhs heap
    if ((this->heap_lhs < this->heap_rhs && this->heap_lhs != 2) || this->heap_rhs == 2) {
        this->current_player->current_choice = 'l';
    } else {
        this->current_player->current_choice = 'r';
    }
}

//check is console is good otherwise reset and clear console
void gameOne::check_console() {
    //check cin
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
    }

    
    
}
