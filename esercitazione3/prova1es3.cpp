#include <iostream>
#include<concepts>
#include"rational.hpp"
int main() {
    rational<int> a(4,2);
    rational<int> b(2,8);

    std::cout << a << "\n";
    std::cout << a-b <<"\n";
    std::cout << a/b <<"\n";
    std::cout << a+b << "\n";
    std::cout << a*b << "\n";
    std::cout << "Numeratore: " << a.num() << " Denominatore: " << a.den() << "\n";

    return 0;
}