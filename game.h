#ifndef game_h
#define game_h

#include "globals.h"

class Game {
public:
    Game();
    void play();
    square spin();
private:
    square allSquares[38];
};

#endif /* game_h */
