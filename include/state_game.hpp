#ifndef STATE_GAME_HPP_
#define STATE_GAME_HPP_

#include "board.hpp"
#include <string>

class State_game{

    public:
        State_game();
        ~State_game();
        int min_items_quantity;
        int max_items_quantity;
        int depth;
        Board board;
        bool invalid_move;
        int max_utility;
        int min_utility;

};

#endif