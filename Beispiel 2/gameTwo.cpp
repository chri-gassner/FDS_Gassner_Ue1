//
//  game.cpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on
//  03.09.22 22:04 - 23:06+
//  04.09.22 13:15 - 18:33 Uhr
//  Zeit:

#include "gameTwo.hpp"

//set true if using xcodes built in command line tool
bool const USING_XCODE = true;
//variable for setting time to wait between moves easy
size_t const WAIT_MS = 1500;

//returns an object player_t named username
gameTwo::player_t * gameTwo::create_player(string const & username) {
    //creating player object
    gameTwo::player_t * player = new gameTwo::player_t;
    //set username
    player->username = username;
    
    return player;
}

//starts the game
void gameTwo::start_game(string const & filename) {
    //create game
    gameTwo * current_game = new gameTwo;
    
    //ask where to take the settings from file or console
    if (filename == "none") {
        char choice = '0';
        current_game->set_from_file = false;
        //ask where to take the settings from file or console
        while (!(tolower(choice) == 'n' || tolower(choice) == 'y')) {
            std::cout << "Do you want to load your settings from a file? (y/n)" << std::endl;
            
            std::cin >> choice;
            check_console();
        }
        
        //set from file
        if (tolower(choice) == 'y') {
            current_game->set_from_file = true;
            std::cout << "Please, enter filename (example: settings.txt): ";
            string tmp;
            std::cin >> tmp;
            current_game->read_settings(tmp);
        }
        
        //set from console
        if (!current_game->set_from_file) {
            //set_from_console();
            //greet player and ask for username
            std::cout << "Welcome to the Game!" << std::endl;
            
            std::cout << "Do you want to play Singleplayer? (y/n)" << std::endl;
            std::cin >> choice;
            
            if (tolower(choice) == 'n') {
                current_game->singleplayer = false;
            }
            
            
            std::cout << "Please enter username for Player A: " << std::endl;
            
            string username = "";
            std::cin >> username;
            
            check_console();

            //create playerA
            current_game->playerA = create_player(username);
            
            if (!current_game->singleplayer) {
                //creater PlayerB
                std::cout << "Please enter username for Player B: " << std::endl;
                std::cin >> username;
                
                check_console();
                
                //check for different usernames
                if (username == current_game->playerA->username) {
                    std::cout << username << ", is already taken.. Please choose anoother!" << std::endl;
                    std::cout << "Please enter username for Player B: " << std::endl;
                    std::cin >> username;
                    check_console();
                }

                current_game->playerB = create_player(username);
            } else {
                current_game->playerB = current_game->computer;
            }
            
            choice = '0';
            
            //check who is starting
            while (!(tolower(choice) == 'n' || tolower(choice) == 'y')) {
                std::cout << current_game->playerA->username << ", do you wanna start? (y/n)" << std::endl;
                std::cin >> choice;
                
                check_console();
            }
            
            //set beginner
            if ('y' == tolower(choice)) {
                current_game->current_player = current_game->playerA;
            } else if ('n' == tolower(choice)) {
                current_game->current_player = current_game->playerB;
            }
            
            //ask for amount of heaps
            while ((*current_game->heaps).size() == 0) {
                std::cout << "How many heaps you want to play with? (3-20)" << std::endl;
                size_t tmp_num = 0;
                std::cin >> tmp_num;
                check_console();
                
                //if valid input set heaps
                if (tmp_num < 21 && tmp_num > 2) {
                    (*current_game->heaps).resize(tmp_num, 0);
                }
                
            }
            
            //ask for auto set
            std::cout << "Do you wanna auto set lenght (1-20) of each heap? (y/n)" << std::endl;
            std::cin >> choice;
            
            //set autoset
            if ('y' == tolower(choice)) {
                current_game->auto_set = true;
            }
            
            //if not autoset do
            if (!current_game->auto_set) {
                //asks player for size of each heap
                size_t len = 0;
                for (int i = 0; i < (*current_game->heaps).size(); ++i) {
                    std::cout << "Please enter the lenght (1-20) of Heap Nr. " << i+1 << ": ";
                    std::cin >> len;
                    std::cout << std::endl;
                    check_console();
                    //if invalid, repeat
                    if (!(len < 21 && len > 0)) {
                        --i;
                    } else {
                        //set lenght
                        (*current_game->heaps)[i] = len;
                    }
                }
            }
        }
    } else {
        //set from file
        if (!current_game->read_settings(filename)) return;
    }
    
    //autoset lenght of heaps random
    if (current_game->auto_set) {
        for (int i = 0; i < (*current_game->heaps).size(); ++i) {
            //autoset each lenght of each heap (random 3-20)
            (*current_game->heaps)[i] = get_random_number(1,20);
        }
    }
    
    //print settings
    current_game->print_settings();
    //wait (for reading settings)
    std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS+2000));
    
    //start game
    std::cout << "Lets start the Game!" << std::endl;
    
    while (!current_game->finish) {
        //clear console
        if (!USING_XCODE) {
            system("clear");
        } else {
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
        }
        //print current player
        current_game->print_current_player();
        
        //increase moves
        ++current_game->current_player->moves;
        
        //Print Heaps
        current_game->print_all_heaps();
        
        //get choice from current player
        current_game->get_choice();
        
        //evaluate
        current_game->evaluate_choice();
        
        //if no winner next players turn
        if (!current_game->finish) {
            current_game->next_player();
        }
        
        //wait for comfort reasons
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));

    }
    
    
    //print winner to console
    if (current_game->winner == current_game->playerA) {
        std::cout << std::endl << "Congrats, " << current_game->playerA->username << "  you have won!" << std::endl << "You took "
        << current_game->playerA->moves << " moves to win!" << std::endl;
    } else {
        std::cout << "Congrats, " << current_game->playerB->username << "  you have won!" << std::endl << "You took "
        << current_game->playerB->moves << " moves to win!" << std::endl;
    }
    
}

