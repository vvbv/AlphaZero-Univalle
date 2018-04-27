#include "board.hpp"

Board::Board(){};
Board::~Board(){};
std::tuple < int, int > Board::get_pos_horse_pc(){};
std::tuple < int, int > Board::get_pos_horse_human(){};
std::vector < std::tuple < int, int > > Board::get_pos_fruits(){};
int Board::generate_board( ){};
int Board::generate_board( int fruit_quantity ){
    if( fruit_quantity % 2 == 0 ){
        return -1;
    }else{
        return 0;
    }
};
std::vector < std::tuple < int, int > > Board::get_list_pos_random( int number_elements ){

};