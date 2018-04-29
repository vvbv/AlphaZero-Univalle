#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <tuple>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include "math.hpp"
#include <iostream>

class Board{

    private:
        Math math;
        int boxes[6][6];
        int BOARD_SIDE_SIZE = 6;
        int HORSES_QUANTITY = 2;
        int ITEM_ID = 3;
        int HORSE_HUMAN_ID = 1;
        int HORSE_PC_ID = 2;
        int FREE_ID = 0;
        int items_quantity;
        std::vector < std::tuple < int, int > > get_list_pos_random( int number_elements );

    public:
        Board();
        ~Board();
        std::tuple < int, int > get_pos_horse_pc();
        std::tuple < int, int > get_pos_horse_human();
        std::vector < std::tuple < int, int > > get_pos_fruits();
        int generate_board( int items_quantity );
        int get_box_value( int pos[2] );
        int get_BOARD_SIDE_SIZE();
        void print_board();
        int get_item_id();
        int get_horse_human_id();
        int get_horse_pc_id();
        int get_free_id();
        int get_items_quantity();
};

#endif