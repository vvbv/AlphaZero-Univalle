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

void Game::start_new_game( Board board, int max_depth  ){
    this->board = board;
    this->max_depth = max_depth;
    this->start_new_game();
};

void Game::start_new_game(){
    bool call_gg_displayed = false;
    std::cout << "#! >> Ingrese la profundiad" << std::endl;
    std::cout << "#! << ";
    std::cin >> this->max_depth;
    State_game new_game;
    new_game.min_items_quantity = 0;
    new_game.max_items_quantity = 0;
    new_game.depth = 0;
    new_game.board = this->board;
    new_game.invalid_move = false;
    std::cout << std::endl << "#! >> Tablero\n" << std::endl;
    for( int i = 0; i <  this->board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j <  this->board.get_BOARD_SIDE_SIZE(); j++ ){
            int i_j_tmp[2] = {i, j}; 
            std::cout << " " << this->board.get_box_value( i_j_tmp );
        };
        std::cout << std::endl;
    };
    
    std::vector < State_game > previous_moves;
    State_game best_mov = max_move( new_game, previous_moves );
    previous_moves = {};
    std::cout << std::endl << "#! >> Movimiento [ PC(2) ]  Marcador >> Usuario >> " << best_mov.min_items_quantity << " >> PC >> " << best_mov.max_items_quantity << std::endl;
    std::cout << "#! >> UF >> " << best_mov.max_items_quantity << "\n" << std::endl;
    for( int i = 0; i <  best_mov.board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j <  best_mov.board.get_BOARD_SIDE_SIZE(); j++ ){
            int i_j_tmp[2] = {i, j}; 
            std::cout << " " << best_mov.board.get_box_value( i_j_tmp );
        };
        std::cout << std::endl;
    };
    bool the_game_continues = true;
    if( game_ended( best_mov ) ){
        std::cout << "\n#! >> Juego terminado" << std::endl;
        std::cout << "#! >> Marcador final! >> Usuario >> " << best_mov.min_items_quantity << " >> PC >> " << best_mov.max_items_quantity << " \n" << std::endl;
        the_game_continues = false;
    };
    while( the_game_continues ){
        std::cout <<  best_mov.depth << std::endl;
        int current_position[2];
        for( int i = 0; i < best_mov.board.get_BOARD_SIDE_SIZE(); i++ ){
            for( int j = 0; j < best_mov.board.get_BOARD_SIDE_SIZE(); j++ ){
                int tmp_pos[2] = { i, j }; 
                if( best_mov.board.get_box_value( tmp_pos ) == best_mov.board.get_horse_human_id() ){
                    current_position[0] = i;
                    current_position[1] = j;
                };
            };
        };
        int option;
        std::string option_string;
        if( ((best_mov.min_items_quantity + 2) >= best_mov.max_items_quantity) || (call_gg_displayed) ){
            std::cout << "\n#! << ";
        }else{
            std::cout << "\n#! >> MSG PC: Call gg" << std::endl;
            call_gg_displayed = true;
            std::cout << "#! << ";
        };
        std::cin >> option_string;
        if( option_string == "gg" ){
            std::cout << "\n#! >> Juego terminado" << std::endl;
            std::cout << "#! >> PC gana por SYS_GG >> Marcador final! >> Usuario >> " << best_mov.min_items_quantity << " >> PC >> " << best_mov.max_items_quantity << " \n" << std::endl;
            break;
        };
        option = std::stoi( option_string );
        switch ( option )  
        {  
            case 0:   
                new_game = get_pos_up_right( best_mov, current_position, false );
                break;
            case 1:   
                new_game = get_pos_up_left( best_mov, current_position, false );
                break;
            case 2:   
                new_game = get_pos_left_up( best_mov, current_position, false );
                break;
            case 3:
                new_game = get_pos_left_down( best_mov, current_position, false );   
                break;
            case 4:
                new_game = get_pos_down_left( best_mov, current_position, false );   
                break;
            case 5:
                new_game = get_pos_down_right( best_mov, current_position, false );   
                break;
            case 6:
                new_game = get_pos_right_down( best_mov, current_position, false );   
                break;
            case 7:
                new_game = get_pos_right_up( best_mov, current_position, false );   
                break;
            default:  
                new_game = get_pos_up_right( best_mov, current_position, false );
                std::cout << "#! >> Error, default 0" << std::endl; 
        };

        if( new_game.invalid_move ){
            std::cout << "#! >> Oops, movimiento invalido, intenta nuevamente" << std::endl;
            continue;
        };

        std::cout << std::endl << "#! >> Movimiento [ USUARIO(1) ] Marcador >> Usuario >> " << new_game.min_items_quantity << " >> PC >> " << new_game.max_items_quantity << " \n" << std::endl;
        for( int i = 0; i <  new_game.board.get_BOARD_SIDE_SIZE(); i++ ){
            for( int j = 0; j <  new_game.board.get_BOARD_SIDE_SIZE(); j++ ){
                int i_j_tmp[2] = {i, j}; 
                std::cout << " " << new_game.board.get_box_value( i_j_tmp );
            };
            std::cout << std::endl;
        };

        best_mov.depth = 0;
        best_mov = max_move( new_game, previous_moves );
        previous_moves = {};
        std::cout << std::endl << "#! >> Movimiento [ PC(2) ] Marcador >> Usuario >> " << best_mov.min_items_quantity << " >> PC >> " << best_mov.max_items_quantity << std::endl;
        std::cout << "#! >> UF >> " << best_mov.max_items_quantity << "\n" << std::endl;
        for( int i = 0; i <  best_mov.board.get_BOARD_SIDE_SIZE(); i++ ){
            for( int j = 0; j <  best_mov.board.get_BOARD_SIDE_SIZE(); j++ ){
                int i_j_tmp[2] = {i, j}; 
                std::cout << " " << best_mov.board.get_box_value( i_j_tmp );
            };
            std::cout << std::endl;
        };

        if( game_ended( best_mov ) ){
            std::cout << "\n#! >> Juego terminado" << std::endl;
            std::cout << "#! >> Marcador final! >> Usuario >> " << best_mov.min_items_quantity << " >> PC >> " << best_mov.max_items_quantity << " \n" << std::endl;
            break;
        };
    };
};

