#ifndef GAME_HPP_
#define GAME_HPP_

#include "board.hpp"
#include <tuple>



class Game{

    private:

        struct minmax_game_elements {
            int pos_max_row;
            int pos_max_column;
            int pos_min_row;
            int pos_min_column;
            int min_items_quantity;
            int max_items_quantity;
            int depth;
            Board board;
        };

        struct index_in_non_dynamic_expansions{
            int index;
        };

        struct state_game {
            int min_items_quantity;
            int max_items_quantity;
            int depth;
            Board board;
            bool invalid_move;
        };

        Board board;
        int items_to_collect;
        int items_collected_by_human;
        int items_collected_by_pc;
        int minmax( Board board, bool pc_turn );
        enum Action { up_right, up_left, left_up, left_down, down_left, down_right, right_down, right_up };
        bool compare_minmax_game_elements( minmax_game_elements *a, minmax_game_elements *b );
        state_game max_move( state_game state, std::vector < state_game > previous_moves );
        state_game min_move( state_game state, std::vector < state_game > previous_moves );
        bool game_ended( state_game state );
        

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
        state_game get_pos_up_right( state_game, int current_pos[], bool is_max );
        state_game get_pos_up_left( state_game, int current_pos[], bool is_max );
        state_game get_pos_left_up( state_game, int current_pos[], bool is_max );
        state_game get_pos_left_down( state_game, int current_pos[], bool is_max );
        state_game get_pos_down_left( state_game, int current_pos[], bool is_max );
        state_game> get_pos_down_right( state_game, int current_pos[], bool is_max );
        state_game get_pos_right_down( state_game, int current_pos[], bool is_max );
        state_game get_pos_right_up( state_game, int current_pos[], bool is_max );

        void start_new_game( Board board );
        void start_new_game();

};

#endif