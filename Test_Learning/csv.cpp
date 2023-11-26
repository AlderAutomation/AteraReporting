#include <iostream>
// #include <fstream> 
#include <string> 

#include "csv.h"

int CSV::open_csv() {
  outputFile.open(output_filename);

  if (!outputFile.is_open()) {
    std::cerr << "Failed to open the file " << output_filename << "\n";

    return 1; 
  }
  return 0;
}

void CSV::write_data(const std::string& data) {
  outputFile << data;
}

void CSV::close_csv() {
  outputFile.close();
}
