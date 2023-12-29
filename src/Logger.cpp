#include "../include/Logger.hpp"

std::map<int, std::string> errors;
  

void setup_errors() {
    errors[1] = "Error 01: input file not found or not accessible";
    errors[2] = "Error 02: invalid input file format";
    errors[3] = "Error 03: invalid command";
    errors[4] = "Error 07: cannot override output file";
    errors[5] = "Error 05: data packet error at line X";
    errors[6] = "Error 06: data at line X and Y are duplicated";

}