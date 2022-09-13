#include <stdio.h>
#include "bet.h"
#include "game.h"
#include <iostream>
#include <string>

using namespace std;

Bet::Bet(Player* player, Game& game) : mPlayer(player), mGame(game) {
    winner = mGame.spin();
}

//Derived classes of bet for each type of roulette bet

//============================================================
// Even
//============================================================

class Even: public Bet {
public:
    Even(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(1);
        //Initializing list of possible bets
        types[0] = "First Half";
        types[1] = "Second Half";
        types[2] = "Even";
        types[3] = "Odd";
        types[4] = "Red";
        types[5] = "Black";
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    string types[6];
    int choice;
};

void Even::placeBet() {
    cout << "Which type of even bet would you like to make?" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "\t" << i+1 << ". " << types[i] << endl;
    }
    cin >> choice;
    cout << endl;
    //Input validation
    while(choice < 1 || choice > 6) {
        cout << "Please enter a number 1 - 6." << endl;
        cin >> choice;
        cout << endl;
    }
}
 
double Even::calculateMoney(){
    bool win = false;
    //Switch case statement based on which bet the user selected, checks if the bet won
    switch(choice){
        case 1:
            if(getWinner().num <= 19) {
                win = true;
            }
            break;
        case 2:
            if(getWinner().num > 19) {
                win = true;
            }
            break;
        case 3:
            if(getWinner().num % 2 == 0) {
                win = true;
            }
            break;
        case 4:
            if(getWinner().num % 2 != 0) {
                win = true;
            }
            break;
        case 5:
            if(getWinner().color == 'r') {
                win = true;
            }
            break;
        case 6:
            if(getWinner().color == 'b') {
                win = true;
            }
            break;
        default:
            break;
    }
    //Return amount based on if the bet won or not
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Double
//============================================================

class Double: public Bet {
public:
    Double(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(2);
        //Initializing list of possible bets
        types[0] = "First Dozen";
        types[1] = "Second Dozen";
        types[2] = "Third Dozen";
        types[3] = "First Column";
        types[4] = "Second Column";
        types[5] = "Third Column";
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    string types[6];
    int choice;
};

void Double::placeBet() {
    cout << "Which type of double bet would you like to make?" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "\t" << i+1 << ". " << types[i] << endl;
    }
    cin >> choice;
    cout << endl;
    //Input validation
    while(choice < 1 || choice > 6) {
        cout << "Please enter a number 1 - 6." << endl;
        cin >> choice;
        cout << endl;
    }
}
 
double Double::calculateMoney(){
    bool win = false;
    //Another switch case statement to check if the bet won based off user input
    switch(choice){
        case 1:
            if(getWinner().num < 12) {
                win = true;
            }
            break;
        case 2:
            if(getWinner().num >= 12 && getWinner().num < 24) {
                win = true;
            }
            break;
        case 3:
            if(getWinner().num > 24) {
                win = true;
            }
            break;
        case 4:
            if(getWinner().num % 3 == 1) {
                win = true;
            }
            break;
        case 5:
            if(getWinner().num % 3 == 2) {
                win = true;
            }
            break;
        case 6:
            if(getWinner().num % 3 == 0) {
                win = true;
            }
            break;
        default:
            break;
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Straight Up
//============================================================

class StraightUp: public Bet {
public:
    StraightUp(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(35);
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    int betNum;
};

void StraightUp::placeBet() {
    cout << "Which number would you like to bet on? Enter a number 0 - 36 or 100" << endl;
    cin >> betNum;
    cout << endl;
    //Input validation
    while(betNum < 0 || (betNum > 36 && betNum < 100) || betNum > 100) {
        cout << "Please enter a number 1 - 6." << endl;
        cin >> betNum;
        cout << endl;
    }
}
 
double StraightUp::calculateMoney(){
    bool win = false;
    if(getWinner().num == betNum) { // If the square chosen matches the winning square, the bet won
        win = true;
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Split
//============================================================

class Split: public Bet {
    
public:
    Split(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(17);
        //Initializes all possible splits based on pattern in possible split bets of roulette
        int n = 1;
        for(int i = 0; i < 55; ) {
            if(n % 3 != 0) {
                splits[i][0] = n;
                splits[i][1] = n + 1;
                splits[i+1][0] = n;
                splits[i+1][1] = n + 3;
                i+=2;
                n++;
                continue;
            }
            if(n % 3 == 0) {
                splits[i][0] = n;
                splits[i][1] = n + 3;
                i++;
                n++;
                continue;
            }
        }
        splits[55][0] = 34;
        splits[55][1] = 35;
        splits[56][0] = 35;
        splits[56][1] = 36;
    }
    
    virtual void placeBet();
    virtual double calculateMoney();
private:
    int choice;
    int splits[57][2];
};

void Split::placeBet() {
    cout << "Which split would you like to bet on?" << endl;
    //Output all possible split options
    for(int i = 0; i < 57; i++) {
        cout << "\t" << i+1 << ". " << splits[i][0] << " and " << splits[i][1] << endl;
    }
    cin >> choice;
    cout << endl;
    //Input validation
    while(choice < 1 || choice > 57) {
        cout << "Please enter a number 1 - 57." << endl;
        cin >> choice;
        cout << endl;
    }
    choice--;
}
 
double Split::calculateMoney(){
    bool win = false;
    if(getWinner().num == splits[choice][0] || getWinner().num == splits[choice][1]){
        win = true;
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Corner
//============================================================

class Corner: public Bet {
    
public:
    Corner(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(8);
        //Initialize all possible corner bets based off patterns in corner bets of roulette
        int n = 1;
        for(int i = 0; i < 22; i++) {
            if(n == 33) {
                break;
            }
            if(n % 3 != 0) {
                corners[i][0] = n;
                corners[i][1] = n + 3;
                corners[i][2] = n + 1;
                corners[i][3] = n + 4;
                n++;
                continue;
            }
            if(n % 3 == 0) {
                n++;
                i--;
                continue;
            }
        }
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    int choice;
    int corners[22][4];
};

void Corner::placeBet() {
    cout << "Which corner would you like to bet on?" << endl;
    //Output all possible corner bets
    for(int i = 0; i < 22; i++) {
        cout << "\t" << i+1 << ". " << corners[i][0] << ", " << corners[i][1] << ", " << corners[i][2] << " and " <<
        corners[i][3] << endl;
    }
    cin >> choice;
    cout << endl;
    //Input validation
    while(choice < 1 || choice > 22) {
        cout << "Please enter a number 1 - 22." << endl;
        cin >> choice;
        cout << endl;
    }
    choice--;
}
 
double Corner::calculateMoney(){
    bool win = false;
    if(getWinner().num == corners[choice][0] || getWinner().num == corners[choice][1] || getWinner().num == corners[choice][2] || getWinner().num == corners[choice][3]){
        win = true;
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Street or Trio
//============================================================

class StreetTrio: public Bet {
  
public:
    StreetTrio(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(11);
        //Initialize all possible trio or street bets based off patterns in street bets in roulette
        int n = 1;
        for(int i = 0; i < 12; i++) {
            trios[i][0] = n;
            trios[i][1] = n + 1;
            trios[i][2] = n + 2;
            n+=3;
        }
        trios[12][0] = 0;
        trios[12][1] = 2;
        trios[12][2] = 3;
        
        trios[13][0] = 1;
        trios[13][1] = 2;
        trios[13][2] = 100;
        
        trios[14][0] = 0;
        trios[14][1] = 2;
        trios[14][2] = 100;
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    int choice;
    int trios[15][3];
};

void StreetTrio::placeBet() {
    cout << "Which trio or split would you like to bet on?" << endl;
    //Output all possible streets and trios
    cout << "Streets" << endl;
    cout << "=====" << endl;
    for(int i = 0; i < 12; i++) {
        cout << "\t" << i+1 << ". " << trios[i][0] << ", " << trios[i][1] << " and " <<  trios[i][2] << endl;
    }
    cout << "Trios" << endl;
    cout << "=====" << endl;
    for(int i = 12; i < 15; i++) {
        cout << "\t" << i+1 << ". " << trios[i][0] << ", " << trios[i][1] << " and " <<  trios[i][2] << endl;
    }
    cin >> choice;
    cout << endl;
    while(choice < 1 || choice > 15) {
        cout << "Please enter a number 1 - 15." << endl;
        cin >> choice;
        cout << endl;
    }
    choice--;
}
 
double StreetTrio::calculateMoney(){
    bool win = false;
    if(getWinner().num == trios[choice][0] || getWinner().num == trios[choice][1] || getWinner().num == trios[choice][2]){
        win = true;
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Double Street
//============================================================

class DoubleStreet: public Bet {
    
public:
    DoubleStreet(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(5);
        //Initialize all double streets
        int n = 1;
        for(int i = 0; i < 12; i++) {
            if(n == 34) {
                break;
            }
            doubleStreets[i][0] = n;
            doubleStreets[i][1] = n + 1;
            doubleStreets[i][2] = n + 2;
            doubleStreets[i][3] = n + 3;
            doubleStreets[i][4] = n + 4;
            doubleStreets[i][5] = n + 5;
            n+=3;
        }
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    int choice;
    int doubleStreets[11][6];
};

void DoubleStreet::placeBet() {
    cout << "Which double street would you like to bet on?" << endl;
    //Output all possible double streets
    for(int i = 0; i < 11; i++) {
        cout << "\t" << i+1 << ". " << doubleStreets[i][0] << ", " << doubleStreets[i][1] << ", "  << doubleStreets[i][2] << ", " << doubleStreets[i][3] << ", "  <<
        doubleStreets[i][4] << " and " <<  doubleStreets[i][5] << endl;
    }
    cin >> choice;
    cout << endl;
    while(choice < 1 || choice > 11) {
        cout << "Please enter a number 1 - 11." << endl;
        cin >> choice;
        cout << endl;
    }
    choice--;
}
 
double DoubleStreet::calculateMoney(){
    bool win = false;
    if(getWinner().num == doubleStreets[choice][0] || getWinner().num == doubleStreets[choice][1] || getWinner().num == doubleStreets[choice][2] || getWinner().num == doubleStreets[choice][3] || getWinner().num == doubleStreets[choice][4] || getWinner().num == doubleStreets[choice][5]){
        win = true;
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//============================================================
// Top Line
//============================================================

class TopLine: public Bet {
    
public:
    TopLine(Player* player, Game& game, double amount) : Bet(player, game) {
        setAmount(amount);
        setFactor(6);
        //Initialize all possible winning squares of a top line bet
        wins[0] = 0;
        wins[1] = 1;
        wins[2] = 2;
        wins[3] = 3;
        wins[4] = 100;
    }
    virtual void placeBet();
    virtual double calculateMoney();
private:
    int wins[5];
};

void TopLine::placeBet() {
    cout << "You have placed a Top Line bet on 0, 1, 2, 3, and 100" << endl;
}
 
double TopLine::calculateMoney(){
    bool win = false;
    for(int i = 0; i < 5; i++) {
        if(getWinner().num == wins[i]) {
            win = true;
        }
    }
    if(win) {
        return getFactor() * getMoney();
    } else {
        return 0;
    }
}

//Create Bet Function

Bet* createBet(int choice, Player* p, double amt, Game& game) {
    switch (choice) {
        case 1:
            return new Even(p, game, amt);
            break;
        case 2:
            return new Double(p, game, amt);
            break;
        case 3:
            return new StraightUp(p, game, amt);
            break;
        case 4:
            return new Split(p, game, amt);
            break;
        case 5:
            return new Corner(p, game, amt);
            break;
        case 6:
            return new StreetTrio(p, game, amt);
            break;
        case 7:
            return new DoubleStreet(p, game, amt);
            break;
        case 8:
            return new TopLine(p, game, amt);
            break;
        default:
            return nullptr;
    }
    return nullptr;
}
