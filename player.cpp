#include "player.h"
using namespace std;

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    board = new Board();

    this->side = side;
    cerr<<(side==BLACK)<<endl;

    /* initialize weights for board */
    int temp[8][8] = 
    {{20, -5, 2, 2, 2, 2, -5, 20},
     {-5, -10, 1, 1, 1, 1, -10, -5},
     {2, 1, 2, 2, 2, 2, 1, 2},
     {2, 1, 2, 0, 0, 2, 1, 2},
     {2, 1, 2, 0, 0, 2, 1, 2},
     {2, 1, 2, 2, 2, 2, 1, 2},
     {-5, -10, 1, 1, 1, 1, -10, -5},
     {20, -5, 2, 2, 2, 2, -5, 20}};
    memcpy(&weights, &temp, 64 * sizeof(int));
    /* 
     * Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
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
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    vector<Move> moves;
    Move *final_move;

    /**
     * Process opponent's move.
     */
    Side other = (this->side == BLACK) ? WHITE : BLACK;
    board->doMove(opponentsMove, other);

    /**
     * Make a random move.
     */

    /*if (board->hasMoves(side))
    {
        moves = get_possible_moves();
        final_move = choose_random_move(moves);
        board->doMove(final_move, this->side);
        return final_move;
    }
    return NULL;
    */

    /**
     * Make a move using heuristics
     */
    
    if (board->hasMoves(side))
    {
        moves = get_possible_moves();
        final_move = choose_weighted_move(moves);
        board->doMove(final_move, this->side);
        return final_move;
    }
    return NULL;
}

/**
 * @brief Finds a vector of all possible moves for the side specified.
 */
vector<Move> Player::get_possible_moves()
{
    vector<Move> moves;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move to_test(i, j);
            if (board->checkMove(&to_test, this->side))
            {
                moves.push_back(to_test);
            }
        }
    }

    return moves;
}

/**
 * @brief Chooses a random move from a vector of moves.
 */
Move *Player::choose_random_move(vector<Move> moves)
{
    srand(time(NULL));
    int len = moves.size();
    int move_index = rand() % len;
    Move temp = moves[move_index];
    Move *move = new Move(temp.getX(), temp.getY());
    return move;
}

/**
 * @brief Chooses a weighted move from a vector of moves (heuristics).
 */
Move *Player::choose_weighted_move(vector<Move> moves)
{
    Move max_move = moves[0];
    int score, max_score;
    /* score all possible moves */
    for(unsigned int i = 0; i < moves.size(); i++) {
        /* copy board and make move */
        Board * copy = board->copy();
        copy->doMove(&moves[i], this->side);
        score = copy->score(this->side, this->weights);

        /* initialize max score as first move */
        if(i == 0){
            max_score = score;
        }
        else {
            if(score > max_score){
                max_score = score;
                max_move = moves[i];
            }
        }
        delete copy; 
    }
    return new Move(max_move.getX(), max_move.getY());
}

