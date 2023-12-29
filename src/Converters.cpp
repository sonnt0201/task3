#include "../include/Converters.hpp"

Converters::Converters(std::string iFileName, std::string oFileName)
{
    this->iFileName = iFileName;
    this->oFileName = oFileName;
};

void Converters::csvToDat() {

    std::ifstream iFile(this->iFileName);
    std::ofstream oFile(this->oFileName);
    // Check if the file is open
    if (!iFile.is_open() || !oFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }


    // read each line
    std::string line = "";
    bool firstRow = true;
    while (std::getline(iFile, line)) {
        if (firstRow) {firstRow = false; continue;}
        Record record = Record(line);
        if (!record.isvalid()) continue;
        oFile<<record.toHex()<<"\n";
    }



}
void Converters::datToCsv()
{
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
    out << this->checkSum() << " "
        << "a9";
    return out.str();
}

HexRow::HexRow(std::string row) {
    this->valid = true;
    const int rowlen = 43;
    if (row.length() != rowlen) {this->valid = false; return;}
    std::string hstart, hlen, hid, htime[4], hlocation, hlux[4];
    std::stringstream ss(row);

    ss>>hstart>>hlen>>hid
    >>htime[0]>>htime[1]>>htime[2]>>htime[3]
    >>hlocation
    >>hlux[0]>>hlux[1]>>hlux[2]>>hlux[3];

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
        }
        converter;
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

