#include <cstddef>
#include <string>
#include <fstream> 
#include <curl/curl.h>
#include <iostream>

#include "curl_handler.h"


size_t Curl_Handler::WriteCallbackStatic(void* contents, size_t size, size_t nmemb, std::string* output, void* user_ptr) {
    return static_cast<Curl_Handler*>(user_ptr)->WriteCallback(contents, size, nmemb, output);
}


size_t Curl_Handler::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}


std::string Curl_Handler::readApiKey () {
  std::ifstream file("secrets.txt");
  std::string apiKey;

  if (file.is_open()) {
    std::string line; 
    while (std::getline(file, line)) {
      size_t pos = line.find('=');
      if (pos != std::string::npos) {
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        if (key == "API_KEY") {
          apiKey = value;
          break;
        }
      }
    }
    file.close();
  }
  return apiKey;
}


CURLcode Curl_Handler::init_curler(std::string BASE_URL) {
  CURL* curl_handle;
  curl_handle = curl_easy_init();
  const std::string API_KEY = readApiKey();

  if (!curl_handle) {
    throw std::runtime_error("CURL initialization error");

  }

  // Setup the URL
  curl_easy_setopt(curl_handle, CURLOPT_URL, BASE_URL.c_str());

  // Debugging connection, REMOVE for prod
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

  // Setup Headers 
  struct curl_slist* headers = nullptr;
  headers = curl_slist_append(headers, ("X-API-KEY: " + API_KEY).c_str());
  headers = curl_slist_append(headers, "Accept: application/json");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

  // Set the callback function
  std::string responseData;
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, &Curl_Handler::WriteCallbackStatic);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &responseData);

  // perform the request 
  CURLcode res = curl_easy_perform(curl_handle);

  // Clean up 
  curl_slist_free_all(headers);


  return res;
}
