#include <iostream>
#include "calculator.hpp"

int main() {
    Calculator calculator;
    Score score{calculator.total(2, 3)};
    const char* text = "imaginary_call() is only text";
    std::cout << "Score: " << twice(score.value) << '\n';
    std::cout << text << '\n';
    return 0;
}
