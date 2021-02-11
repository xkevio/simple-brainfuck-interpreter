#include "brainfuck.h"

#include <array>
#include <string>
#include <algorithm>
#include <iostream>

namespace Brainfuck {

    namespace {
        std::array<std::uint8_t, 30'000> cells; 
        std::string input_;
        
        int current_index = 0;
        int current_char = 0;

        void remove_spaces(std::string &input) {
            input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
        }

        void remove_new_lines(std::string &input) {
            input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
        }

        int find_matching_end_bracket(int current_char, const std::string &input) {
            int new_index = 0;
            int expected = 0;
            int found = 0;
            for (;current_char < input.length(); current_char++) {
                if(input[current_char] == '[') expected++;
                if(input[current_char] == ']') {
                    found++;
                    if(expected == found) {
                        new_index = current_char;
                        break;
                    }
                }
            }
            return new_index;
        }

        int find_matching_start_bracket(int current_char, const std::string &input) {
            int new_index = 0;
            int expected = 0;
            int found = 0;
            for (;current_char >= 0; current_char--) {
                if(input[current_char] == ']') expected++;
                if(input[current_char] == '[') {
                    found++;
                    if(expected == found) {
                        new_index = current_char;
                        break;
                    }
                }
            }
            return new_index;
        }

        void op_codes(const char &cur, std::string &output, bool ascii) {
            switch (cur)
            {
                case '>':
                    if(current_index == cells.size() - 1) {
                        current_index = 0;
                    } else {
                        current_index++;
                    }
                    break;
                case '<':
                    if(current_index == 0) {
                        current_index = cells.size() - 1;
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
                    if(!ascii) {
                        output += std::to_string(cells[current_index]);
                    }
                    else {
                        output += char(cells[current_index]);
                    }
                    break;
                case ',':
                {
                    std::string in;
                    std::cout << "Enter input between 0 and 255: ";
                    std::cin >> in;
                    if(!in.empty() && std::all_of(in.begin(), in.end(), ::isdigit)) {
                        auto c_in = stoi(in);
                        if(c_in >= 0 && c_in <= 255) {
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
                    if(cells[current_index] == 0) {
                        current_char = find_matching_end_bracket(current_char, input_);
                    }
                    break;
                case ']':
                    if(cells[current_index] != 0) {
                        current_char = find_matching_start_bracket(current_char, input_);
                    }
                    break;
                default:
                    std::cout << "Not a valid Brainfuck program! Unknown symbol at " << current_index << std::endl;
                    break;
            }
        }


        void reset() {
            std::fill(cells.begin(), cells.end(), 0);
            current_char = 0;
            current_index = 0;
            input_ = "";
        }
    }

    void execute(const std::string &input, std::string &output, bool ascii) {
        input_ = input;
        remove_spaces(input_);
        remove_new_lines(input_);
        
        while(current_char < input_.length()) {
            op_codes(input_[current_char], output, ascii);
            current_char++;
        }

        reset();
    }
}