#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

#include <memory>
#include <string>

// namespaces used by CasaBlanca (CPPRESTSDK)
using namespace utility;               // Common utilities like string conversions
using namespace web;                   // Common features like URIs.
using namespace web::http;             // Common HTTP functionality
using namespace web::http::client;     // HTTP client features
using namespace concurrency::streams;  // Asynchronous streams

// enums to parse OpenSky data from api calls
enum ApiData { time_now, states };
enum States {
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

// api details
std::string domain{"https://opensky-network.org/"};
std::string path{"/api/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226"};


int main(int argc, char* argv[]) {
  std::shared_ptr<ostream> fileStream = std::make_shared<ostream>();

  // Open stream to output file.
  pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile) {
    *fileStream = outFile;

    // Create http_client to send the request.
    http_client client(U(domain));

    // Build request URI and start the request.
    uri_builder builder(U(path));
    // builder.append_query(U("q"), U("cpprestsdk github"));
    return client.request(methods::GET, builder.to_string());
  })

  // Handle response headers arriving.
  .then([=](http_response response) {
    printf("Received response status code:%u\n", response.status_code());

    // CHANGE: print the body
    std::cout << response.body() << std::endl;

    // Write response body into the file.
    return response.body().read_to_end(fileStream->streambuf());
  })

  // Close the file stream.
  .then([=](size_t) {
    return fileStream->close();
  });

  // Wait for all the outstanding I/O to complete and handle any exceptions
  try {
    requestTask.wait();
  } catch (const std::exception& e) {
    printf("Error exception:%s\n", e.what());
  }

  return 0;
}