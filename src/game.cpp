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
/*
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

    current_max_position[0] = pos_pc[0];
    current_max_position[1] = pos_pc[1];
    current_min_position[0] = pos_human[0];
    current_min_position[1] = pos_human[1];

    std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > last_node;
    std::vector < std::tuple < minmax_game_elements > > no_dynamic_expansions;
    std::vector < std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > > expansions;

    minmax_game_elements first_expansion_elements;
    first_expansion_elements.pos_max_row = current_max_position[0];
    first_expansion_elements.pos_max_column = current_max_position[1];
    first_expansion_elements.pos_min_row = current_min_position[0];
    first_expansion_elements.pos_min_column = current_min_position[1];
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

    last_node = expansions[ 0 ];

    bool is_max = true;
    while( expansions.size() > 0 ){

        last_node = expansions[ 0 ];
        //expansions.erase( expansions.begin() );

        minmax_game_elements tmp_game_elements;
        tmp_game_elements = std::get< 0 >( last_node );


        std::vector < std::tuple < int, int, int > > moves_pos_info;

        int current_position[2];
        if( is_max ){
            current_position[0] = tmp_game_elements.pos_max_row;
            current_position[1] = tmp_game_elements.pos_max_column;
        }else{
            current_position[0] = tmp_game_elements.pos_min_row;
            current_position[1] = tmp_game_elements.pos_min_column;
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

            int pos[2] = { std::get< 0 >( moves_pos_info[i] ), std::get< 1 >( moves_pos_info[i] ) };
            int pos_info = std::get< 2 >( moves_pos_info[i] );

            if( pos_info != -1 ){

                minmax_game_elements tmp_expansion_elements = tmp_game_elements;
                tmp_expansion_elements.depth = tmp_expansion_elements.depth + 1;

                if( (pos_info == tmp_expansion_elements.board.get_horse_pc_id()) || (pos_info == tmp_expansion_elements.board.get_horse_human_id()) ){
                    continue;
                };

                if( pos_info == tmp_expansion_elements.board.get_item_id() ){
                    if( is_max ){
                        tmp_expansion_elements.max_items_quantity++;
                        tmp_expansion_elements.board.change_value_in_boxes( pos, tmp_expansion_elements.board.get_horse_pc_id() );
                        tmp_expansion_elements.board.change_value_in_boxes( current_position, tmp_expansion_elements.board.get_free_id() );
                        tmp_expansion_elements.pos_max_row = pos[0];
                        tmp_expansion_elements.pos_max_column = pos[1];
                    }else{
                        tmp_expansion_elements.min_items_quantity++;
                        tmp_expansion_elements.board.change_value_in_boxes( pos, tmp_expansion_elements.board.get_horse_human_id() );
                        tmp_expansion_elements.board.change_value_in_boxes( current_position, tmp_expansion_elements.board.get_free_id() );
                        tmp_expansion_elements.pos_min_row = pos[0];
                        tmp_expansion_elements.pos_min_column = pos[1];
                    };
                };

                std::tuple < minmax_game_elements > new_no_dynamic_expansion = std::make_tuple( tmp_expansion_elements );
                index_in_non_dynamic_expansions index_nde;
                index_nde.index = no_dynamic_expansions.size() - 1;
                no_dynamic_expansions.push_back( new_no_dynamic_expansion );

                std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > new_expansion = std::make_tuple( tmp_expansion_elements, index_nde );
                
                bool is_different = true;
                for( int x = 0; x < expansions.size(); x++  ){
                    if(
                        ( std::get<0>( no_dynamic_expansions[x] ).pos_max_column == std::get<0>( new_no_dynamic_expansion ).pos_max_column ) &&
                        ( std::get<0>( no_dynamic_expansions[x] ).pos_max_row == std::get<0>( new_no_dynamic_expansion ).pos_max_row ) &&
                        ( std::get<0>( no_dynamic_expansions[x] ).pos_min_column == std::get<0>( new_no_dynamic_expansion ).pos_min_column ) &&
                        ( std::get<0>( no_dynamic_expansions[x] ).pos_min_row == std::get<0>( new_no_dynamic_expansion ).pos_min_row ) &&
                        ( std::get<0>( no_dynamic_expansions[x] ).max_items_quantity == std::get<0>( new_no_dynamic_expansion ).max_items_quantity ) &&
                        ( std::get<0>( no_dynamic_expansions[x] ).min_items_quantity == std::get<0>( new_no_dynamic_expansion ).min_items_quantity ) 
                    ){
                        std::cout << "Repetida en:" << x << std::endl;
                        is_different = false;
                        break;
                    };
                };

                if( is_different ){
                    expansions.push_back( new_expansion );
                    std::cout 
                        << "POS MAX: [" << std::get< 0 >( new_expansion ).pos_max_row << "," <<  std::get< 0 >( new_expansion ).pos_max_column << "] - " 
                        << "POS MIN: [" << std::get< 0 >( new_expansion ).pos_min_row << "," <<  std::get< 0 >( new_expansion ).pos_min_column << "] - "
                        << "MAX ITEMS: " << std::get< 0 >( new_expansion ).max_items_quantity << " - " 
                        << "MIX ITEMS: " << std::get< 0 >( new_expansion ).min_items_quantity << " - " 
                        << "DEPTH: " << std::get< 0 >( new_expansion ).depth << " - "
                        << "IS MAX: " << is_max << " - "   
                        << "IS PC TURN: " << pc_turn << " - " 
                        << "EXP: " << expansions.size() << " - "
                        << "IQ: " << board.get_items_quantity() - std::get< 0 >( new_expansion ).max_items_quantity - std::get< 0 >( new_expansion ).min_items_quantity 
                        << std::endl;
                    //std::cout << board.get_items_quantity() - std::get< 0 >( new_expansion ).max_items_quantity - std::get< 0 >( new_expansion ).min_items_quantity << " - " << expansions.size() << std::endl;

                    // Paada arbitraria
                    if( (board.get_items_quantity() - std::get< 0 >( new_expansion ).max_items_quantity - std::get< 0 >( new_expansion ).min_items_quantity) == 0 ){
                        break;
                    };
                };
            };
        };
        is_max = !is_max;
    };
    */
};

