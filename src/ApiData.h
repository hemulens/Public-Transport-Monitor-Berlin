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
  // To use other maps, please 1) choose and uncomment any desired coordinate sets, 2) in Controller.cpp change the file name and img resolution. Example: map set 2 requires img file "berlin-md-2.jpg" with resolution 2880 × 1624 px
  // Experimental map set 1: https://www.google.com/maps/place/Berlin,+Germany/@52.5051999,13.3392366,16z/data=!4m5!3m4!1s0x47a84e373f035901:0x42120465b5e3b70!8m2!3d52.5200066!4d13.404954
  // std::make_pair("north", 52.510535),
  // std::make_pair("west", 13.323787),
  // std::make_pair("south", 52.500034),
  // std::make_pair("east", 13.354665)
  // Experimental map set 2: https://www.google.com/maps/@52.5074075,13.3471116,14.41z
  // std::make_pair("north", 52.523554), 
  // std::make_pair("west", 13.300639),
  // std::make_pair("south", 52.491885),
  // std::make_pair("east", 13.393520)
  // Experimental map set 3: https://www.google.com/maps/@52.5360627,13.3619777,13.29z
  // std::make_pair("north", 52.571106),
  // std::make_pair("west", 13.260888),
  // std::make_pair("south", 52.502273),
  // std::make_pair("east", 13.462927)
  // Experimental map set 4: https://www.google.com/maps/dir/52.565727,+13.254447/52.465946,+13.546986/@52.5151224,13.4008417,12.75z/data=!4m9!4m8!1m3!2m2!1d13.254447!2d52.565727!1m3!2m2!1d13.546986!2d52.465946
  std::make_pair("north", 52.565727),
  std::make_pair("west", 13.254447),
  std::make_pair("south", 52.465946), 
  std::make_pair("east", 13.546986)
}; 

class Data {
  public:
    // Constructors
    Data();
    // Getters/setters
    void Fetch();
    void Update(const web::json::value &&data);
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