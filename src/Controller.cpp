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

  int nData;
  int nVehicles;
  web::json::value d;
  std::chrono::system_clock::time_point t;

  while (true) {
    data->Fetch();
    // std::cout << "Dataset size = " << data->GetData().size() << std::endl;
    // std::cout << "Time of update = " << std::chrono::system_clock::to_time_t(data->GetTime()) << std::endl;
    // std::cout << "***" << std::endl;
    nData = data->GetDataSize();
    nVehicles = vehicles.size();
    d = data->GetData();
    t = data->GetTime();

    // Update vehicles vector
    if (nVehicles > 0) {
      for (int i = 0; i < nData; ++i) {
        // Find a vehicle with an ID of x
        std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find_if(vehicles.begin(), vehicles.end(), [&d, i] (std::unique_ptr<Vehicle> &v) {
          return v->GetTripId() == d[i]["tripId"].as_string();
        });
        if (it == vehicles.end()) {
          std::cout << "ERROR!!! = " << (it - vehicles.begin()) << std::endl;  // Data object does not exist in the vehicles vector 
        }
        std::cout << "ITERATOR = " << (it - vehicles.begin()) << std::endl;
        // std::cout << "OBJ ID (IT) = " << vehicles[it-vehicles.begin()]->GetTripId() << std::endl;

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
      }
    // Create vehicles and push to vector
    } else {
      for (int i = 0; i < nData; ++i) {
        // std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>();  
        // vehicle->Update(data->GetTime(), data->GetData(i));
        std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>(data->GetTime(), data->GetData(i));  
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
    std::cout << "Vector size: " << vehicles.size() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
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