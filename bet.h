#ifndef bet_h
#define bet_h

#include "globals.h"

struct square;
class Player;
class Game;

class Bet { // Bet base class
public:
    Bet(Player* player, Game& game);
    void setAmount(double amount) {mInitial = amount;}
    double getMoney() const {return mInitial;}
    void setFactor(int factor) {mFactor = factor;}
    int getFactor() const {return mFactor;}
    square getWinner() const {return winner;}
    virtual double calculateMoney() = 0; // calculates payout
    virtual void placeBet() = 0; // ask which specific bet to place
private:
    Player* mPlayer;
    Game& mGame;
    double mInitial;
    double mPayout;
    int mFactor;
    square winner;
};



Bet* createBet(int choice, Player* p, double amt, Game& game);

#endif /* bet_h */
