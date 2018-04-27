#import "board.hpp"

Board::Board(){};
Board::~Board(){};
std::tubple < int, int > Board::get_pos_horse_pc(){};
std::tubple < int, int > Board::get_pos_horse_human(){};
std::vector < std::tuple < int, int > > Board::get_pos_fruits(){};
void Board::generate_board( ){};
void Board::generate_board( int fruit_quantity ){
    if( fruit_quantity % 2 != 0 ){
        return -1;
    }else{

    }
};
std::vector < std::tuple < int, int > > Board::get_list_pos_random( int number_elements ){

};