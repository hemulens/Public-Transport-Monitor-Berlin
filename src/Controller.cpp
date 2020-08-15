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
  std::vector<std::unique_ptr<Vehicle>> allVehicles;

  int nData;
  int nVehicles;
  web::json::value d;

  while (true) {
    data->Fetch();
    // std::cout << "Dataset size = " << data->GetData().size() << std::endl;
    // std::cout << "Time of update = " << std::chrono::system_clock::to_time_t(data->GetTime()) << std::endl;
    // std::cout << "***" << std::endl;
    nData = data->GetDataSize();
    nVehicles = allVehicles.size();
    d = data->GetData();
    // Update vehicles vector
    if (nVehicles > 0) {
      for (int i = 0; i < nVehicles; ++i) {
        // Find a vehicle with an ID of x
        for (int j = 0; j < nData; ++j) {
          if (allVehicles[i]->GetTripID() == d[j]["tripId"].serialize()) {
            // allVehicles[j]->Update(data->GetTime(), data->GetData(i));
            std::cout << "Vehicle " << allVehicles[i]->GetVehicleID() << " updated." << std::endl;
          } else {
            // std::cout << "I AM HERE!" << std::endl;
          }
        }
      }
    // Create vehicles and push to vector
    } else {
      for (int i = 0; i < nData; ++i) {
        // std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>();  
        // vehicle->Update(data->GetTime(), data->GetData(i));
        std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>(data->GetTime(), data->GetData(i));  
        // std::cout << "Vehicle's trip ID = " << vehicle->GetTripID() << std::endl;
        vehicle->PrintInstance();
        allVehicles.emplace_back(std::move(vehicle));
      }
    }
    // std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find(allVehicles.begin(), allVehicles.end(), [](){});

    // Stop watch
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "Speed of operation: " << duration << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}