//print current player to the console
void gameTwo::print_current_player() const {
    std::cout << "Current Player: " << this->current_player->username << std::endl;
    
}

//prints a heap with "size_of_heap"
//if end_of_line is set to true it will also prints std::endl
void gameTwo::print_heap(size_t const size_of_heap, bool const end_of_line) const{
    for (size_t i = 0; i < size_of_heap; ++i) {
        std::cout << "*";
    }
    
    std::cout << " (" << size_of_heap << ")";
    
    if (end_of_line) {
        std::cout << std::endl;
    }
}

//asks current player for his choise
void gameTwo::get_choice() {
    if (this->current_player != this->computer) {
        int cur_choice = -1;
        
        //while for error handling
        while (cur_choice > (*this->heaps).size() || cur_choice < 1) {
            //ask for choice
            std::cout << "Please choose a heap: " << std::endl;
            std::cin >> cur_choice;
            check_console();
        }
        
        this->current_player->current_choice = cur_choice-1;
        
        int amount = 0;
        
        while (amount < 1 || amount > (*this->heaps)[this->current_player->current_choice]) {
            std::cout << "How many elements do you want to take? (1-" << (*this->heaps)[this->current_player->current_choice] << ") " << std::endl;
            
            std::cin >> amount;
            check_console();
        }
        
        this->current_player->amount_per_heap = amount;
    } else {
        this->make_move();
    }
    
}


//evalutes choice of current user
void gameTwo::evaluate_choice() {
    
    (*this->heaps)[this->current_player->current_choice] = (*this->heaps)[this->current_player->current_choice] - this->current_player->amount_per_heap;
    
    std::cout << this->current_player->username << " took " << this->current_player->amount_per_heap << " elements from Heap " << this->current_player->current_choice+1 <<"." << std::endl;
    
    if ((*this->heaps)[this->current_player->current_choice] == 0) {
        this->loser = this->current_player;
        this->next_player();
        this->winner = this->current_player;
        this->finish = true;
    }
    
}

//checks is "player" is winner or not
bool gameTwo::is_winner(player_t const * player) const{
    return (player == this->winner) ? true : false;
}

//sets player to next in row
void gameTwo::next_player() {
    if (this->current_player == this->playerA) {
        this->current_player = this->playerB;
    } else {
        this->current_player = this->playerA;
    }
}

//check is console is good otherwise reset and clear console
void gameTwo::check_console() {
    //check cin
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
    }
}


int  gameTwo::get_random_number(int const lower_bound, int const upper_bound) {
    int random{rand()};
    return (random % (upper_bound - lower_bound + 1)) + lower_bound;
}

//prints all heaps
void gameTwo::print_all_heaps() const{
    for (int i = 1; i <= (*this->heaps).size(); ++i) {
        std::cout  << "Heap " << std::setw(2) << i << ": ";
        this->print_heap((*this->heaps)[i-1]);
    }
    std::cout << std::endl;
}


