#include <iostream>

struct state_game {
        int min_items_quantity;
        int max_items_quantity;
        int depth;
        bool invalid_move;
    };

state_game print_struct( state_game s_g );

int main(){
    state_game s_g;
    s_g.min_items_quantity = 0;
    s_g.max_items_quantity = 0;
    s_g.depth = 1;
    s_g.invalid_move = false;
    std::cout << print_struct( s_g ).depth;
};

state_game print_struct( state_game s_g ){
   s_g.depth = 2;
   return s_g;
};