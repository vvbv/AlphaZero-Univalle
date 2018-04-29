#ifndef GAME_HPP_
#define GAME_HPP_

#include "board.hpp"
#include <tuple>

class Game{

    private:

        Board board;

    public:

        Game();
        ~Game();
        void set_board( Board board );
        Board get_board();
        int minmax( bool is_max, Board board, bool human_turn );
        /*
            std::tuple < int <= This's pos in x or row
                            , int <= This's pos in y or column
                                    , int <= This's the value what contains the matrix in that position.
                                            > 
        */
        std::tuple < int, int, int > get_pos_up_right( int pos[] );
        std::tuple < int, int, int > get_pos_up_left( int pos[] );
        std::tuple < int, int, int > get_pos_left_up( int pos[] );
        std::tuple < int, int, int > get_pos_left_down( int pos[] );
        std::tuple < int, int, int > get_pos_down_left( int pos[] );
        std::tuple < int, int, int > get_pos_down_right( int pos[] );
        std::tuple < int, int, int > get_pos_right_down( int pos[] );
        std::tuple < int, int, int > get_pos_right_up( int pos[] );

};

#endif