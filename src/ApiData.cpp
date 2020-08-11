// #include <vector>
#include <map>
#include <iostream>

#include "ApiData.h"

Data::Data() : _time(0) {}

pplx::task<void> Data::Request() {
  // Declare HTTP request:
  return pplx::create_task([=] {
    // Create http_client to send the request
    web::http::client::http_client client(U(domain));
    // Build request URI and start the request
    web::http::uri_builder builder(U(path));
    // Append queries
    builder.append_query(U("lamin"), U(geo["lamin"]));
    builder.append_query(U("lomin"), U(geo["lomin"]));
    builder.append_query(U("lamax"), U(geo["lamax"]));
    builder.append_query(U("lomax"), U(geo["lomax"]));
    return client.request(web::http::methods::GET, builder.to_string());
  })
  // Handle response headers arriving
  .then([=](web::http::http_response response) {
    if (response.status_code() == web::http::status_codes::OK) {
      printf("Received response status code: %u\n", response.status_code());
      // Response body -> return json
      return response.extract_json();
    }
    // Response body -> wait to return json
    return pplx::create_task([] {
      return web::json::value();
    });
  })
  .then([this](web::json::value data){
    // Parse json object
    if (data.is_null()) {
      std::cout << "Data unavailable: returned emply JSON" << std::endl; 
      return;
    }
    // std::cout << data << std::endl;  // print JSON object
    // std::string time = data["time"];
    // this->_time = stoi(data[api_data::t].serialize());  // create a separate setter?
    // std::cout << "TIME: " << data["time"] << std::endl;
    // this->_states = data[api_data::states];
    // std::cout << data["states"][0][states::longitude] << std::endl;
    this->UpdateData(data);
    return;
  });
  // .then([](){
  //   std::cout << "success" << std::endl; 
  // });
}

void Data::Init() {
  // Run requestTask and wait for all the outstanding I/O to complete and handle any exceptions
  // ADD WHILE LOOP
  try {
    Request().wait();
  } catch (const std::exception &e) {
    printf("Error exception: %s\n", e.what());
  }  
}

void Data::UpdateData(web::json::value &data) {
  int t = stoi(data["time"].serialize());
  web::json::value st = data["states"];
  if (_time != t) {
    _time = t;
    _states = st;
    std::cout << "_time and _states updated" << std::endl;
    return;
  }
  std::cout << "_time and _states NOT updated" << std::endl;
}

int Data::GetTime() {
  return _time;
}

web::json::value Data::GetStates() {
  return _states;
}