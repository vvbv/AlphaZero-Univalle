#ifndef GAME_HPP_
#define GAME_HPP_

#include "board.hpp"
#include "state_game.hpp"
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

        Board board;
        int items_to_collect;
        int items_collected_by_human;
        int items_collected_by_pc;
        int minmax( Board board, bool pc_turn );
        enum Action { up_right, up_left, left_up, left_down, down_left, down_right, right_down, right_up };
        bool compare_minmax_game_elements( minmax_game_elements *a, minmax_game_elements *b );
        State_game max_move( State_game state, std::vector < State_game > previous_moves_x );
        State_game min_move( State_game state, std::vector < State_game > previous_moves_x );
        State_game get_pos_up_right( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_up_left( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_left_up( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_left_down( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_down_left( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_down_right( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_right_down( State_game state, int current_pos[2], bool is_max );
        State_game get_pos_right_up( State_game state, int current_pos[2], bool is_max );
        bool game_ended( State_game state );
        bool states_equals( State_game a, State_game b );

    public:

        Game();
        ~Game();
        void set_board( Board board );
        void set_items_to_collect( int items_quantity );
        Board get_board();
        void start_new_game( Board board );
        void start_new_game();

};

#endif