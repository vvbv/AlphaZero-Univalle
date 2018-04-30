#include "game.hpp"

Game::Game(){};
Game::~Game(){};
void Game::set_board( Board board ){
    this->board = board;
    this->items_collected_by_human = 0;
    this->items_collected_by_pc = 0;
};
Board Game::get_board(){
    return this->board;
};
int Game::minmax( Board board, bool pc_turn ){

    int pos_pc[2];
    int pos_human[2];

    for( int i = 0; i < board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j < board.get_BOARD_SIDE_SIZE(); j++ ){
            int tmp_pos[2] = { i, j }; 
            if( board.get_box_value( tmp_pos ) == board.get_horse_human_id() ){
                pos_human[0] = i;
                pos_human[1] = j;
            };
            if( board.get_box_value( tmp_pos ) == board.get_horse_pc_id() ){
                pos_pc[0] = i;
                pos_pc[1] = j;
            };
        };
    };

    int current_max_position[2];
    int current_min_position[2];

    if( pc_turn ){
        current_max_position[0] = pos_pc[0];
        current_max_position[1] = pos_pc[1];
    }else{
        current_min_position[0] = pos_human[0];
        current_min_position[1] = pos_human[1];
    };

    struct minmax_game_elements {
        int pos_max_row;
        int pos_max_column;
        int pos_min_row;
        int pos_min_column;
        bool same_pos_with_other_player;
        int min_items_quantity;
        int max_items_quantity;
        int depth;
        Board board;
    };

    struct index_in_non_dynamic_expansions{
        int index;
    };

    std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > last_node;
    std::vector < std::tuple < minmax_game_elements > > no_dynamic_expansions;
    std::vector < std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > > expansions;

    minmax_game_elements first_expansion_elements;
    first_expansion_elements.pos_max_row = current_max_position[0];
    first_expansion_elements.pos_max_column = current_max_position[1];
    first_expansion_elements.pos_min_row = current_min_position[0];
    first_expansion_elements.pos_min_column = current_min_position[1];
    first_expansion_elements.same_pos_with_other_player = false;
    first_expansion_elements.min_items_quantity = 0;
    first_expansion_elements.max_items_quantity = 0;
    first_expansion_elements.depth = 0;
    first_expansion_elements.board = board;

    index_in_non_dynamic_expansions first_index_in_non_dynamic_expansions;
    first_index_in_non_dynamic_expansions.index = 0;

    std::tuple < minmax_game_elements > first_non_dynamic_expansion = std::make_tuple( first_expansion_elements  );
    no_dynamic_expansions.push_back( first_non_dynamic_expansion );

    std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > first_expansion = std::make_tuple( first_expansion_elements, first_index_in_non_dynamic_expansions );
    expansions.push_back( first_expansion );

    int index_controller = 0;

    bool is_max = true;
    while( ( board.get_items_quantity() - std::get< 0 >( last_node ).min_items_quantity + std::get< 0 >( last_node ).max_items_quantity ) > 0 ){

        last_node = expansions[ index_controller ];

        minmax_game_elements tmp_game_elements;
        tmp_game_elements = std::get< 0 >( last_node );


        std::vector < std::tuple < int, int, int > > moves_pos_info;

        int current_position[2];
        if( is_max ){
            current_position[0] = tmp_game_elements.pos_max_row;
            current_position[0] = tmp_game_elements.pos_max_column;
        }else{
            current_position[0] = tmp_game_elements.pos_min_row;
            current_position[0] = tmp_game_elements.pos_min_column;
        };

        moves_pos_info.push_back( get_pos_up_right( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_up_left( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_left_up( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_left_down( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_down_left( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_down_right( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_right_down( tmp_game_elements.board, current_position ) );
        moves_pos_info.push_back( get_pos_right_up( tmp_game_elements.board, current_position ) );

        for( int i = 0; i < moves_pos_info.size(); i++ ){
            int pos_row = std::get< 0 >( moves_pos_info[i] );
            int pos_column = std::get< 1 >( moves_pos_info[i] );
            int pos_info = std::get< 2 >( moves_pos_info[i] );
            if( pos_info != -1 ){

                minmax_game_elements tmp_expansion_elements = tmp_game_elements;
                
                tmp_expansion_elements.depth = tmp_expansion_elements.depth + 1;

                if( is_max ){
                    tmp_expansion_elements.pos_max_row = pos_row;
                    tmp_expansion_elements.pos_max_column = pos_column;
                }else{
                    tmp_expansion_elements.pos_min_row = pos_row;
                    tmp_expansion_elements.pos_min_column = pos_column;
                };

                if( pos_info == tmp_game_elements.board.get_item_id() ){
                    
                };

                
                

            };

        };
        is_max = !is_max;
    }

    /*
        int pos_actual[2];
        pos_actual[0] = entorno.get_posicion_inicial()[0]; 
        pos_actual[1] = entorno.get_posicion_inicial()[1]; 

        std::tuple < int, int*, std::string, std::string, int, int, int, bool > ultima_tupla;
        std::vector < std::tuple < int, int*, std::string, std::string, int, int, bool > > arbol_expansiones_no_dinamico;
        std::vector < std::tuple < int, int*, std::string, std::string, int, int, int, bool > > arbol_expansiones;
        std::vector < std::tuple < int, int, bool > > posiciones_visitadas;

        std::vector < std::string > info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual, true );
        std::string info_casilla = info_entorno[4];

        int indice_controlador = -1;
        int pos_meta_vector = -1;
        int numero_nodos_expandidos = 0;
        int profundidad_maxima = -1;

        auto inicio = std::chrono::system_clock::now();
        std::time_t tiempo_inicio = std::chrono::system_clock::to_time_t( inicio );
        std::cout << std::endl << "Inició: " << std::ctime(&tiempo_inicio) << std::endl;

        while( info_casilla != "5" ){

            if( indice_controlador == -1 ){
                // index, posicion, información de la casilla, operador aplicado( nodo root, operador root )
                std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion;
                int *pos_apuntada = new int[2]();

                pos_apuntada[0] = pos_actual[0];
                pos_apuntada[1] = pos_actual[1];

                std::tuple  < int, int*, std::string, std::string, int, int, bool > expansion_no_dinamica;
                expansion_no_dinamica = std::make_tuple( 0, pos_apuntada, info_casilla, "root", 0, 0, false );
                arbol_expansiones_no_dinamico.push_back( expansion_no_dinamica );

                expansion = std::make_tuple( 0, pos_apuntada, info_casilla, "root", 0, 0, 0, false );

                arbol_expansiones.push_back( expansion );
                

                ultima_tupla = expansion;
                indice_controlador++;
            }else{

                int pos_tupla_controladora[2];

                pos_tupla_controladora[0] = std::get<1>( arbol_expansiones[ indice_controlador ] )[0];
                pos_tupla_controladora[1] = std::get<1>( arbol_expansiones[ indice_controlador ] )[1];

                // Id de la tupla controladora en el arreglo
                int id_padre_no_dinamico = std::get<6>( arbol_expansiones[ indice_controlador ] );
                int profundidad_actual = std::get<5>( arbol_expansiones[ indice_controlador ] ) + 1;
                if( profundidad_maxima < profundidad_actual ){
                    profundidad_maxima = profundidad_actual;
                }

                posiciones_visitadas.push_back( std::make_tuple( pos_tupla_controladora[0], pos_tupla_controladora[1], std::get<7>( arbol_expansiones[ indice_controlador ] ) ) );

                info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_tupla_controladora, true );
                info_casilla = info_entorno[4];
                numero_nodos_expandidos++;

                if( debug_mode ){

                    std::cout << std::to_string( pos_tupla_controladora[0] ) << " <> " << std::to_string( pos_tupla_controladora[1] ) 
                        << " Info: [" << info_entorno[4] << "] " 
                        << "Información del entorno: A:" << info_entorno[0] 
                        << " I:" << info_entorno[1] 
                        << " X:" << info_entorno[2] 
                        << " D:" << info_entorno[3] 
                        << " ID P-ND:" << id_padre_no_dinamico 
                        << " Tamaño del arbol: " << arbol_expansiones.size() 
                        << " Tiene flor: " << std::get<7>( arbol_expansiones[ indice_controlador ] ) << std::endl;

                }
                
                int pos_superior[2];
                int pos_lateral_izquierda[2];
                int pos_inferior[2];
                int pos_lateral_derecha[2];
                
                pos_superior[0] = this->c_entorno.get_pos_entorno_arriba( pos_tupla_controladora )[0];
                pos_superior[1] = this->c_entorno.get_pos_entorno_arriba( pos_tupla_controladora )[1];
                pos_lateral_izquierda[0] = this->c_entorno.get_pos_entorno_izquierda( pos_tupla_controladora )[0];
                pos_lateral_izquierda[1] = this->c_entorno.get_pos_entorno_izquierda( pos_tupla_controladora )[1];
                pos_inferior[0] = this->c_entorno.get_pos_entorno_abajo( pos_tupla_controladora )[0];
                pos_inferior[1] = this->c_entorno.get_pos_entorno_abajo( pos_tupla_controladora )[1];
                pos_lateral_derecha[0] = this->c_entorno.get_pos_entorno_derecha( pos_tupla_controladora )[0];
                pos_lateral_derecha[1] = this->c_entorno.get_pos_entorno_derecha( pos_tupla_controladora )[1];

                std::vector < std::string > info_entorno_casilla_superior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_superior, true );
                std::vector < std::string > info_entorno_casilla_lateral_izquierda = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_izquierda, true );
                std::vector < std::string > info_entorno_casilla_inferior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_inferior, true );
                std::vector < std::string > info_entorno_casilla_lateral_derecha = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_derecha, true );

                if( !info_entorno_casilla_lateral_derecha.empty() ){
                    if( ( info_entorno_casilla_lateral_derecha[4] != "1" ) && ( info_entorno_casilla_lateral_derecha[4] != "F" ) ){
                        
                        bool tiene_flor = std::get<7>( arbol_expansiones[ indice_controlador ] );
                        if( info_entorno_casilla_lateral_derecha[4] == "3" ){
                            tiene_flor = true;
                        }
                        
                        int *pos_apuntada = new int[2]();

                        pos_apuntada[0] = pos_lateral_derecha[0];
                        pos_apuntada[1] = pos_lateral_derecha[1];

                        int profundidad_tupla_padre = std::get<5>( arbol_expansiones[ indice_controlador ] ) + 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, bool > expansion_no_dinamica;
                        expansion_no_dinamica = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha", id_padre_no_dinamico, profundidad_actual, tiene_flor );
                        arbol_expansiones_no_dinamico.push_back( expansion_no_dinamica );
                        int id_homologo_no_dinamico = arbol_expansiones_no_dinamico.size() - 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha", id_homologo_no_dinamico, profundidad_actual, id_homologo_no_dinamico, tiene_flor );
                        if ( ultima_tupla != expansion ){
                            std::tuple < int, int, bool > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1], tiene_flor );
                            if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                                arbol_expansiones.insert( arbol_expansiones.begin() + indice_controlador + 1, expansion );
                                ultima_tupla = expansion;
                            }
                        }
                    }
                }

                if( !info_entorno_casilla_inferior.empty() ){
                    if( ( info_entorno_casilla_inferior[4] != "1" ) && ( info_entorno_casilla_inferior[4] != "F" ) ){

                        bool tiene_flor = std::get<7>( arbol_expansiones[ indice_controlador ] );
                        if( info_entorno_casilla_inferior[4] == "3" ){
                            tiene_flor = true;
                        }

                        int *pos_apuntada = new int[2]();

                        pos_apuntada[0] = pos_inferior[0];
                        pos_apuntada[1] = pos_inferior[1];

                        int profundidad_tupla_padre = std::get<5>( arbol_expansiones[ indice_controlador ] ) + 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, bool > expansion_no_dinamica;
                        expansion_no_dinamica = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo", id_padre_no_dinamico, profundidad_actual, tiene_flor );
                        arbol_expansiones_no_dinamico.push_back( expansion_no_dinamica );
                        int id_homologo_no_dinamico = arbol_expansiones_no_dinamico.size() - 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo", id_homologo_no_dinamico, profundidad_actual, id_homologo_no_dinamico, tiene_flor );
                        if ( ultima_tupla != expansion ){
                            std::tuple < int, int, bool > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1], tiene_flor );
                            if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                                arbol_expansiones.insert( arbol_expansiones.begin() + indice_controlador + 1, expansion );
                                ultima_tupla = expansion;
                            }
                        }
                    }
                }

                if( !info_entorno_casilla_lateral_izquierda.empty() ){
                    if( ( info_entorno_casilla_lateral_izquierda[4] != "1" ) && ( info_entorno_casilla_lateral_izquierda[4] != "F" ) ){

                        bool tiene_flor = std::get<7>( arbol_expansiones[ indice_controlador ] );
                        if( info_entorno_casilla_lateral_izquierda[4] == "3" ){
                            tiene_flor = true;
                        }

                        int *pos_apuntada = new int[2]();

                        pos_apuntada[0] = pos_lateral_izquierda[0];
                        pos_apuntada[1] = pos_lateral_izquierda[1];

                        int profundidad_tupla_padre = std::get<5>( arbol_expansiones[ indice_controlador ] ) + 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, bool > expansion_no_dinamica;
                        expansion_no_dinamica = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda", id_padre_no_dinamico, profundidad_actual, tiene_flor );
                        arbol_expansiones_no_dinamico.push_back( expansion_no_dinamica );
                        int id_homologo_no_dinamico = arbol_expansiones_no_dinamico.size() - 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda", id_homologo_no_dinamico, profundidad_actual, id_homologo_no_dinamico, tiene_flor );
                        if ( ultima_tupla != expansion ){
                            std::tuple < int, int, bool > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1], tiene_flor );
                            if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                                arbol_expansiones.insert( arbol_expansiones.begin() + indice_controlador + 1, expansion );
                                ultima_tupla = expansion;
                            }
                        }
                    }
                }
                
                if( !info_entorno_casilla_superior.empty() ){
                    if( ( info_entorno_casilla_superior[4] != "1" ) && ( info_entorno_casilla_superior[4] != "F" ) ){

                        bool tiene_flor = std::get<7>( arbol_expansiones[ indice_controlador ] );
                        if( info_entorno_casilla_superior[4] == "3" ){
                            tiene_flor = true;
                        }

                        int *pos_apuntada = new int[2]();

                        pos_apuntada[0] = pos_superior[0];
                        pos_apuntada[1] = pos_superior[1];

                        int profundidad_tupla_padre = std::get<5>( arbol_expansiones[ indice_controlador ] ) + 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, bool > expansion_no_dinamica;
                        expansion_no_dinamica = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba", id_padre_no_dinamico, profundidad_actual, tiene_flor );
                        arbol_expansiones_no_dinamico.push_back( expansion_no_dinamica );
                        int id_homologo_no_dinamico = arbol_expansiones_no_dinamico.size() - 1;

                        std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba", id_homologo_no_dinamico, profundidad_actual, id_homologo_no_dinamico, tiene_flor );
                        if ( ultima_tupla != expansion ){
                            std::tuple < int, int, bool > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1], tiene_flor );
                            if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                                arbol_expansiones.insert( arbol_expansiones.begin() + indice_controlador + 1, expansion );
                                ultima_tupla = expansion;
                            }
                        }
                    }
                }

                indice_controlador++;

                if( info_casilla == "5" ){
                    for( int e = 0; e < arbol_expansiones.size(); e++){
                        if( std::get< 2 >( arbol_expansiones[e] ) == "5" ){
                            pos_meta_vector = std::get< 6 >( arbol_expansiones[e] );
                            break;
                        }
                    }
                    break;
                }
            }
        };    

        auto fin = std::chrono::system_clock::now();
        std::time_t tiempo_fin = std::chrono::system_clock::to_time_t( fin );
        std::cout << "Finalizó: " << std::ctime(&tiempo_fin) << std::endl;

        std::tuple  < int, int*, std::string, std::string, int, int, bool > *tupla_regresion = &arbol_expansiones_no_dinamico[ pos_meta_vector ];
        int *pos_regresion = std::get<1>( *tupla_regresion );
        std::string val_tupla_regresion = std::get<2>( *tupla_regresion );
        std::string accion_tupla_regresion = std::get<3>( *tupla_regresion );
        int indice_padre =  std::get<4>( *tupla_regresion );

        std::vector < std::string > acciones;
    
        while( accion_tupla_regresion != "root" ){
            
            std::cout << " Pos: "
                    << "[" << pos_regresion[0] << "," << pos_regresion[1] << "]" 
                    << " Val: " << val_tupla_regresion 
                    << " Acción previa: " 
                    << accion_tupla_regresion 
                    << std::endl;

            acciones.push_back( accion_tupla_regresion );

            tupla_regresion = &arbol_expansiones_no_dinamico[std::get<4>( *tupla_regresion )];
            pos_regresion = std::get<1>( *tupla_regresion );
            val_tupla_regresion = std::get<2>( *tupla_regresion );
            accion_tupla_regresion = std::get<3>( *tupla_regresion );
            indice_padre = std::get<4>( *tupla_regresion );

        }

        std::cout << std::endl;
        std::cout << "Tamaño del arbol: " << arbol_expansiones.size() << std::endl;

        std::cout << "Número de nodos expandidos: " 
                << numero_nodos_expandidos << std::endl;
                
        std::cout << "Profundidad del árbol: " 
                << profundidad_maxima << std::endl;

        std::chrono::duration<double> duracion_algoritmo = fin - inicio;
        std::cout << "Duración del algoritmo: "
                << duracion_algoritmo.count() << "s" << std::endl;

        return std::make_tuple( acciones, numero_nodos_expandidos, profundidad_maxima, duracion_algoritmo.count() );
    };

    */
};
std::tuple < int, int, int > Game::get_pos_up_right( Board board, int pos[] ){
    int new_pos_row = pos[0] - 2;
    int new_pos_column = pos[1] + 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_up_left( Board board, int pos[] ){
    int new_pos_row = pos[0] - 2;
    int new_pos_column = pos[1] - 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column >= 0 ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_left_up( Board board, int pos[] ){
    int new_pos_row = pos[0] - 1;
    int new_pos_column = pos[1] - 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column >= 0 ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_left_down( Board board, int pos[] ){
    int new_pos_row = pos[0] + 1;
    int new_pos_column = pos[1] - 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column >= 0 ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_down_left( Board board, int pos[] ){
    int new_pos_row = pos[0] + 2;
    int new_pos_column = pos[1] - 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column >= 0 ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_down_right( Board board, int pos[] ){
    int new_pos_row = pos[0] + 2;
    int new_pos_column = pos[1] + 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_right_down( Board board, int pos[] ){
    int new_pos_row = pos[0] + 1;
    int new_pos_column = pos[1] + 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

std::tuple < int, int, int > Game::get_pos_right_up( Board board, int pos[] ){
    int new_pos_row = pos[0] - 1;
    int new_pos_column = pos[1] + 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        return std::make_tuple( new_pos_row, new_pos_column, board.get_box_value( new_pos ) );
    }else{
        return std::make_tuple( pos[0], pos[1], -1 );
    };
};

void Game::set_items_to_collect( int items_quantity ){
    this->items_to_collect = items_quantity;
};

void Game::start_new_game( Board board ){
    this->board = board;
    this->start_new_game();
};

void Game::start_new_game(){
    
    bool pc_turn = true; // In each game, pc starts first.
    while( ( this->items_collected_by_human + this->items_collected_by_pc - this->items_to_collect ) != 0 ){
        int minmax_action = minmax( this->board, pc_turn );
        pc_turn = !pc_turn;
    };
    
};