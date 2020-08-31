// #include "PublicTransport.cpp"
// #include "Vehicle.cpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "Graphics.cpp"


int main() {
  // Draw all objects in vector
  Graphics *graphics = new Graphics();
  graphics->SetBgFilename("../data/berlin-lg.png");
  PublicTransport publicTransport;
  // graphics->SetVehicles(publicTransport.GetVehiclesPtr());
  graphics->Simulate(publicTransport);

  // // set timer
  // std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

  // while (true) {
  //   publicTransport.Run();
  // }

  return 0;
}
