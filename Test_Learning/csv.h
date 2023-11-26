#ifndef CSV_H
#define CSV_H

#include <string> 
#include <fstream>

class CSV { 
  public: 
    std::ofstream outputFile;
    std::string output_filename;

    int open_csv();
    void write_data(const std::string& data);
    void close_csv();


};

#endif