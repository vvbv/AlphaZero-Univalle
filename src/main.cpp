#include "main.hpp"
#include "board.hpp"
#include "game.hpp"
#include "minmax_node.hpp"

int main(int argc, const char* argv[]){
    int items_quantity = 0;
    std::cout << "\nAlpha-Zero Univalle\n" << std::endl;
    std::cout << "Cantidad de items << ";
    std::cin >> items_quantity;
    if( items_quantity > 33 ){
        std::cout << "!# >> No hay casillas suficientes para el juego" << std::endl;
    }else{
        Board board;
        Game game;
        if( board.generate_board( items_quantity ) == 0 ){
            std::cout << "Tablero generado correctamente" << std::endl;
            game.set_board( board );
            game.set_items_to_collect( items_quantity );
            /*int pos[2] = {2,2};
            std::tuple < int, int, int > tp;
            tp = game.get_pos_up_right( pos );
            std::cout << "UR" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_up_left( pos );
            std::cout << "UL" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_left_up( pos );
            std::cout << "LU" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_left_down( pos );
            std::cout << "LD" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_down_left( pos );
            std::cout << "DL" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_down_right( pos );
            std::cout << "DR" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_right_down( pos );
            std::cout << "RD" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            tp = game.get_pos_right_up( pos );
            std::cout << "RU" << "[" << std::get<0>( tp ) << "," << std::get<1>( tp ) << "] - " << std::get<2>( tp ) << std::endl;
            */
        }else{
            std::cout << "!# >> Número de items inválido" << std::endl; 
        }
    }

    //Minmax_node *ancestor;
    //Minmax_node minmax_node;

    return 0;
}