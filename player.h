//
//  player.h
//  roulette
//
//  Created by Tej Thambi on 8/13/22.
//

#ifndef player_h
#define player_h

#include <string>
using namespace std;

struct square;

class Game;
class Bet;

class Player {
public:
    Player(string name, Game& game, double b) : mName(name), mGame(game), mBalance(b) {}
    void bet();
    void setBalance(double amount) {
        mBalance = amount;
    }
    double getBalance() {return mBalance;}
private:
    double mBalance;
    string mName;
    Game& mGame;
};

#endif /* player_h */
