#include "board.hpp"

Board::Board(){};
Board::~Board(){};
std::tuple < int, int > Board::get_pos_horse_pc(){};
std::tuple < int, int > Board::get_pos_horse_human(){};
std::vector < std::tuple < int, int > > Board::get_pos_fruits(){};

int Board::generate_board( int fruit_quantity ){
    if( fruit_quantity % 2 == 0 ){
        return -1;
    }else{
        std::cout << "Cantidad de items a recolectar: " << fruit_quantity << std::endl;
        std::vector < std::tuple < int, int > > pos_items = get_list_pos_random( ( fruit_quantity + this->HORSES_QUANTITY ) );
        
        for( int i = 0; i < pos_items.size(); i++ ){
            std::cout << " [ " << std::get< 0 >( pos_items[ i ] ) << " - " << std::get< 1 >( pos_items[ i ] ) << "  ]" << std::endl;
        }
        
        return 0;
    }
};
std::vector < std::tuple < int, int > > Board::get_list_pos_random( int number_elements ){
    std::vector < std::tuple < int, int > > pos_items;
    while( pos_items.size() != number_elements ){
        int pos_x = this->math.generate_random_number( 0, ( this->BOARD_SIDE_SIZE - 1 ) );
        int pos_y = this->math.generate_random_number( 0, ( this->BOARD_SIDE_SIZE - 1 ) );
        std::tuple < int, int > tmp_pos = std::make_tuple( pos_x, pos_y );
        if ( std::find( pos_items.begin(), pos_items.end(), tmp_pos ) == pos_items.end() ){
            pos_items.push_back( tmp_pos );
        }
    }
    return pos_items;
};  