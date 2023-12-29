#include "../include/MyIO.hpp"
#include "../include/Converters.hpp"

// g++ main.cpp MyIO.cpp Converters.cpp -o ../bin/lux_comm
// ./lux_comm lux_condition_test3.csv out.dat
int main(int argv, char** argc) {
   
  // test for hexrow
  HexRow row = HexRow("A0 0E 02 65 4E 6F A0 02 43 C8 03 D7 47 A9");

  // cout all row values
  std::cout<<row.getId()<<std::endl
  <<row.getTimestamp()<<std::endl
  <<row.getLocation()<<"\n"
  <<row.getLux()<<std::endl;
  ;


  // MyIO io = MyIO(argv, argc);

  // if (io.inputType == ENCODE) {
  //   Converters con = Converters(io.iFile, io.oFile);
  //   con.csvToDat();
  // }

  return 0;
 

}