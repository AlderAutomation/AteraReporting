#ifndef CURL_HANDLER_H
#define CURL_HANDLER_H

#include <iostream> 
#include <curl/curl.h>
#include <string>
#include <fstream>

class Curl_Handler {
  public: 
    std::string BASE_URL; 

    CURLcode init_curler(std::string BASE_URL);
    static size_t WriteCallbackStatic(void* contents, size_t size, size_t nmemb, std::string* output, void* user_ptr);
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
    std::string readApiKey();

  private: 

};

#endif 