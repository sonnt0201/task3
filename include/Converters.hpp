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

// extern std::vector<float> MINLUX;
// extern std::vector<float> MAXLUX;


class Converters {
    private:
    std::string iFileName;
    std::string oFileName;
    
    

    public:
    Converters(std::string iFileName, std::string oFileName);
    void csvToDat();
    void datToCsv();
   
    
};

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
    std::string toCsv();
};

std::string timestampToTime(int timestamp); 