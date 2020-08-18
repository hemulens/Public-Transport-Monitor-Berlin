#include "PublicTransport.cpp"
// #include "Vehicle.cpp"

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

int main(int argc, char* argv[]) {
  // set timer
  std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
  PublicTransport transport;

  while (true) {
    transport.Run();
  }

  return 0;
}
