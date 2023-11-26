#include <iostream>

#include "csv.h"

int main () {
  CSV csv_file;
  csv_file.output_filename = "csv_class_test.csv";
  csv_file.open_csv();
  csv_file.write_data(std::string("Name,Age,Occupation\n"));
  csv_file.write_data(std::string("Matt,38,Programmer\n"));
  csv_file.close_csv();


  return 0;
}