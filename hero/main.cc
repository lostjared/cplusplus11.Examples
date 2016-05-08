#include"hero.hpp"
#include<iostream>


int main(int argc, char **argv) {
    
    
    
    game::Hero hero(0, 0);
    
    std::cout << "Hero starting position: " << hero.toString() << "\n";

    hero.move(game::DIRECTION_RIGHT);
    
    std::cout << "Hero Position after moving right: " << hero.toString() << "\n";
    
    hero.move(game::DIRECTION_DOWN);
    
    std::cout << "New Hero Position after moving down: " << hero.toString() << "\n";
    
    return 0;
}