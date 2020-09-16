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
  // Experimental map set 1: https://www.google.com/maps/@52.5074075,13.3471116,14.41z
  std::make_pair("north", 52.523554), 
  std::make_pair("west", 13.300639),
  std::make_pair("south", 52.491885),
  std::make_pair("east", 13.393520)
  // Experimental map set 2: https://www.google.com/maps/place/Berlin,+Germany/@52.5051999,13.3392366,16z/data=!4m5!3m4!1s0x47a84e373f035901:0x42120465b5e3b70!8m2!3d52.5200066!4d13.404954
  // std::make_pair("north", 52.510535),
  // std::make_pair("west", 13.323787),
  // std::make_pair("south", 52.500034),
  // std::make_pair("east", 13.354665)
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
    web::json::value *GetDataPtr();
    int GetDataSize();
    std::chrono::high_resolution_clock::time_point GetTime();
    std::chrono::high_resolution_clock::time_point *GetTimePtr();
  private:
    // HTTP variables
    web::http::client::http_client _client;
    web::http::uri_builder _builder;
    // Data variables
    std::chrono::high_resolution_clock::time_point _time;
    web::json::value _data;
};

#endif /* APIDATA_H */