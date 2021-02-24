#include <iostream>
#include <string>

#include "brainfuck.h"

int main(int, char**) {
    std::string brainfuck_code;
    std::string output;
    char yn;

    std::cout << "Enter your brainfuck code: ";
    std::cin >> brainfuck_code;
    do {
        std::cout << "Do you wish your output to be letters? y/n ";
        std::cin >> yn;
    } while (yn != 'y' && yn != 'n');

    Brainfuck::execute(brainfuck_code, output, (yn == 'y'));

    std::cout << "\n";
    std::cout << output << std::endl;

    return EXIT_SUCCESS;
}