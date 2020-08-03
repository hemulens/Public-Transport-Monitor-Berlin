#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>

int main() {
  auto fileStream = std::make_shared<ostream>();

  // Open stream to output file.
  pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile) {
    *fileStream = outFile;
  });

  return 0;
}