#include"mini_game.h"

class UnitTesting{
    private:
        void miniGameTest(){
            mini_game game;
        if (game.window_open() && game.money_earned_end() == 0) {
            std::cout << "Passed" << std::endl;
        } else {
            std::cout << "Failed" << std::endl;
        }
        }
    public:
        void runTests(){
            miniGameTest();
        }
};