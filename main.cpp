#include "vector.hpp"
#include "matrix.hpp"
int main() {
    Vector<float> vec({1, 2, 3, 4, 5});
    //std::cout << vec;
    std::clog << " -- Main function --\n";
    Matrix<float> test({{1, 2, 3}, 
                        {4, 5, 6},
                        {7, 8, 9}});
    std::cout << test;

}