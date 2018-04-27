#ifndef BOARD_HPP_
#define BOARD_HPP_

#import <tuple>

class Board{

    private:
        int boxes[6][6];
        std::vector < std::tuple < int, int > > get_list_pos_random( int number_elements );
    public:
        Board();
        ~Board();
        std::tubple < int, int > get_pos_horse_pc();
        std::tubple < int, int > get_pos_horse_human();
        std::vector < std::tuple < int, int > > get_pos_fruits();
        void generate_board( );
        void generate_board( int fruit_quantity );

};

#endif