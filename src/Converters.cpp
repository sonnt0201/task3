#include "../include/Converters.hpp"


std::vector<float> MINLUX = {0, 20, 50, 100, 100, 150, 200, 250, 300, 500, 750, 1500, 2000, 5000, 10000};
std::vector<float> MAXLUX = {0, 50, 100, 200, 150, 250, 400, 350, 500, 700, 850, 2000, 5000, 20000};


Converters::Converters(std::string iFileName, std::string oFileName)
{
    this->iFileName = iFileName;
    this->oFileName = oFileName;
};

void Converters::csvToDat() {

    std::ifstream iFile(this->iFileName);
    std::ofstream oFile(this->oFileName);
    // Check if the file is open
    if (!iFile.is_open() ) {
        std::cerr << "Error opening the file." << std::endl;
        logError(ERROR_INP_FILE);
        return;
    }

    if (!oFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        logError(ERROR_OUT_FILE);
        return;
    }

    // read each line
    std::string line = "";
    bool firstRow = true;
    int linenum = 0;
    while (std::getline(iFile, line)) {
        linenum++;
        if (firstRow) {firstRow = false; continue;}
        Record record = Record(line);
        if (!record.isvalid()) {logError(ERROR_DATA_PACK, linenum);continue;}
        oFile<<record.toHex()<<"\n";
    }



}
void Converters::datToCsv()
{
    std::ifstream iFile(this->iFileName);
    std::ofstream oFile(this->oFileName); 

   // Check if the file is open
    if (!iFile.is_open() ) {
        std::cerr << "Error opening the file." << std::endl;
        logError(ERROR_INP_FILE);
        return;
    }

    if (!oFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        logError(ERROR_OUT_FILE);
        return;
    }

    // read each line
     std::string line = "";
     int linenum = 0;
    oFile<<"id,time,location,value,condition\n";
    while (std::getline(iFile, line)) {
      linenum++;
       HexRow hexrow = HexRow(line);
       if (!hexrow.isvalid()) {logError(ERROR_DATA_PACK, linenum);continue;}

        oFile<<hexrow.toCsv();
    


     
    }

}

Record::Record(std::string row)
{
    this->valid = true;

    std::stringstream ss(row);
    std::string token;

    // Parse and extract values from the comma-separated row
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ','))
    {
        // std::cout<<token<<"\n";
        tokens.push_back(token);
    }

    // Assuming that the input row has the correct format
    if (tokens.size() == 5)
    {
        try
        {
            id = std::stoi(tokens[0]);
            timestamp = parseTimestamp(tokens[1]);
            location = std::stoi(tokens[2]);

            union
            {
                float f;
                uint32_t i;
            } converter;

            converter.f = std::stof(tokens[3]);

            this->lux = converter.i;
        }
        catch (const std::exception &e)
        {
            this->valid = false;
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
        // Convert string values to appropriate types
    }
    else
    {
        this->valid = false;
        // Handle incorrect input format
        std::cerr << "Error: Incorrect input format:" << std::endl;
        std::cout << row << std::endl;
    }
}

int Record::parseTimestamp(const std::string &timestampStr)
{

    struct std::tm tm = {};
    std::istringstream ss(timestampStr);
    ss >> std::get_time(&tm, "%Y:%m:%d %H:%M:%S");
    return std::mktime(&tm);
}

bool Record::isvalid() {
    return this->valid;
}

int Record::getId()
{
    return this->id;
};
int Record::getTimestamp()
{
    return this->timestamp;
};
int Record::getLocation()
{
    return this->location;
};
int Record::getLux()
{
    return this->lux;
};
int Record::checkSum()
{
    int sum = ~packLen + ~id + ~location + 3;
    int temp = lux;
    while (temp > 0)
    {
        sum += ~(temp % 0x100) + 1;
        temp = temp / 0x100;
    }

    temp = timestamp;
    while (temp > 0)
    {
        sum += ~(temp % 0x100) + 1;
        temp = temp / 0x100;
    }

    // Take two's complement

    // Extract least significant byte
    uint8_t leastSignificantByte = static_cast<uint8_t>(sum);
    // checksum ++;
    return leastSignificantByte;
    // (sum % 0x100);
};

