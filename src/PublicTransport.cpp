#include "PublicTransport.h"


PublicTransport::PublicTransport() : _data(std::make_shared<Data>()) {
  _apiOutput = _data->GetDataPtr();
  _updateTime = _data->GetTimePtr();
}

std::vector<std::unique_ptr<Vehicle>> *PublicTransport::GetVehiclesPtr() {
  return &_vehicles;
}

void PublicTransport::Run() {
  // Send request and reset data
  _data->Fetch();  // There are two separate stopwatches inside this function
  // Init stopwatch (updating vehicles)
  std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
  _updated = 0;
  _created = 0;
  _deleted = 0;
  // Update vehicles vector if vector is not empty
  if (_vehicles.size() > 0) {
    // Update or add vehicles
    for (int i = 0; i < _apiOutput->size(); ++i) {
      // // Internal TEST for debugging: count frequency to find repeated TripIDs (requires over 60 milliseconds on dataset i = 500)
      // // Reason the test is needed – sometimes VBB server returns vehicles with duplicate IDs
      // int freq = std::count_if(_vehicles.begin(), _vehicles.end(), [this, i] (std::unique_ptr<Vehicle> &vehicle) {
      //   return vehicle->GetTripId() == (*this->_apiOutput)[i]["tripId"].as_string();
      // });
      // if (freq > 1) {
      //   std::cout << "ERROR!!! FREQUENCY = " << freq << ". TripID = " << _vehicles[i]->GetTripId() << std::endl;
      // }
      // // EOF TEST
      // Find a vehicle with an ID of x
      std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find_if(_vehicles.begin(), _vehicles.end(), [this, i](std::unique_ptr<Vehicle> &vehicle){
        return vehicle->GetTripId() == (*this->_apiOutput)[i]["tripId"].as_string();
      }); 
      // If found
      if (it != _vehicles.end()) {
        // Update vehicle's data and add vehicle's index to an index vector
        _vehicles[it - _vehicles.begin()]->Update(*_updateTime, (*_apiOutput)[i]);
        ++_updated;
      // If not found
      } else {
        // Create new vehicle based on the data object  
        _vehicles.emplace_back(std::make_unique<Vehicle>(*_updateTime, (*_apiOutput)[i]));
        ++_created;
      }
    }
    // Delete vehicles that went out of map:
    for (int i = 0; i < _vehicles.size(); ++i) {  // or use remove_if()
      if (_vehicles[i]->GetUpdateTime() != *_updateTime) {
        _vehicles.erase(_vehicles.begin() + i);
        ++_deleted;
        // i--;
      } 
    }
  // Create vehicles and push to vector if vector is empty
  } else {
    for (int i = 0; i < _apiOutput->size(); ++i) {
      _vehicles.emplace_back(std::make_unique<Vehicle>(*_updateTime, (*_apiOutput)[i]));
      ++_created;
    }
  }

  // End stopwatch
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
  
  std::cout << "Updated: " << _updated << std::endl;
  std::cout << "Created: " << _created << std::endl;
  std::cout << "Deleted: " << _deleted << std::endl;
  std::cout << "Vehicles size: " << _vehicles.size() << std::endl;
  std::cout << "Data size: " << _apiOutput->size() << std::endl;
  std::cout << "*-*-*" << std::endl;
  std::cout << duration << " milliseconds – updating vehicles" << std::endl;
}