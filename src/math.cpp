#include "math.hpp"

Math::Math(){};

Math::~Math(){};

int Math::generate_random_number( int start, int end ){
    std::random_device rd; 
    std::mt19937 eng( rd() );
    std::uniform_int_distribution<> distr( start, end );
    return distr( eng );
};

int Math::generate_random_number_odd( int start, int end ){
        int random_fruit_quantity = generate_random_number( start, end );
        if( random_fruit_quantity % 2 != 0 ){
            return random_fruit_quantity;
        }else{
            return generate_random_number_odd( start, end );
        }
};