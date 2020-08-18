#include "Vehicle.cpp"
// #include "ApiData.cpp"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>

int main(int argc, char* argv[]) {
  // set timer
  std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

  std::shared_ptr<Data> data = std::make_shared<Data>();
  std::vector<std::unique_ptr<Vehicle>> vehicles;

  int nData;  // size of data
  web::json::value d;  // local copy of data (to speed up computations) (use std::move later)
  std::chrono::high_resolution_clock::time_point t;  // time when data was received

  while (true) {
    data->Fetch();
    d = std::move(data->GetData());
    nData = d.size();
    t = data->GetTime();

    // Update vehicles vector
    if (vehicles.size() > 0) {
      // Update or add vehicles
      for (int i = 0; i < nData; ++i) {
        // Find a vehicle with an ID of x
        std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find_if(vehicles.begin(), vehicles.end(), [&d, i] (std::unique_ptr<Vehicle> &vehicle) {
          return vehicle->GetTripId() == d[i]["tripId"].as_string();
        }); 
        // If data object exists in vehicles vector
        if (it != vehicles.end()) {
          // Update vehicle's data and add vehicle's index to an index vector
          int vehicleIndex = it - vehicles.begin();
          vehicles[vehicleIndex]->Update(t, d[i]);
        } else {
          // Create new vehicle based on the data object  
          vehicles.emplace_back(std::move(std::make_unique<Vehicle>(t, d[i])));
        }
        // std::cout << "ITERATOR = " << (it - vehicles.begin()) << std::endl;  // delete later
      }
      // Delete vehicles that went out of map
      // 1. Get indexes of vehicles to be deleted
      std::vector<int> deleteIndex {};
      for (int i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i]->GetUpdateTime() != t) {
          deleteIndex.push_back(i);
        } 
      }
      // 2. Erase vehicle objects
      for (int i = 0; i < deleteIndex.size(); ++i) {
        vehicles.erase(vehicles.begin() + deleteIndex[i] - i);
      }
    // Create vehicles and push to vector
    } else {
      for (int i = 0; i < nData; ++i) {
        // std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>();  
        // vehicle->Update(data->GetTime(), data->GetData(i));
        std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>(t, d[i]);  
        // std::cout << "Vehicle's trip ID = " << vehicle->GetTripID() << std::endl;
        vehicle->PrintInstance();
        vehicles.emplace_back(std::move(vehicle));
      }
    }
    // std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find(allVehicles.begin(), allVehicles.end(), [](){});

    // Stop watch
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "Speed of operation: " << duration << std::endl;
    std::cout << "Vehicles vector size: " << vehicles.size() << std::endl;
    std::cout << "Data size: " << d.size() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}



// for (int j = 0; j < vehicles.size(); ++j) {
//   // When equals obj i = obj j, update vehicle
//   if (d[i]["tripId"].as_string() == vehicles[j]->GetTripId()) {
//     web::json::value dI = data->GetData(i);
//     vehicles[j]->Update(t, dI);
//     std::cout << "VEHICLE " << vehicles[j]->GetVehicleId() << " UPDATED." << std::endl;
//     // add a mark to a special variable to NOT move (delete) this object from the vector?
//     break;
//   }
// }