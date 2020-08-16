// #include <vector>
#include <iostream>

#include "ApiData.h"

Data::Data() : _time(std::chrono::system_clock::now()),
               _client(U(domain)),  // Initialize http_client prior to sending a request – web::http::client::http_client _client(U(domain));
               _builder(U(path)) {  // Initialize request URI and start the request – web::http::uri_builder _builder(U(path));
  // Append queries – more info: https://github.com/derhuerst/vbb-rest/blob/5/docs/api.md#get-radar
  _builder.append_query(U("north"), U(geo["north"]));
  _builder.append_query(U("west"), U(geo["west"]));
  _builder.append_query(U("south"), U(geo["south"]));
  _builder.append_query(U("east"), U(geo["east"]));
  // Set max number of vehicles in JSON
  _builder.append_query(U("results"), U(700));
  // Set duration for computing frames
  _builder.append_query(U("duration"), U(0));
  // Set max number of frames per vehicle
  _builder.append_query(U("frames"), U(0));
}

void Data::Fetch() {
  // Run requestTask and wait for all the outstanding I/O to complete and handle any exceptions
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
    .then([this](web::json::value data){
      // Parse json object
      if (!data.is_null()) {
        this->Update(std::move(data));
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

void Data::Update(web::json::value &&data) {
  if (data.is_null()) {
   std::cout << "_data NOT updated – 'data is NULL'" << std::endl;
   return;
  }
  _data = data;
  _time = std::chrono::system_clock::now();
  std::cout << "_data updated" << std::endl;
  return;
}

std::chrono::system_clock::time_point Data::GetTime() {
  return _time;
}

web::json::value Data::GetData() {
  return _data;
}

web::json::value Data::GetData(const int index) {
  return _data[index];
}

int Data::GetDataSize() {
  return _data.size();
};