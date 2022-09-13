//
//  player.cpp
//  roulette
//
//  Created by Tej Thambi on 8/13/22.
//

#include <stdio.h>
#include "bet.h"
#include "player.h"
#include "globals.h"
#include <iostream>
using namespace std;

void Player::bet() {
    //Getting information about the bet from the player
    int choice;
    double initialBet;
    char yesNo = 'y';
    do {
        cout << "What type of bet would you like to place?" << endl;
        cout << "\t" << "1. Even (1:1)" << endl;
        cout << "\t" << "2. Double (2:1)" << endl;
        cout << "\t" << "3. Straight Up (35:1)" << endl;
        cout << "\t" << "4. Split (17:1)" << endl;
        cout << "\t" << "5. Corner (8:1)" << endl;
        cout << "\t" << "6. Street or Trio (11:1)" << endl;
        cout << "\t" << "7. Double Street (5:1)" << endl;
        cout << "\t" << "8. Top Line (6:1)" << endl << endl;
        cin >> choice;
        cout << endl;
        while(choice < 1 || choice > 8) {
            cout << "Please enter a number 1 - 8." << endl;
            cin >> choice;
            cout << endl;
        }
        cout << "How much would you like to bet?" << endl;
        cin >> initialBet;
        cout << endl;
        while(initialBet <= 0 || initialBet > getBalance()) {
            cout << "Your current balance is " << getBalance() << "." << endl;
            cout << "Please enter an amount greater than 0 and less than your balance." << endl;
            cin >> initialBet;
            cout << endl;
        }
        
        //Placing the bet
        Bet* bet = createBet(choice, this, initialBet, mGame);
        bet->placeBet();
        
        //Calculating the user balance based off the bet
        double amount = bet->calculateMoney();
        cout << "Spinning..." << endl;
        cout << "The wheel has landed on " << bet->getWinner().num;
        if(bet->getWinner().color == 'r') {
            cout << " red!" << endl;
        }
        if(bet->getWinner().color == 'b') {
            cout << " black!" << endl;
        }
        if(bet->getWinner().color == 'g') {
            cout << " green!" << endl;
        }
        if(amount != 0) {
            cout << "You have won $" << amount << "!" << endl;
            setBalance(amount + getBalance());
            cout << "Your balance is now $" << getBalance() << endl;
        } else {
            cout << "You lost." << endl;
            setBalance(getBalance() - initialBet);
            cout << "Your balance is now $" << getBalance() << endl;
        }
        delete bet; //Deleting dynamically allocated bet object
        
        //In case player balance hits 0
        if(getBalance() <= 0) {
            char yn;
            cout << "It looks like you have run out of money in your balance. Would you like to deposit more? Enter y for yes or n for no." << endl;
            cin >> yn;
            while(!(yn == 'y' || yn == 'n')) {
                cout << "Please enter y for yes or n for no." << endl;
                cin >> yn;
                cout << endl;
            }
            if(yn == 'y') {
                double addBal;
                cout << "How much would you like to add to your balance?" << endl;
                cin >> addBal;
                cout << endl;
                while(addBal < 0) {
                    cout << "Please enter an amount greater than 0." << endl;
                    cin >> addBal;
                    cout << endl;
                }
                setBalance(addBal);
            } else if (yn == 'n') {
                break;
            }
        }
        
        //Play again option
        cout << "Would you like to play again? Enter y for yes or n for no." << endl;
        cin >> yesNo;
        cout << endl;
        while(!(yesNo == 'y' || yesNo == 'n')) {
            cout << "Please enter y for yes or n for no." << endl;
            cin >> yesNo;
            cout << endl;
        }
    } while(yesNo == 'y');
    
    return;
}
