#ifndef MATH_HPP_
#define MATH_HPP_

#include <random>
#include <cmath>

class Math{

    private:
        
    public:
        Math();
        ~Math();
        int generate_random_number( int start, int end );
        int generate_random_number_odd( int start, int end );
};

#endif