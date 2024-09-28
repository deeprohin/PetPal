#include "mini_game.h"
int main(){
     std::srand(static_cast<unsigned>(std::time(nullptr)));
    mini_game new_game;
    while(new_game.window_open()){
        new_game.update();
        new_game.render();
    }
    return 0;
}