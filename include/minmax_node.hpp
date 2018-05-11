#ifndef MINMAX_NODE_HPP_
#define MINMAX_NODE_HPP_

#include <vector>

class Minmax_node{

    private:

        bool is_max;
        bool is_root;
        bool is_sheet;
        Minmax_node *ancestor;
        Minmax_node *selection;
        std::vector < Minmax_node* > descendent;
        int utility;

    public:
        Minmax_node();
        Minmax_node( bool is_max, bool is_root, bool is_sheet, int utility, Minmax_node &ancestor );
        ~Minmax_node();
        void regressive_update();
        void set_utility( int utility );
        int get_utility();
        void set_is_max( bool is_max );
        bool get_is_max();
        void set_is_root( bool is_root );
        bool get_is_root();
        void set_is_sheet( bool is_sheet );
        bool get_is_sheet();

};

#endif