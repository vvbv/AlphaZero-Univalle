#include "main.h"
#include "board.hpp"

int main(int argc, const char* argv[]){
    int items_quantity = 0;
    std::cout << "Alpha-Zero Univalle" << std::endl;
    std::cout << "Cantidad de items: ";
    std::cin >> items_quantity;
    Board board;
    if( board.generate_board( items_quantity ) == 0 ){
        std::cout << "Tablero generado correctamente" << std::endl;
    }
    
    return 0;
}