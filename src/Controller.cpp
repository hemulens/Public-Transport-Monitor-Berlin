#include "Vehicle.cpp"
// #include "ApiData.cpp"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {
  // set timer
  std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

  std::shared_ptr<Data> data = std::make_shared<Data>();
  data->Fetch();
  // std::cout << data.GetData()[0] << std::endl;
  std::cout << "Dataset size = " << data->GetData().size() << std::endl;
  std::cout << "Time of update = " << std::chrono::system_clock::to_time_t(data->GetTime()) << std::endl;
  std::cout << "***" << std::endl;
  
  // // web::json::value::is_null() test
  // int i = 0;
  // std::cout << "geo_altitude of plane [i] = " << data.GetStates()[i][states::sensors].serialize() << std::endl;

  std::vector<std::unique_ptr<Vehicle>> allVehicles;
  int jsonSize = data->GetData().size();
  for (int i = 0; i < jsonSize; i++) {
    // std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>();  
    // vehicle->Update(data->GetTime(), data->GetData(i));
    std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>(data->GetTime(), data->GetData(i));  
    // std::cout << "Vehicle's trip ID = " << vehicle->GetTripID() << std::endl;
    vehicle->PrintInstance();
    allVehicles.emplace_back(std::move(vehicle));
  }

  // Experiment with deletion of NEW on the heap + deallocation of smart pointers
  // std::unique_ptr<Aeroplane> aeroplane = std::make_unique<Aeroplane>();
  // Aeroplane *aeroplane2 = new Aeroplane();
  // std::cout << "Aeroplane instance counter = " << aeroplane->GetCounter() << std::endl;
  // delete aeroplane2;
  // std::cout << "Aeroplane instance counter = " << aeroplane->GetCounter() << std::endl;

  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

  std::cout << "Speed of operation: " << duration << std::endl;

  std::cout << "Trip ID = " << data->GetData()[0]["tripId"] << std::endl;

  return 0;
}