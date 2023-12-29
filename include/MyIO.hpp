#include <iostream>

#include <string>

#pragma once

#define ENCODE 1
#define DECODE 2
#define INVALID 0

// length of the file extension : both ".dat" and ".csv" has 4 in length
#define EXT_LEN 4

/*
    check for valid command-line input, return ENCODE | DECODE | INVALID
    ENCODE when command line request to create .dat file.
    DECODE when command line request to create .csv file.
    INVALID if invalid input.
*/

class MyIO
{
private:
    int argv;
    char **argc;

    int setupInput();

public:
    MyIO(int argv, char **argc);
    std::string iFile;
    std::string oFile;
    int inputType;
};
