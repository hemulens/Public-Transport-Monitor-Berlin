#ifndef APIDATA_H
#define APIDATA_H

#ifdef __APPLE__
  #include <string.h>
  #include <xlocale.h>
#endif

#include <cpprest/http_client.h>
#include <cpprest/json.h>  // casablanca's json parser

#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <memory>

// API details:
const utility::string_t domain{"https://v5.vbb.transport.rest/"};
const utility::string_t path{"/radar"};

// Map coordinates:
std::map<utility::string_t, double> geo {
  std::make_pair("north", 52.557396),
  std::make_pair("west", 13.287704),
  std::make_pair("south", 52.483175),
  std::make_pair("east", 13.505750)
  // Another experimental map set (smaller)
  // std::make_pair("north", 52.525562),
  // std::make_pair("west", 13.348276),
  // std::make_pair("south", 52.503455),
  // std::make_pair("east", 13.413168)
}; 

class Data {
  public:
    // Constructors
    Data();
    // Getters/setters
    void Fetch();
    void Update(web::json::value &&data);
    web::json::value GetData();
    web::json::value GetData(const int index);
    int GetDataSize();
    std::chrono::system_clock::time_point GetTime();
  private:
    // HTTP variables
    web::http::client::http_client _client;
    web::http::uri_builder _builder;
    // Data variables
    std::chrono::system_clock::time_point _time;
    web::json::value _data;
};

#endif /* APIDATA_H */