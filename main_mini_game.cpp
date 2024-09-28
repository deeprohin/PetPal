#include "mini_game.h"
int main(){
    mini_game new_game;
    while(new_game.window_open()){
        new_game.poll_events();
        new_game.render();
    }
    return 0;
}