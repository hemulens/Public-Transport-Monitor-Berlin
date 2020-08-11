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

// namespaces used by CasaBlanca (CPPRESTSDK)
// using namespace utility;               // Common utilities like string conversions
// using namespace web;                   // Common features like URIs.
// using namespace web::http;             // Common HTTP functionality
// using namespace web::http::client;     // HTTP client features
// using namespace concurrency::streams;  // Asynchronous streams (writing to files)

// API details:
utility::string_t domain{"https://opensky-network.org/"};
utility::string_t path{"/api/states/all"};
// std::string path{"/api/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226"};  

// Map coordinates:
std::map<utility::string_t, double> geo {
  std::make_pair("lamin", 45.8389),
  std::make_pair("lomin", 5.9962),
  std::make_pair("lamax", 47.8229),
  std::make_pair("lomax", 10.5226)
};

// enums to parse OpenSky data from api calls
// enum api_data {
//   t,  // The time which the state vectors in this response are associated with. All vectors represent the state of a vehicle with the interval [time−1,time].
//   states  // The state vectors.
// };
enum states {
  icao24,  // Unique ICAO 24-bit address of the transponder in hex string representation.
  callsign,  // Callsign of the vehicle (8 chars). Can be null if no callsign has been received.
  origin_country, // Country name inferred from the ICAO 24-bit address.
  time_position,  // Unix timestamp (seconds) for the last position update. Can be null if no position report was received by OpenSky within the past 15s.
  last_contact,  // Unix timestamp (seconds) for the last update in general. This field is updated for any new, valid message received from the transponder.
  longitude,  // WGS-84 longitude in decimal degrees. Can be null.
  latitude,  // WGS-84 latitude in decimal degrees. Can be null.
  baro_altitude,  // Barometric altitude in meters. Can be null.
  on_ground,  // Boolean value which indicates if the position was retrieved from a surface position report.
  velocity,  // Velocity over ground in m/s. Can be null.
  true_track,  // True track in decimal degrees clockwise from north (north=0°). Can be null.
  vertical_rate,  // Vertical rate in m/s. A positive value indicates that the airplane is climbing, a negative value indicates that it descends. Can be null.
  sensors,  // IDs of the receivers which contributed to this state vector. Is null if no filtering for sensor was used in the request.
  geo_altitude,  // Geometric altitude in meters. Can be null.
  squawk,  // The transponder code aka Squawk. Can be null.
  spi,  // Whether flight status indicates special purpose indicator.
  position_source  // Origin of this state’s position: 0 = ADS-B, 1 = ASTERIX, 2 = MLAT
};

class Data {
  public:
    // Constructors
    Data();
    // Getters/setters
    void Init();
    pplx::task<void> Request();
    void UpdateData(web::json::value &data);
    int GetTime();
    web::json::value GetStates();
  private:
    // HTTP request task declaration
    // pplx::task<void> _requestTask;
    // API data
    int _time;
    web::json::value _states;
};

#endif /* APIDATA_H */