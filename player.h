#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include "common.h"
#include "board.h"
#include <cstring>


using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board *board;
    Side side;
    
    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Move> get_possible_moves();
    Move *choose_random_move(vector<Move> moves);

    Move *choose_weighted_move(vector<Move> moves);

    int weights[8][8];

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

};

#endif
