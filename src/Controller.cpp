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
  graphics->SetBgFilename("../data/berlin-xl-4.jpg"); 
  graphics->SetBgSize(2880, 1620);
  PublicTransport publicTransport;
  graphics->SetVehicles(publicTransport.GetVehiclesPtr());
  graphics->Simulate(publicTransport);

  return 0;
}