State_game Game::get_pos_up_right( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] - 2;
    int new_pos_column = current_pos[1] + 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column < new_state.board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_up_left( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] - 2;
    int new_pos_column = current_pos[1] - 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column >= 0 ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_left_up( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] - 1;
    int new_pos_column = current_pos[1] - 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column >= 0 ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_left_down( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] + 1;
    int new_pos_column = current_pos[1] - 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < new_state.board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column >= 0 ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_down_left( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] + 2;
    int new_pos_column = current_pos[1] - 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < new_state.board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column >= 0 ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_down_right( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] + 2;
    int new_pos_column = current_pos[1] + 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < new_state.board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column < new_state.board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_right_down( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] + 1;
    int new_pos_column = current_pos[1] + 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < new_state.board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column < new_state.board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

State_game Game::get_pos_right_up( State_game state, int current_pos[2], bool is_max ){
    State_game new_state = state;
    new_state.depth = new_state.depth + 1;
    int new_pos_row = current_pos[0] - 1;
    int new_pos_column = current_pos[1] + 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column < new_state.board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = new_state.board.get_box_value( new_pos );
        if( (box_value == new_state.board.get_horse_pc_id()) || (box_value == new_state.board.get_horse_human_id()) ){
            new_state.invalid_move = true;
            return new_state;
        };
        if( box_value == new_state.board.get_item_id() ){
            if( is_max ){
                new_state.max_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.min_items_quantity++;
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        }else if( box_value == new_state.board.get_free_id() ){
            if( is_max ){
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_pc_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            }else{
                new_state.board.change_value_in_boxes( new_pos, new_state.board.get_horse_human_id() );
                new_state.board.change_value_in_boxes( current_pos, new_state.board.get_free_id() );
            };
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

void Game::set_items_to_collect( int items_quantity ){
    this->items_to_collect = items_quantity;
};

bool Game::compare_minmax_game_elements( minmax_game_elements *a, minmax_game_elements *b ){
    if(
        ( a->pos_max_row == b->pos_max_row ) &&
        ( a->pos_max_column == b->pos_max_column ) &&
        ( a->pos_min_row == b->pos_min_row ) &&
        ( a->pos_min_column == b->pos_min_column ) &&
        ( a->min_items_quantity == b->min_items_quantity ) &&
        ( a->max_items_quantity == b->max_items_quantity )
    ){
        return true;
    };
    return false;
};

bool Game::states_equals( State_game a, State_game b, bool is_max ){

    for( int i = 0; i < a.board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j < a.board.get_BOARD_SIDE_SIZE(); j++ ){
            int tmp_pos[2] = { i, j }; 
            if( is_max ){
                if( a.board.get_box_value( tmp_pos ) == a.board.get_horse_pc_id() ){
                    if( b.board.get_box_value( tmp_pos ) != a.board.get_horse_pc_id() ){
                        return false;
                    };
                };
            }else{
                if( a.board.get_box_value( tmp_pos ) == a.board.get_horse_human_id() ){
                    if( b.board.get_box_value( tmp_pos ) != a.board.get_horse_human_id() ){
                        return false;
                    };
                };
            };
            
        };
    };

    if(
        ( a.min_items_quantity == b.min_items_quantity ) &&
        ( a.max_items_quantity == b.max_items_quantity )
    ){
        return true;
    };
    return false;
};

State_game Game::max_move( State_game state, std::vector < State_game > previous_moves_x ){
    std::vector < State_game > previous_moves = previous_moves_x;
    int current_position[2];
    for( int i = 0; i < state.board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j < state.board.get_BOARD_SIDE_SIZE(); j++ ){
            int tmp_pos[2] = { i, j }; 
            if( state.board.get_box_value( tmp_pos ) == state.board.get_horse_pc_id() ){
                current_position[0] = i;
                current_position[1] = j;
            };
        };
    };
    if( game_ended( state ) ){
        return state;
    }else if( state.depth >= this->max_depth ){
        return state;
    }else{
        State_game best_move;
        int best_items = 0;
        std::vector < State_game > moves;
        State_game state_0 = state;
        moves.push_back( get_pos_up_right( state_0, current_position, true ) );
        State_game state_1 = state;
        moves.push_back( get_pos_up_left( state_1, current_position, true ) );
        State_game state_2 = state;
        moves.push_back( get_pos_left_up( state_2, current_position, true ) );
        State_game state_3 = state;
        moves.push_back( get_pos_left_down( state_3, current_position, true ) );
        State_game state_4 = state;
        moves.push_back( get_pos_down_left( state_4, current_position, true ) );
        State_game state_5 = state;
        moves.push_back( get_pos_down_right( state_5, current_position, true ) );
        State_game state_6 = state;
        moves.push_back( get_pos_right_down( state_6, current_position, true ) );
        State_game state_7 = state;
        moves.push_back( get_pos_right_up( state_7, current_position, true ) );
        // Con esto solo se mira si hay al menos un movimiento válido
        bool min_one_valid_move = false;
        for( int index_move = 0; index_move < moves.size(); index_move++ ){
            if( !moves[ index_move ].invalid_move ){
                min_one_valid_move = true;
            }else{
                moves.erase( moves.begin() + index_move );
            };
        };
        if( min_one_valid_move ){
            previous_moves.push_back( state );
        };
        for( int index_move = 0; index_move < moves.size(); index_move++ ){
            /*if( index_move == 0 ){
                best_move = moves[ index_move ];
            };*/
            if( !moves[ index_move ].invalid_move ){
                bool no_exist = true;
                for( int x = 0; x < previous_moves.size(); x++ ){
                    if( states_equals( previous_moves[x], moves[ index_move ], true ) ){
                        no_exist = false;
                        break;
                    };
                };
                if( no_exist ){
                    State_game min_game_state = min_move( moves[ index_move ], previous_moves );
                    /*if( moves[ index_move ].max_items_quantity <= min_game_state.max_items_quantity ){
                        if( best_move.max_items_quantity <= moves[ index_move ].max_items_quantity ){
                            best_move = moves[ index_move ];
                        };           
                    };*/
                    if( (moves[ index_move ].max_items_quantity <= min_game_state.max_items_quantity) && (min_game_state.max_items_quantity >= best_items) ){
                        /*if( best_items <= min_game_state.min_items_quantity ){
                            best_move = moves[ index_move ];
                        };*/
                        best_move = moves[ index_move ];
                        best_items = min_game_state.max_items_quantity;
                    };
                };                
            };
        };
        return best_move;
    };
};

State_game Game::min_move( State_game state, std::vector < State_game > previous_moves_x ){
    std::vector < State_game > previous_moves = previous_moves_x;
    int current_position[2];
    for( int i = 0; i < state.board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j < state.board.get_BOARD_SIDE_SIZE(); j++ ){
            int tmp_pos[2] = { i, j }; 
            if( state.board.get_box_value( tmp_pos ) == state.board.get_horse_human_id() ){
                current_position[0] = i;
                current_position[1] = j;
            };
        };
    };
    State_game best_move;
    int best_items = 0;
    std::vector < State_game > moves;
    State_game state_0 = state;
    moves.push_back( get_pos_up_right( state_0, current_position, false ) );
    State_game state_1 = state;
    moves.push_back( get_pos_up_left( state_1, current_position, false ) );
    State_game state_2 = state;
    moves.push_back( get_pos_left_up( state_2, current_position, false ) );
    State_game state_3 = state;
    moves.push_back( get_pos_left_down( state_3, current_position, false ) );
    State_game state_4 = state;
    moves.push_back( get_pos_down_left( state_4, current_position, false ) );
    State_game state_5 = state;
    moves.push_back( get_pos_down_right( state_5, current_position, false ) );
    State_game state_6 = state;
    moves.push_back( get_pos_right_down( state_6, current_position, false ) );
    State_game state_7 = state;
    moves.push_back( get_pos_right_up( state_7, current_position, false ) );
    // Con esto solo se mira si hay al menos un movimiento válido
    bool min_one_valid_move = false;
    for( int index_move = 0; index_move < moves.size(); index_move++ ){
        if( !moves[ index_move ].invalid_move ){
            min_one_valid_move = true;
        }else{
            moves.erase( moves.begin() + index_move );
        };
    };
    if( min_one_valid_move ){
        previous_moves.push_back( state );
    };
    for( int index_move = 0; index_move < moves.size(); index_move++ ){
        /*if( index_move == 0 ){
            best_move = moves[ index_move ];
        };*/
        if( !moves[ index_move ].invalid_move ){
            bool no_exist = true;
            for( int x = 0; x < previous_moves.size(); x++ ){
                if( states_equals( previous_moves[x], moves[ index_move ], false ) ){
                    no_exist = false;
                    break;
                };
            };
            if( no_exist ){
                State_game max_game_state = max_move( moves[ index_move ], previous_moves );
                //std::cout << "Prof min: " << max_game_state.depth << std::endl;
                /*if( moves[ index_move ].min_items_quantity >= max_game_state.min_items_quantity ){
                    best_move = moves[ index_move ];
                };*/
                if( (moves[ index_move ].min_items_quantity <= max_game_state.min_items_quantity) && (max_game_state.min_items_quantity >= best_items) ){
                    /*if( best_items <= max_game_state.min_items_quantity ){
                        best_move = moves[ index_move ];
                    };*/
                    best_move = moves[ index_move ];
                    best_items = max_game_state.min_items_quantity;
                };
            };
        };
    };
    if( moves[0].depth == 2 ){
        std::cout << best_move.max_items_quantity << " ";
    };
    std::cout << moves[0].depth << " ";
    return best_move;
};

bool Game::game_ended( State_game state ){
    for( int i = 0; i < state.board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j < state.board.get_BOARD_SIDE_SIZE(); j++ ){
            int tmp_pos[2] = { i, j }; 
            if( state.board.get_box_value( tmp_pos ) == state.board.get_item_id() ){
                return false;
            };
        };
    };
    return true;
};