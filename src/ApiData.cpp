// #include <vector>
#include <iostream>

#include "ApiData.h"

Data::Data() : _time(std::chrono::high_resolution_clock::now()),
               _client(U(domain)),  // Initialize http_client prior to sending a request – web::http::client::http_client _client(U(domain));
               _builder(U(path)) {  // Initialize request URI and start the request – web::http::uri_builder _builder(U(path));
  // Append queries – more info: https://github.com/derhuerst/vbb-rest/blob/5/docs/api.md#get-radar
  _builder.append_query(U("north"), U(geo["north"]));
  _builder.append_query(U("west"), U(geo["west"]));
  _builder.append_query(U("south"), U(geo["south"]));
  _builder.append_query(U("east"), U(geo["east"]));
  // Set max number of vehicles in JSON
  _builder.append_query(U("results"), U(1000));
  // Set duration for computing frames
  // _builder.append_query(U("duration"), U(1));
  // Set max number of frames per vehicle
  // _builder.append_query(U("frames"), U(0));
}

void Data::Fetch() {
  // Run requestTask and wait for all the outstanding I/O to complete and handle any exceptions
  // Init stopwatch (data fetching)
  std::chrono::high_resolution_clock::time_point t0_fetch = std::chrono::high_resolution_clock::now();
  try {
    // RequestTask().wait();
    pplx::create_task([=] {
      // Formulate request
      return _client.request(web::http::methods::GET, _builder.to_string());
    })
    // Handle response headers arriving
    .then([=](web::http::http_response response) {
      printf("Received response status code: %u\n", response.status_code());
      // Response body -> return json
      return response.extract_json();
    })
    .then([this, t0_fetch](web::json::value data){
      // End stopwatch (fetching)
      std::chrono::high_resolution_clock::time_point t1_fetch = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1_fetch - t0_fetch).count();
      std::cout << duration << " milliseconds – fetching data" << std::endl;
      // Parse json object
      // Init stopwatch ()
      std::chrono::high_resolution_clock::time_point t0_update = std::chrono::high_resolution_clock::now();
      if (!data.is_null()) {
        this->Update(std::move(data));  // JSON for 500 vehicles weighs approx. 3.2 MB 😱
        // End stopwatch (fetching)
        std::chrono::high_resolution_clock::time_point t1_update = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1_update - t0_update).count();
        std::cout << duration << " milliseconds – updating data" << std::endl;
        std::cout << "*-*-*" << std::endl;
        return;
      }
      std::cout << "Data unavailable: returned emply JSON" << std::endl;  // throw exception instead
      return;
    })
    .wait();
  } catch (const std::exception &e) {
    printf("Error exception: %s\n", e.what());
  }  
}

void Data::Update(const web::json::value &&data) {
  _data = data;
  _time = std::chrono::high_resolution_clock::now();
  // std::cout << "_data updated" << std::endl;
  return;
}

std::chrono::high_resolution_clock::time_point Data::GetTime() {
  return _time;
}

std::chrono::high_resolution_clock::time_point *Data::GetTimePtr() {
  return &_time;
}

web::json::value Data::GetData() {
  return _data;
}

web::json::value Data::GetData(const int index) {
  return _data[index];
}

web::json::value *Data::GetDataPtr() {
  return &_data;
}

int Data::GetDataSize() {
  return _data.size();
};