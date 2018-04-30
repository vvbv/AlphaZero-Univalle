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

                //same_pos_with_other_player = false;

                if( is_max ){
                    tmp_expansion_elements.pos_max_row = pos_row;
                    tmp_expansion_elements.pos_max_column = pos_column;
                    if( pos_info == 9 ){
                        tmp_game_elements.board.change_value_in_boxes( current_position, tmp_game_elements.board.get_horse_human_id() );
                    };
                }else{
                    tmp_expansion_elements.pos_min_row = pos_row;
                    tmp_expansion_elements.pos_min_column = pos_column;
                    if( pos_info == 9 ){
                        tmp_game_elements.board.change_value_in_boxes( current_position, tmp_game_elements.board.get_horse_pc_id() );                        
                    };
                };

                if( pos_info == tmp_game_elements.board.get_item_id() ){
                    if( is_max ){
                        tmp_expansion_elements.max_items_quantity++;
                    }else{
                        tmp_expansion_elements.min_items_quantity++;
                    };
                };

                if( is_max ){
                    if( pc_turn ){
                        if( pos_info == tmp_game_elements.board.get_horse_human_id() ){
                            tmp_expansion_elements.max_items_quantity += tmp_expansion_elements.min_items_quantity;
                            tmp_expansion_elements.min_items_quantity = 0;
                            tmp_expansion_elements.same_pos_with_other_player = true;
                            tmp_game_elements.board.change_value_in_boxes( current_position, tmp_game_elements.board.get_horse_human_pc_id() );
                        };
                    }else{
                        if( pos_info == tmp_game_elements.board.get_horse_pc_id() ){
                            tmp_expansion_elements.max_items_quantity += tmp_expansion_elements.min_items_quantity;
                            tmp_expansion_elements.min_items_quantity = 0;
                            tmp_expansion_elements.same_pos_with_other_player = true;
                            tmp_game_elements.board.change_value_in_boxes( current_position, tmp_game_elements.board.get_horse_human_pc_id() );
                        };
                    };
                }else{
                    if( pc_turn ){
                        if( pos_info == tmp_game_elements.board.get_horse_human_id() ){
                            tmp_expansion_elements.min_items_quantity += tmp_expansion_elements.max_items_quantity;
                            tmp_expansion_elements.max_items_quantity = 0;
                            tmp_expansion_elements.same_pos_with_other_player = true;
                            tmp_game_elements.board.change_value_in_boxes( current_position, tmp_game_elements.board.get_horse_human_pc_id() );
                        };
                    }else{
                        if( pos_info == tmp_game_elements.board.get_horse_pc_id() ){
                            tmp_expansion_elements.min_items_quantity += tmp_expansion_elements.max_items_quantity;
                            tmp_expansion_elements.max_items_quantity = 0;
                            tmp_expansion_elements.same_pos_with_other_player = true;
                            tmp_game_elements.board.change_value_in_boxes( current_position, tmp_game_elements.board.get_horse_human_pc_id() );
                        };
                    };
                };
                std::tuple < minmax_game_elements > new_no_dynamic_expansion = std::make_tuple( tmp_expansion_elements );
                no_dynamic_expansions.push_back( new_no_dynamic_expansion );
                index_in_non_dynamic_expansions index_nde;
                index_nde.index = no_dynamic_expansions.size() - 1;
                std::tuple < minmax_game_elements, index_in_non_dynamic_expansions > new_expansion = std::make_tuple( tmp_expansion_elements, index_nde );
                expansions.push_back( new_expansion );
                
                std::cout << "POS MAX: [" << std::get< 0 >( new_expansion ).pos_max_row << "," <<  std::get< 0 >( new_expansion ).pos_max_column << "] - " 
                          << "POS MIN: [" << std::get< 0 >( new_expansion ).pos_min_row << "," <<  std::get< 0 >( new_expansion ).pos_min_column << "] - "
                          << "SAME POS: " << std::get< 0 >( new_expansion ).same_pos_with_other_player << " - " 
                          << "MAX ITEMS: " << std::get< 0 >( new_expansion ).max_items_quantity << " - " 
                          << "MAX ITEMS: " << std::get< 0 >( new_expansion ).min_items_quantity << " - " 
                          << "DEPTH: " << std::get< 0 >( new_expansion ).depth << " - "
                          << "IS MAX: " << is_max << " - "   
                          << "IS PC TURN: " << pc_turn 
                          << std::endl;;
            };
        };
        is_max = !is_max;
    };
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