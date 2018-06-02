#include "main.hpp"
#include "board.hpp"
#include "game.hpp"
#include "minmax_node.hpp"

int main(int argc, const char* argv[]){
    int items_quantity = 0;
    std::cout << "\nAlpha-Zero Univalle\n" << std::endl;
    std::cout << "!# >> Ingrese la cantidad de items\n";
    std::cout << "!# << ";
    std::cin >> items_quantity;
    if( items_quantity > 33 ){
        std::cout << "!# >> No hay casillas suficientes para el juego" << std::endl;
    }else{
        Board board;
        Game game;
        if( board.generate_board( items_quantity ) == 0 ){
            std::cout << "!# >> Tablero generado correctamente" << std::endl;
            game.set_board( board );
            game.set_items_to_collect( items_quantity );
            game.start_new_game();
           
        }else{
            std::cout << "!# >> Número de items inválido" << std::endl; 
        };
    };

    return 0;
}