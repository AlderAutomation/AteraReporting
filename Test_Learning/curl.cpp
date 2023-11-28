#include <iostream>
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>



std::string readApiKey() {
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

int main () {
  // initialize lib curl 
  CURL* curl_handle;
  curl_handle = curl_easy_init();
  std::string BASE_URL = "https://app.atera.com/api/v3/tickets?itemsInPage=5&ticketStatus=closed";

  if (!curl_handle) {
    std::cout << "CURL init error";

    return 1;
  }

  // Setup the URL
  curl_easy_setopt(curl_handle, CURLOPT_URL, BASE_URL.c_str());

  // Setup Headers 
  struct curl_slist* headers = nullptr;
  headers = curl_slist_append(headers, "X-API-KEY: fef2a568b8a84c47aba735e179fbefa4");
  headers = curl_slist_append(headers, "Accept: application/json");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

  // Set the callback function
  std::string responseData;
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &responseData);

  // perform the request 
  CURLcode res = curl_easy_perform(curl_handle);

  if (res != CURLE_OK) {
    std::cout << "Error in the CURL response";

    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));  
    } else {
      try {
        // parse json response 
        json jsonResponse = json::parse(responseData);

        // std::cout << "Pretty Printed JSON Response: \n" << jsonResponse.dump(4) << std::endl;
        std::cout << std::setw(4) << jsonResponse << std::endl;
      } catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON Response: " << e.what() << std::endl;
      }
    }
  
  // Clean up libcurl
  curl_easy_cleanup(curl_handle);
  curl_slist_free_all(headers);

  return 0;
}