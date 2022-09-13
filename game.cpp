#include <stdio.h>
#include "game.h"
#include "player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;


void Game::play() {
    cout << "Welcome to Roulette!" << endl << endl;
    string name;
    cout << "What is your name?" << endl;
    cin >> name;
    cout << endl;
    double initialBal;
    cout << "How much would you like to deposit?" << endl;
    cin >> initialBal;
    cout << endl;
    while(initialBal < 0) {
        cout << "Please enter an amount greater than 0." << endl;
        cin >> initialBal;
        cout << endl;
    }
    Player* p1 = new Player(name, *this, initialBal);
    p1->bet();
    cout << "Thank you for playing Roulette!" << endl;
}

square Game::spin() { //"Spinning" the roulette wheel
    random_device r;
    int n;
    n = r() % 37; // Generating a random number as a random square
    return allSquares[n];
}


Game::Game() {
    
    allSquares[0].num = 0;
    allSquares[0].color = 'g';
    
    allSquares[1].num = 100;
    allSquares[1].color = 'g';
    
    allSquares[2].num = 1;
    allSquares[2].color = 'r';
    
    allSquares[3].num = 2;
    allSquares[3].color = 'b';
    
    allSquares[4].num = 3;
    allSquares[4].color = 'r';
    
    allSquares[5].num = 4;
    allSquares[5].color = 'b';
    
    allSquares[6].num = 5;
    allSquares[6].color = 'r';
    
    allSquares[7].num = 6;
    allSquares[7].color = 'b';
    
    allSquares[8].num = 7;
    allSquares[8].color = 'r';
    
    allSquares[9].num = 8;
    allSquares[9].color = 'b';
    
    allSquares[10].num = 9;
    allSquares[10].color = 'r';
    
    allSquares[11].num = 10;
    allSquares[11].color = 'b';
    
    allSquares[12].num = 11;
    allSquares[12].color = 'b';
    
    allSquares[13].num = 12;
    allSquares[13].color = 'r';
    
    allSquares[14].num = 13;
    allSquares[14].color = 'b';
    
    allSquares[15].num = 14;
    allSquares[15].color = 'r';
    
    allSquares[16].num = 15;
    allSquares[16].color = 'b';
    
    allSquares[17].num = 16;
    allSquares[17].color = 'r';
    
    allSquares[18].num = 17;
    allSquares[18].color = 'b';
    
    allSquares[19].num = 18;
    allSquares[19].color = 'r';
    
    allSquares[20].num = 19;
    allSquares[20].color = 'r';
    
    allSquares[21].num = 20;
    allSquares[21].color = 'b';
    
    allSquares[22].num = 21;
    allSquares[22].color = 'r';
    
    allSquares[23].num = 22;
    allSquares[23].color = 'b';
    
    allSquares[24].num = 23;
    allSquares[24].color = 'r';
    
    allSquares[25].num = 24;
    allSquares[25].color = 'b';
    
    allSquares[26].num = 25;
    allSquares[26].color = 'r';
    
    allSquares[27].num = 26;
    allSquares[27].color = 'b';
    
    allSquares[28].num = 27;
    allSquares[28].color = 'r';
    
    allSquares[29].num = 28;
    allSquares[29].color = 'b';
    
    allSquares[30].num = 29;
    allSquares[30].color = 'b';
    
    allSquares[31].num = 30;
    allSquares[31].color = 'r';
    
    allSquares[32].num = 31;
    allSquares[32].color = 'b';
    
    allSquares[33].num = 32;
    allSquares[33].color = 'r';
    
    allSquares[34].num = 33;
    allSquares[34].color = 'b';
    
    allSquares[35].num = 34;
    allSquares[35].color = 'r';
    
    allSquares[36].num = 35;
    allSquares[36].color = 'r';
    
    allSquares[37].num = 36;
    allSquares[37].color = 'r';
}
