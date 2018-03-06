#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *simpleMove(Move *opponentsMove, int msLeft);
    Move *heuristicMove(Move *opponentsMove, int msLeft);
    int simpleHeuristic(Board * board, Side s);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Side side;
    Side other;
    Board * board;
};

#endif
