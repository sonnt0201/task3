#include "../include/Logger.hpp"


std::ofstream logfile("task3.log");

void logError(int errorcode, int line)
{

    // errors[1] = "Error 01: input file not found or not accessible";
    // errors[2] = "Error 02: invalid input file format";
    // errors[3] = "Error 03: invalid command";
    // errors[4] = "Error 07: cannot override output file";
    // errors[5] = "Error 05: data packet error at line X";
    // errors[6] = "Error 06: data at line X and Y are duplicated";

    switch (errorcode)
    {
    case 1:
        logfile << "Error 01: input file not found or not accessible";
        break;
    case 2:
        logfile << "Error 02: invalid input file format";
        break;
    case 3:
        logfile << "Error 03: invalid command";
        break;
    case 4:
        logfile << "Error 07: cannot override output file";
        break;
    case 5:
        logfile << "Error 05: data packet error at line " << line;
        break;

    case 6:
        logfile << "Error 06: data at line " << line << " are duplicated";
        break;
    default:
        break;
    };

    logfile<<"\n";
}
