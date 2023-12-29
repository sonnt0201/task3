#include <iostream>
#include <fstream>
#include <string>
#include <map>

#pragma once

 // errors[1] = "Error 01: input file not found or not accessible";
    // errors[2] = "Error 02: invalid input file format";
    // errors[3] = "Error 03: invalid command";
    // errors[4] = "Error 04: cannot override output file";
    // errors[5] = "Error 05: data packet error at line X";
    // errors[6] = "Error 06: data at line X and Y are duplicated";

#define ERROR_INP_FILE 1
#define ERROR_INP_FORMAT 2
#define ERROR_COMMAND 3
#define ERROR_OUT_FILE 4
#define ERROR_DATA_PACK 5
#define ERROR_DATA_DUP 6

using namespace std;

void logError(int errorcode, int line = -1);

