#include <iostream>

// #include "csv.h"
#include "curl_handler.h"

int main () {
  // CSV csv_file;
  // csv_file.output_filename = "csv_class_test.csv";
  // csv_file.open_csv();
  // csv_file.write_data(std::string("Name,Age,Occupation\n"));
  // csv_file.write_data(std::string("Matt,38,Programmer\n"));
  // csv_file.close_csv();

  Curl_Handler myCurl; 
  
  std::cout << myCurl.init_curler("https://app.atera.com/api/v3/tickets?itemsInPage=5&ticketStatus=closed");
  


  return 0;
}