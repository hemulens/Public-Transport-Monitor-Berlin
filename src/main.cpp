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


// API details:
std::string domain{"https://opensky-network.org/"};
// std::string path{"/api/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226"};
std::string path{"/api/states/all"};

// Map coordinates:
std::string map_lamin = "45.8389";
std::string map_lomin = "5.9962";
std::string map_lamax = "47.8229";
std::string map_lomax = "10.5226";


int main(int argc, char* argv[]) {
  std::shared_ptr<ostream> fileStream = std::make_shared<ostream>();

  // Open stream to output file.
  pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile) {
    *fileStream = outFile;

    // Create http_client to send the request.
    http_client client(U(domain));
    std::cout << "app works" << std::endl;
    // Build request URI and start the request.
    uri_builder builder(U(path));
    // builder.append_query(U("q"), U("cpprestsdk github"));
    builder.append_query(U("lamin"), U(map_lamin));
    builder.append_query(U("lomin"), U(map_lomin));
    builder.append_query(U("lamax"), U(map_lamax));
    builder.append_query(U("lomax"), U(map_lomax));
    return client.request(methods::GET, builder.to_string());
  })

  // Handle response headers arriving.
  .then([=](http_response response) {
    printf("Received response status code: %u\n", response.status_code());

    // CHANGE: print the body
    pplx::task<utility::string_t> stringified_body = response.extract_string();
    // convert to utf-8 string
    std::cout << "response body:" << response.body() << std::endl;

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