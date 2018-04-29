#include "main.h"
#include "board.hpp"

int main(int argc, const char* argv[]){
    int items_quantity = 0;
    std::cout << "\nAlpha-Zero Univalle\n" << std::endl;
    std::cout << "Cantidad de items << ";
    std::cin >> items_quantity;
    if( items_quantity > 33 ){
        std::cout << "!# >> No hay casillas suficientes para el juego" << std::endl;
    }else{
        Board board;
        if( board.generate_board( items_quantity ) == 0 ){
            std::cout << "Tablero generado correctamente" << std::endl;
        }else{
            std::cout << "!# >> Número de items inválido" << std::endl; 
        }
    }
    return 0;
}