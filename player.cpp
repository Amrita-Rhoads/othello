#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "s". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side s) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     board = new Board();
     side = s;
     other = (side == BLACK) ? WHITE : BLACK;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     return heuristicMove(opponentsMove, msLeft);

}


Move *Player::simpleMove(Move *opponentsMove, int msLeft){
    // Update the board for the most recent move.
    board->doMove(opponentsMove, other);
    
    // If we can't move, return nullptr.
    if (!(board->hasMoves(side))){
        return nullptr;
    }
    
    Move * move = new Move(0,0); // TODO: Free this in destructor
    // Otherwise, move randomly.
    for (int i = 0; i < 8; i++) {
        move->setX(i);
        for (int j = 0; j < 8; j++) {
            move->setY(j);
            if (board->checkMove(move, side)){
                 board->doMove(move, side);
                 return move;
             }
        }
    }
    
    // This shouldn't ever happen!
    return nullptr;
}


Move *Player::heuristicMove(Move *opponentsMove, int msLeft){
    // Update the board for the most recent move.
    board->doMove(opponentsMove, other);
    
    // If we can't move, return nullptr.
    if (!(board->hasMoves(side))){
        return nullptr;
    }
    
    Move * move = new Move(0,0); // TODO: Free this in destructor
    int max_score = -65;
    
    // Iterate over valid moves, evaluate heuristic score of each,
    // and choose best.
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move dummy_move(i,j);
            // If move is valid check heuristic.
            if (board->checkMove(&dummy_move, side)){
                Board * dummy = board->copy();
                dummy->doMove(move, side);
                if (simpleHeuristic(dummy, side) >= max_score){
                    move->setX(i);
                    move->setY(j);
                    max_score = simpleHeuristic(dummy, side);
                }
                delete dummy;
             }
        }
    }
    
    // Record and return our move.
    board->doMove(move, side);
    return move;
}


int Player::simpleHeuristic(Board * board, Side s){
    int score = 0;
    int total = board->countBlack() + board->countWhite();
    
    // Difference in colors. Early game, one actually wants fewer disks.
    if ((s == BLACK && total > 40) || (s != BLACK && total < 40)){
        score = board->countBlack() - board->countWhite();
    }
    else {
        score = board->countWhite() - board->countBlack();
    }
    
    // Corners provide a significant boost.
    int corner_indicies[] = {0, 7};
    for (auto i : corner_indicies){
        for (auto j : corner_indicies){
            if (board->get(s, i, j)){
                score += 10;
            }
        }
    }
    
    
    
    return score;
    
}