std::string Record::toHex()
{
    std::stringstream out;
    out.clear();

    // start
    out << std::hex
        << "a0 0e " << ((id <= 0xF) ? "0" : "") << id << " ";

    // timestamp
    std::stringstream temp;
    temp << std::hex << timestamp;
    std::string sTime = temp.str();
    while (sTime.length() < 8)
        sTime = '0' + sTime;

    for (int i = 0; i < sTime.length(); i++)
    {
        out << sTime[i];
        if (i % 2 == 1)
            out << " ";
    }

    temp.clear();
    temp.str("");
    out << ((location <= 0xF) ? "0" : "") << location << " ";

    // lux
    temp << std::hex << lux;
    std::string sLux = temp.str();
    // std::cout << sLux << std::endl;
    while (sLux.length() < 8)
        sLux = '0' + sLux;

    for (int i = 0; i < sLux.length(); i++)
    {
        out << sLux[i];
        if (i % 2 == 1)
            out << " ";
    }
    temp.clear();
    temp.str("");

    int checkSum = this->checkSum();
    out <<((checkSum <= 0xF) ? "0": "")<< this->checkSum() << " "
        << "a9";
    return out.str();
}

HexRow::HexRow(std::string row) {

    // example of row "A0 0E 02 65 4E 6F A0 02 43 C8 03 D7 47 A9"
     std::string const SAMPLE = "a0 0e 01 65 84 ed a0 02 44 b4 86 b8 43 a9";
       this->valid = true;
 if ((row.length() - 1)!= SAMPLE.length()) {cout<<row.length()<<" "<<SAMPLE.length()<<std::endl;this->valid = false; return;}

  
    const int rowlen = 43;
    // if (row.length() != rowlen) {this->valid = false; return;}
    std::string hstart, hlen, hid, htime[4], hlocation, hlux[4];
    std::stringstream ss(row);

    ss>> std::ws>>hstart>>hlen>>hid
    >>htime[0]>>htime[1]>>htime[2]>>htime[3]
    >>hlocation
    >>hlux[0]>>hlux[1]>>hlux[2]>>hlux[3];
    // std::cout<<hstart<<"\n";
    try {
        this->id = stoi(hid, nullptr, 16);
        this->timestamp = stoi(htime[0] + htime[1] + htime[2] + htime[3], nullptr, 16);
        this->location = stoi(hlocation, nullptr, 16);

        // get raw string of lux:
        std::string str = hlux[0] + hlux[1] + hlux[2] + hlux[3];
        int num = stoi(str, nullptr, 16);

        // convert num to float
        union {
            float f;
            uint32_t i;
        } converter;
        converter.i = num;
        this->lux = converter.f;
       
    } catch  (const std::exception& e) {
        this->valid = false;
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

int HexRow::getId()
{
    return this->id;
};  

int HexRow::getTimestamp() {
    return this->timestamp;
}

int HexRow::getLocation() {
    return this->location;
}

float HexRow::getLux() {
    return this->lux;
}

bool HexRow::isvalid() {
    return this->valid;
}



std::string HexRow::getBright() {
    int loc = this->location;
 if (this->lux < MINLUX[loc]) return "dark";
 if (this->lux > MAXLUX[loc]) return "bright";
 return "good";
}

std::string HexRow::toCsv() {
    std::stringstream ss;

      ss<<this->id<<","
       <<timestampToTime(this->timestamp)<<","
       <<this->location<<","
       <<this->lux<<","
       <<this->getBright()<<"\n";

    return ss.str();
}

std::string timestampToTime(int timestamp) {
    std::time_t t = static_cast<std::time_t>(timestamp);
    std::tm tmStruct = *std::localtime(&t);

    // Format the time
    std::stringstream ss;
    ss << std::put_time(&tmStruct, "%Y:%m:%d %H:%M:%S");

    return ss.str();
}
