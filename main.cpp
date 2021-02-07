#include "brainfuck.h"

#include <iostream>
#include <string>

int main(int, char**) {

    std::string brainfuck_code;
    std::string output;
    char ascii;

    std::cout << "Enter your brainfuck code: ";
    std::cin >> brainfuck_code;
    do {
        std::cout << "Do you wish your output to be letters? y/n ";
        std::cin >> ascii;
    } while(ascii != 'y' && ascii != 'n');
    
    Brainfuck::execute(brainfuck_code, output, ascii);

    std::cout << "\n";
    std::cout << output << std::endl;
    
    return EXIT_SUCCESS;
}