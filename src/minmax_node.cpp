#include "minmax_node.hpp"

Minmax_node::Minmax_node(){};
Minmax_node::~Minmax_node(){};
void Minmax_node::regressive_update(){
    
    int index_min_descendent = -1;
    int index_max_descendent = -1;
    for( int i = 0; i < this->descendent.size(); i++ ){
        if( this->descendent[ i ]->get_utility() < index_max_descendent ){
            index_min_descendent = i;
        };
        if( this->descendent[ i ]->get_utility() > index_max_descendent ){
            index_max_descendent = i;
        };
    };

    if( this->is_max && this->is_root && !this->is_sheet ){
        this->utility = this->descendent[ index_max_descendent ]->get_utility();
    };
    if( !this->is_max && this->is_root && !this->is_sheet ){
        this->utility = this->descendent[ index_min_descendent ]->get_utility();
    };
    if( !this->is_root ){
        this->ancestor->regressive_update();
    };

};
void Minmax_node::set_utility( int utility ){
    this->utility = utility;
};
int Minmax_node::get_utility(){
    return this->utility;
};
void Minmax_node::set_is_max( bool is_max ){
    this->is_max = is_max;
};
bool Minmax_node::get_is_max(){
    return this->is_max;
};
void Minmax_node::set_is_root( bool is_root ){
    this->is_root = is_root;
};
bool Minmax_node::get_is_root(){
    return this->is_root;
};
void Minmax_node::set_is_sheet( bool is_sheet ){
    this->is_sheet = is_sheet;
};
bool Minmax_node::get_is_sheet(){
    return this->is_sheet;
};