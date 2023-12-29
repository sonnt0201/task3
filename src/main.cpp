#include "../include/MyIO.hpp"
#include "../include/Converters.hpp"
#include "../include/Logger.hpp"
#include <chrono>
// g++ main.cpp MyIO.cpp Converters.cpp Logger.cpp -o ../bin/lux_comm
// ./lux_comm lux_condition_test3.csv out.dat
int main(int argv, char **argc)
{

  // test for hexrow
  // HexRow row = HexRow("a0 0e 01 65 84 ed a0 02 44 b4 86 b8 43 a9");

  // // cout all row values
  // std::cout<<row.toCsv()<<std::endl;
  auto start = std::chrono::high_resolution_clock::now();

  MyIO io = MyIO(argv, argc);

  if (io.inputType == ENCODE)
  {
    Converters con = Converters(io.iFile, io.oFile);
    con.csvToDat();

    // Counting time
    time_t now = time(0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << ctime(&now);
    std::cout << "Finish creating \"" << io.oFile << "\" in "
              << duration.count() << " millisec(s)." << std::endl
              << "Open task3.log to see error(s)."
              << std::endl;

    return 0;
  }

  if (io.inputType == DECODE)
  {
    Converters con = Converters(io.iFile, io.oFile);
    con.datToCsv();

    // Counting time
    time_t now = time(0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << ctime(&now);
    std::cout << "Finish creating \"" << io.oFile << "\" in "
              << duration.count() << " millisec(s)." << std::endl
              << "Open task3.log to see error(s)."
              << std::endl;

    return 0;
  }

  logError(ERROR_COMMAND);

  // Counting time
  time_t now = time(0);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << ctime(&now);
  std::cout << "Failed to handle command line." << std::endl
            << "Open task3.log to see error(s)."
            << std::endl;

  return 0;
}