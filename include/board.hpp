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
        const int BOARD_SIDE_SIZE = 6;
        const int HORSES_QUANTITY = 2;
        std::vector < std::tuple < int, int > > get_list_pos_random( int number_elements );

    public:
        Board();
        ~Board();
        std::tuple < int, int > get_pos_horse_pc();
        std::tuple < int, int > get_pos_horse_human();
        std::vector < std::tuple < int, int > > get_pos_fruits();
        int generate_board( int fruit_quantity );

};

#endif