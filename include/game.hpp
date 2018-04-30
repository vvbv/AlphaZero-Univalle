#ifndef GAME_HPP_
#define GAME_HPP_

#include "board.hpp"
#include <tuple>

class Game{

    private:

        Board board;
        int items_to_collect;
        int items_collected_by_human;
        int items_collected_by_pc;
        int minmax( Board board, bool pc_turn );
        enum Action { up_right, up_left, left_up, left_down, down_left, down_right, right_down, right_up };

    public:

        Game();
        ~Game();
        void set_board( Board board );
        void set_items_to_collect( int items_quantity );
        Board get_board();
        
        /*
            std::tuple < int <= This's pos in x or row
                            , int <= This's pos in y or column
                                    , int <= This's the value what contains the matrix in that position.
                                            > 
        */
        std::tuple < int, int, int > get_pos_up_right( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_up_left( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_left_up( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_left_down( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_down_left( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_down_right( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_right_down( Board board, int pos[] );
        std::tuple < int, int, int > get_pos_right_up( Board board, int pos[] );
        void start_new_game( Board board );
        void start_new_game();

};

#endif