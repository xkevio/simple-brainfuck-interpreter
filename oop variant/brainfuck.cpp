#include "brainfuck.h"

#include <algorithm>
#include <iostream>
#include <string>

Brainfuck::Brainfuck(const std::string& input) : input(input) {
    remove_spaces();
    remove_new_lines();

    cells.assign(30'000, 0);

    current_index = 0;
    current_char = 0;
}

void Brainfuck::remove_spaces() {
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
}

void Brainfuck::remove_new_lines() {
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
}

void Brainfuck::find_matching_end_bracket() {
    int expected = 0;
    int found = 0;
    while (current_char < input.length()) {
        if (input[current_char] == '[') expected++;
        if (input[current_char] == ']') {
            found++;
            if (expected == found) break;
        }
        current_char++;
    }
}

void Brainfuck::find_matching_start_bracket() {
    int expected = 0;
    int found = 0;
    while (current_char >= 0) {
        if (input[current_char] == ']') expected++;
        if (input[current_char] == '[') {
            found++;
            if (expected == found) break;
        }
        current_char--;
    }
}

void Brainfuck::op_codes(const char& cur, std::string& output) {
    switch (cur) {
        case '>':
            if (current_index == cells.size() - 1) {
                cells.emplace_back(0);
            } else {
                current_index++;
            }
            break;
        case '<':
            if (current_index == 0) {
                cells.emplace_front(0);
            } else {
                current_index--;
            }
            break;
        case '+':
            cells[current_index]++;
            break;
        case '-':
            cells[current_index]--;
            break;
        case '.':
            if (!ascii) {
                output += std::to_string(cells[current_index]);
            } else {
                output += cells[current_index];
            }
            break;
        case ',': {
            std::string in;
            std::cout << "Enter input between 0 and 255: ";
            std::cin >> in;
            if (!in.empty() && std::all_of(in.begin(), in.end(), ::isdigit)) {
                auto c_in = stoi(in);
                if (c_in >= 0 && c_in <= 255) {
                    cells[current_index] = c_in;
                } else {
                    std::cout << "Not a valid input! Enter a number between 0 and 255!" << std::endl;
                }
            } else {
                std::cout << "Not a valid input!" << std::endl;
            }
            break;
        }
        case '[':
            if (cells[current_index] == 0) {
                find_matching_end_bracket();
            }
            break;
        case ']':
            if (cells[current_index] != 0) {
                find_matching_start_bracket();
            }
            break;
        default:
            std::cerr << "Not a valid Brainfuck program! Unknown symbol at " << current_index << std::endl;
            break;
    }
}

void Brainfuck::execute(std::string& output, bool ascii) {
    this->ascii = ascii;
    while (current_char < input.length()) {
        op_codes(input[current_char], output);
        current_char++;
    }
}
