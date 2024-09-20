#include <cstdint>
#include <iostream>
#include <math.h>

 
int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    if (a > b and a > c and pow(a, 2) == pow(b, 2) + pow(c, 2)) {
        std::cout << "YES";
    }
    else if (b > a and b > c and pow(b, 2) == pow(a, 2) + pow(c, 2)) {
        std::cout << "YES";
    }
    else if (c > a and c > b and pow(c, 2) == pow(a, 2) + pow(b, 2)) {
        std::cout << "YES";
    }
    else if (a + b > c and a + c > b and b + c > a) {
        std::cout << "NO";
    }
    else {
        std::cout << "UNDEFINED";
    }

}