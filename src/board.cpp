#include "board.hpp"

Board::Board(){
    for( int i = 0; i < this->BOARD_SIDE_SIZE; i++ ){
        for( int j = 0; j < this->BOARD_SIDE_SIZE; j++ ){
            this->boxes[ i ][ j ] = this->FREE_ID;
        };
    };
};
Board::~Board(){};
std::tuple < int, int > Board::get_pos_horse_pc(){};
std::tuple < int, int > Board::get_pos_horse_human(){};
std::vector < std::tuple < int, int > > Board::get_pos_fruits(){};

int Board::generate_board( int fruit_quantity ){
    if( fruit_quantity % 2 == 0 ){
        return -1;
    }else{
        //std::cout << "Cantidad de items a recolectar: " << fruit_quantity << std::endl;
        std::vector < std::tuple < int, int > > pos_items = get_list_pos_random( ( fruit_quantity + this->HORSES_QUANTITY ) );
        for( int i = 0; i < ( pos_items.size() - 2 ); i++ ){
            //std::cout << " [ " << std::get< 0 >( pos_items[ i ] ) << " - " << std::get< 1 >( pos_items[ i ] ) << " ]" << std::endl;
            this->boxes[ std::get< 0 >( pos_items[ i ] ) ][ std::get< 1 >( pos_items[ i ] ) ] = this->ITEM_ID;
        }
        this->boxes[ std::get< 0 >( pos_items[ pos_items.size() - 2 ] ) ][ std::get< 1 >( pos_items[ pos_items.size() - 2 ] ) ] = this->HORSE_HUMAN_ID;
        this->boxes[ std::get< 0 >( pos_items[ pos_items.size() - 1 ] ) ][ std::get< 1 >( pos_items[ pos_items.size() - 1 ] ) ] = this->HORSE_PC_ID;
        return 0;
    }
};
std::vector < std::tuple < int, int > > Board::get_list_pos_random( int number_elements ){
    std::vector < std::tuple < int, int > > pos_items;
    while( pos_items.size() != number_elements ){
        int pos_row = this->math.generate_random_number( 0, ( this->BOARD_SIDE_SIZE - 1 ) );
        int pos_column = this->math.generate_random_number( 0, ( this->BOARD_SIDE_SIZE - 1 ) );
        std::tuple < int, int > tmp_pos = std::make_tuple( pos_row, pos_column );
        if ( std::find( pos_items.begin(), pos_items.end(), tmp_pos ) == pos_items.end() ){
            pos_items.push_back( tmp_pos );
        }
    }
    return pos_items;
};  

int Board::get_box_value( int pos[2] ){
    return this->boxes[pos[0]][pos[1]];
};

int Board::get_BOARD_SIDE_SIZE(){
    return this->BOARD_SIDE_SIZE;
};

void Board::print_board(){
    for( int i = 0; i < this->BOARD_SIDE_SIZE; i++ ){
        for( int j = 0; j < this->BOARD_SIDE_SIZE; j++ ){
            std::cout << this->boxes[ i ][ j ] << " ";
        };
        std::cout << std::endl;
    };
};

int Board::get_item_id(){ 
    return this->ITEM_ID; 
};

int Board::get_horse_human_id(){ 
    return this->HORSE_HUMAN_ID 
};

int Board::get_horse_pc_id(){ 
    return this->HORSE_PC_ID; 
};

int Board::get_free_id(){ 
    return this->FREE_ID; 
};