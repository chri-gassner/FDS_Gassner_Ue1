//
//  main.cpp
//  FDS_Gassner_Ue1
//
//  Created by Christoph Gassner on 03.09.22.
//

#include "../Beispiel 1/gameOne.hpp"
#include "../Beispiel 2/gameTwo.hpp"
#include "../Beispiel 3/substructure.hpp"
#include "../Beispiel 4/sorting.hpp"

//fucntions for testing found under main
void test_gameOne();
void test_gameTwo();

int main() {
    //test_gameTwo();
    //test_gameTwo();
    //test_sub();
    test_cases();
    return 0;
}



int main1(int argc, const char * argv[]) {
    //set random seed for get_random_number()
    srand((int)time(0));
    //game::start_game();
    //gameOne::start_game();
    //gameTwo::start_game();
    //game2::start_game("config.txt");
    //game2::start_game("config2.txt");
    
    char * c_string = (char *) "((((.(()(..(.(.....)..)))))))";
    char * empty_c_string = (char *) "";
    char * invalid_c_string = (char *) ".((.)(..(.(.....)..)))))))";
    
    std::cout << sub_structure(invalid_c_string, -1);
    
    
    std::vector<std::string *> my_data;
    my_data.resize(5);
    my_data[0] = new std::string("Zenzi");
    my_data[1] = new std::string("Hubert");
    my_data[2] = new std::string("Franziska");
    my_data[3] = new std::string("Anna mag Heidelbeeren");
    my_data[4] = new std::string("Anna mag Himbeeren");
    
    
    std::cout <<"My Data: before sorting" << std::endl;
    for (int i = 0; i < my_data.size(); ++i) {
        std::cout << (*my_data[i]) << std::endl;
    }
    
    sort_alpha(my_data);
    std::cout << "My Data: after sorting" << std::endl;
    
    for (int i = 0; i < my_data.size(); ++i) {
        std::cout << (*my_data[i]) << std::endl;
    }
    
    std::vector<std::string *> check(4);
    std::vector<std::string *> sol(4);
    
    check[0] = new std::string("Zebras sind schön.");
    check[1] = new std::string("Lamas sind eigenartig.");
    check[2] = new std::string("Hasen sind süß.");
    check[3] = new std::string("Kühe sind nicht lila.");
    
    sol[3] = new std::string("Zebras sind schön.");
    sol[2] = new std::string("Lamas sind eigenartig.");
    sol[0] = new std::string("Hasen sind süß.");
    sol[1] = new std::string("Kühe sind nicht lila.");
    
    
    std::cout << std::boolalpha << test_sort(check, sol) << std::endl;
    
    return 0;
}

void test_gameOne() {
    //testing game
    gameOne::start_game();
}

void test_gameTwo() {
    
    //file not existing
    gameTwo::start_game("not_found.txt");
    
    //valid file
    gameTwo::start_game("config.txt");
    
    //valid file
    gameTwo::start_game("config2.txt");
    
    //invalid empty file
    gameTwo::start_game("settings.conf");
    
    //file with fail inside
    gameTwo::start_game("config1.txt");
    
    //load settings from console (file or manually)
    gameTwo::start_game();

}


