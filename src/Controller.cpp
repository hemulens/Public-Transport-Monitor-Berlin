// #include "PublicTransport.cpp"
// #include "Vehicle.cpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "Graphics.h"

// OLD

// int main(int argc, char* argv[]) {
//   // set timer
//   std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
//   PublicTransport publicTransport;

//   while (true) {
//     publicTransport.Run();
//   }

//   return 0;
// }
// EOF OLD

// Paris
void createTrafficObjects(std::vector<std::unique_ptr<Vehicle>> &vehicles, std::string &filename, int nVehicles) {
  // assign filename of corresponding city map
  filename = "../data/berlin-lg.png";

  // // add vehicles to streets
  // for (size_t nv = 0; nv < nVehicles; nv++)
  // {
  //     vehicles.push_back(std::make_shared<Vehicle>());
  //     vehicles.at(nv)->setCurrentStreet(streets.at(nv));
  //     vehicles.at(nv)->setCurrentDestination(intersections.at(8));
  // }
}

/* Main function */
int main() {
  /* PART 1 : Set up traffic objects */

  // create and connect intersections and streets
  std::vector<std::unique_ptr<Vehicle>> vehicles;
  std::string backgroundImg;
  int nVehicles = 6;
  createTrafficObjects_Paris(streets, intersections, vehicles, backgroundImg, nVehicles);

  /* PART 2 : simulate traffic objects */

  // simulate intersection
  std::for_each(intersections.begin(), intersections.end(), [](std::shared_ptr<Intersection> &i) {
    i->simulate();
  });

  // simulate vehicles
  std::for_each(vehicles.begin(), vehicles.end(), [](std::shared_ptr<Vehicle> &v) {
    v->simulate();
  });

  /* PART 3 : Launch visualization */

  // add all objects into common vector
  std::vector<std::shared_ptr<TrafficObject>> trafficObjects;
  std::for_each(intersections.begin(), intersections.end(), [&trafficObjects](std::shared_ptr<Intersection> &intersection) {
    std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(intersection);
    trafficObjects.push_back(trafficObject);
  });

  std::for_each(vehicles.begin(), vehicles.end(), [&trafficObjects](std::shared_ptr<Vehicle> &vehicles) {
    std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(vehicles);
    trafficObjects.push_back(trafficObject);
  });

  // draw all objects in vector
  Graphics *graphics = new Graphics();
  graphics->setBgFilename(backgroundImg);
  graphics->setTrafficObjects(trafficObjects);
  graphics->simulate();
}