state_game Game::get_pos_up_right( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] - 2;
    int new_pos_column = pos[1] + 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_up_left( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] - 2;
    int new_pos_column = pos[1] - 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column >= 0 ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_left_up( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] - 1;
    int new_pos_column = pos[1] - 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column >= 0 ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_left_down( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] + 1;
    int new_pos_column = pos[1] - 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column >= 0 ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_down_left( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] + 2;
    int new_pos_column = pos[1] - 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column >= 0 ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_down_right( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] + 2;
    int new_pos_column = pos[1] + 1;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_right_down( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] + 1;
    int new_pos_column = pos[1] + 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row < board.get_BOARD_SIDE_SIZE() ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = board.get_box_value( new_pos );
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
        };
        return new_state;
    }else{
        new_state.invalid_move = true;
        return new_state;
    };
};

state_game Game::get_pos_right_up( state_game, int current_pos[], bool is_max ){
    state_game new_state = state_game;
    //new_state.depth = new_state.depth + 1;
    int new_pos_row = pos[0] - 1;
    int new_pos_column = pos[1] + 2;
    int new_pos[2] = { new_pos_row, new_pos_column };
    if( ( new_pos_row >= 0 ) && ( new_pos_column < board.get_BOARD_SIDE_SIZE() ) ){
        int box_value = board.get_box_value( new_pos );
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

void Game::start_new_game( Board board ){
    this->board = board;
    this->start_new_game();
};

void Game::start_new_game(){
    
    /*bool pc_turn = true; // In each game, pc starts first.
    while( ( this->items_collected_by_human + this->items_collected_by_pc - this->items_to_collect ) != 0 ){
        int minmax_action = minmax( this->board, pc_turn );
        pc_turn = !pc_turn;
    };*/

    state_game new_game;
    new_game.min_items_quantity = 0;
    new_game.max_items_quantity
    new_game.depth = 0;
    new_game.board = 0;
    new_game.invalid_move = false;
    std::vector < state_game > previous_moves;
    max_move( new_game, previous_moves );

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

state_game Game::maxmove( state_game state, std::vector < state_game > previous_moves ){
    if( game_ended( state ) ){
        std::cout << "Juego terminado" << std::endl;
    }else{
        state_game best_move;
        std::vector < state_game > moves;
        moves_pos_info.push_back( get_pos_up_right( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_up_left( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_left_up( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_left_down( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_down_left( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_down_right( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_right_down( state.board, current_position ) );
        moves_pos_info.push_back( get_pos_right_up( state.board, current_position ) );
        for( int index_move = 0; index_move < moves.size(); index_move++ ){
            if( !moves[ index_move ].invalid_move ){
                if ( std::find( previous_moves.begin(), previous_moves.end(), moves[ index_move ] ) == previous_moves.end() ){
                    state_game min_game_state = min_move( moves[ index_move ] );
                    if( moves[ index_move ].max_items_quantity >= min_game_state.max_items_quantity ){
                        best_move = moves[ index_move ];
                    };
                };
            };
        };
        return best_move;
    };
};

state_game Game::min_move( state_game state, std::vector < state_game > previous_moves ){
    state_game best_move;
    std::vector < state_game > moves;
    moves_pos_info.push_back( get_pos_up_right( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_up_left( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_left_up( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_left_down( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_down_left( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_down_right( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_right_down( state.board, current_position ) );
    moves_pos_info.push_back( get_pos_right_up( state.board, current_position ) );
    for( int index_move = 0; index_move < moves.size(); index_move++ ){
        if( !moves[ index_move ].invalid_move ){
            if ( std::find( previous_moves.begin(), previous_moves.end(), moves[ index_move ] ) == previous_moves.end() ){
                state_game max_game_state = max_move( moves[ index_move ] );
                if( moves[ index_move ].min_items_quantity >= max_game_state.min_items_quantity ){
                    best_move = moves[ index_move ];
                };
            };
        };
    };
    return best_move;
};

bool Game::game_ended( state_game state, std::vector < std::tuple < int, int, int > > positions_visited ){
    for( int i = 0; i < state.board.get_BOARD_SIDE_SIZE(); i++ ){
        for( int j = 0; j < state.board.get_BOARD_SIDE_SIZE(); j++ ){
            int tmp_pos[2] = { i, j }; 
            if( state.board.get_box_value( tmp_pos ) != state.board.get_free_id() ){
                return false;
            };
        };
    };
    return true;
};