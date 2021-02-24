#include <iostream>
#include <string>

#include "brainfuck.h"

int main(int, char**) {
    std::string brainfuck_code;
    std::string output_w_ascii;

    std::cout << "Enter your brainfuck code: " << std::endl;
    std::cin >> brainfuck_code;

    Brainfuck bf1(brainfuck_code);
    bf1.execute(output_w_ascii, true);

    std::cout << output_w_ascii << std::endl;

    return EXIT_SUCCESS;
}