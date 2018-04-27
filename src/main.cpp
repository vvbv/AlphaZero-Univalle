#include "main.h"
#include "board.hpp"

int main(int argc, const char* argv[]){
    std::cout << "Alpha-Zero Univalle" << std::endl;
    Board board;
    std::cout << board.generate_board( 5 ) << std::endl;
    std::cout << board.generate_board( 4 ) << std::endl;
    return 0;
}