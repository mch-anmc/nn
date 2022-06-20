//
// Created by anmc on 22-6-16.
//

#include "matrix.hpp"

int main() {
    matrix<float> a(5, 6);
    matrix<float> b(6, 6);
    auto c = a * b;

    std::cout << c << std::endl;
    return 0;
}