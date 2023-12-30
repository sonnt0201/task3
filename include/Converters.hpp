#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "MyIO.hpp"
#include <fstream>
#include <map>
#include "Logger.hpp"
#pragma once

/*
Converters' object encode .csv file to .dat or decode .dat to .csv.
Initialized with input and output file names from MyIO.
*/
class Converters {
    private:
    std::string iFileName;
    std::string oFileName;
    
    

    public:
    Converters(std::string iFileName, std::string oFileName);
    /*
    Use in case input type is ENCODE.
    */
    void csvToDat();

    /*
    Use in case input type is DEOCDE.
    */  
    void datToCsv();
   
    
};

/*
Record extract, save and handle a csv line.
Encode a record data to a hex line.
Init with a row of csv file and extract to a record data.
*/
class Record {
    private:
    std::string raw;
    bool valid;
    int id;
    int timestamp;
    int location;
    int lux;
    int floatToHex(float f);
   public: 
    Record(std::string row);
    
    int parseTimestamp(const std::string& timestampStr);
    
    int getId();
    int getTimestamp();
    int getLocation();
    int getLux();
    int checkSum();
    int packLen = 14;
    std::string toHex();
    bool isvalid();

};

/*
Init with a hex row line from .dat file.
Decode a .dat line to record data
*/
class HexRow {
    private:
    int id, timestamp, location;
    float lux;
    bool valid;
    public:
    HexRow(std::string row);
    bool isvalid ();
    int getId();
    int getTimestamp();
    int getLocation();
    float getLux();
    std::string getBright();

    // return a csv line for Converters.
    std::string toCsv();
};

// convert timestamp(in second) to formated time.
std::string timestampToTime(int timestamp); 