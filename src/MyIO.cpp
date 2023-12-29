#include "../include/MyIO.hpp"

MyIO::MyIO(int argv, char **argc)
{
    this->argv = argv;
    this->argc = argc;

    this-> inputType = this->setupInput();

};

int MyIO::setupInput()
{
    int argv = this->argv;
    char **argc = this->argc;

    if (argv != 3)
        return INVALID;

    std::string first(argc[1]);
    std::string sec(argc[2]);

    // check length of file name
    if (first.length() <= EXT_LEN || sec.length() <= EXT_LEN)
        return INVALID;

    std::cout << (first.substr(first.length() - EXT_LEN, EXT_LEN) == ".csv") << std::endl;

    if (
        (first.substr(first.length() - EXT_LEN, EXT_LEN) == ".dat") && (sec.substr(sec.length() - EXT_LEN, EXT_LEN) == ".csv"))
    {
        this->iFile = first;
        this->oFile = sec;
        return DECODE;
    };

    if (
        (first.substr(first.length() - EXT_LEN, EXT_LEN) == ".csv") && (sec.substr(sec.length() - EXT_LEN, EXT_LEN) == ".dat"))
    {
        
        this->iFile = first;
        this->oFile = sec;
        return ENCODE;
    };

    return INVALID;
}