bool gameTwo::read_settings(string const & filename) {
    if (!std::filesystem::exists(filename)) {
        std::cout << filename << " not found.." << std::endl;
        this->set_from_file = false;
        return false;
    }
    
    std::ifstream in(filename);
    
    if (!in.good()) {
        std::cout << "Sorry, something went wrong.." << std::endl << "Please restart and enter a valid filename!" << std::endl << std::endl;
        this->finish = true;
        in.close();
        return false;
    }
    
    //file:
    //#0 start_tag:start_tag
    //#1 usernameA:name
    //#2 usernameB:name
    //#3 autoset:true/false
    //#4 heapAmount:N
    //#5-#N size of each heaps increasing order eg heap1:10
    //#N+1 end_tag:end_tag
    std::string current;
    std::getline(in, current);
    
    if (current != "start_tag:start_tag") {
        std::cout << "Invalid file: " << filename << " , please restart with valid file!" << std::endl << std::endl;
        this->set_from_file = false;
        in.close();
        return false;
    }
    
    while (in.good()) {
        size_t pos_delimeter = current.find(":");
        std::string setting_name = current.substr(0,pos_delimeter);
        std::string setting_value = current.substr(pos_delimeter+1);
        
        if (setting_name == "usernameA") {
            this->playerA = this->create_player(setting_value);
        } else if (setting_name == "usernameB") {
            if (setting_value == "Computer") {
                this->singleplayer = true;
                this->playerB = this->computer;
            } else {
                this->playerB = this->create_player(setting_value);
                this->singleplayer = false;
            }
            
        } else if (setting_name == "autoset") {
            if (setting_value == "true") {
                this->auto_set = true;
            }
        } else if (setting_name == "heapAmount") {
            char const * tmp = setting_value.c_str();
            if (std::atoi(tmp) > 2 && std::atoi(tmp) < 21) {
                (*this->heaps).resize(std::atoi(tmp));
            } else {
                std::cout << "Error, invalid input: " << std::endl << setting_name << ":" << setting_value << std::endl << "value should be between 3 and 20 (incl)" << std::endl << "Please set Settings manually!" << std::endl << std::endl;
                this->set_from_file = false;
                return false;
            }
        } else if (setting_name.substr(0,4) == "heap") {
            //get heap pos
            int const pos = std::atoi(setting_name.substr(4).c_str())-1;
            //set value
            (*this->heaps)[pos] = std::atoi(setting_value.c_str());
        } else if (setting_name == "beginner") {
            if (this->playerA->username == setting_value) {
                this->current_player = this->playerA;
            } else {
                this->current_player = this->playerB;
            }
        } else if (setting_name == "end_tag") {
            this->filename = filename;
            std::cout << "Sucessfully loaded settings - from file: " << filename << std::endl;
            in.close();
        }
        
        //get next line
        std::getline(in, current);
        
    }
    
    if (in.is_open()) {
        std::cout << "Missing end_tag, please check your file.." << std::endl;
        std::cout << "IMPORTANT: Not sure if game settings are loaded well.." << std::endl;
        
        this->print_settings();
        
        char choice = '0';
        
        while (!(choice == tolower('y') || choice == tolower('n'))) {
            std::cout << "Do you want to use this settings? (y/n)" << std::endl;
            std::cin >> choice;
        }
        
        if (choice == tolower('n')) {
            std::cout << "Please restart" << std::endl;
            this->set_from_file = false;
            (*this->heaps).resize(0);
            
            delete this->playerA;
            delete this->playerB;
            
            this->playerA = nullptr;
            this->playerB = nullptr;
            this->current_player = nullptr;
            this->auto_set = false;
            return false;
        } else {
            this->set_from_file = true;
            this->filename = filename;
            return true;
        }
        
        
    }
    this->set_from_file = true;
    return true;
    
    
}

void gameTwo::print_settings() const {
    //print all settings again
    std::cout << std::endl << "Your settings: " << std::endl;
    
    if (this->set_from_file) {
        std::cout << std::setw(20) << std::left << "set from: " << this->filename << std::endl;
    } else {
        std::cout << std::setw(20) << std::left << "set from: " << "console" <<std::endl;
    }
    
    std::cout << std::setw(20) << std::left << "autoset: " << std::boolalpha << this->auto_set << std::endl;
    std::cout << std::setw(20) << std::left << "PlayerA: " << this->playerA->username << std::endl;
    std::cout << std::setw(20) << std::left << "PlayerB: " << this->playerB->username << std::endl;
    std::cout << std::setw(20) << std::left << "Beginner: " << this->current_player->username << std::endl;
    std::cout << std::setw(20) << std::left << "Amount of heaps:" << (*this->heaps).size() << std::endl << std::endl;
    this->print_all_heaps();
}

void gameTwo::make_move() {
    int big_indx = 0;
    for (int i = 1; i < (*this->heaps).size(); ++i) {
        if ((*this->heaps)[big_indx] < (*this->heaps)[i]) {
            big_indx = i;
        }
    }
    
    this->computer->current_choice = big_indx;
    
    if ((*this->heaps)[big_indx] == 1) {
        this->computer->amount_per_heap = (*this->heaps)[big_indx];
    } else {
        this->computer->amount_per_heap = (*this->heaps)[big_indx] - 1;
    }
    
    
    
}
