#include "PublicTransport.h"


PublicTransport::PublicTransport() : _data(std::make_shared<Data>()) {
  _apiOutput = _data->GetDataPtr();
  _updateTime = _data->GetTimePtr();
}

std::vector<std::unique_ptr<Vehicle>> *PublicTransport::GetVehiclesPtr() {
  return &_vehicles;
}


void PublicTransport::Run() {
  // Reset variables
  _data->Fetch();
  _updated = 0;
  _created = 0;
  _deleted = 0;

  // Set timer
  std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
  // TODO: Add multithreading here to save time parsing JSON! – will not work, as the dataset is too small
  // TODO alternative: 
  // Update vehicles vector
  if (_vehicles.size() > 0) {
    // Update or add vehicles
    for (int i = 0; i < _apiOutput->size(); ++i) {
      // Internal TEST: count frequency
      int freq = std::count_if(_vehicles.begin(), _vehicles.end(), [this, i] (std::unique_ptr<Vehicle> &vehicle) {
        return vehicle->GetTripId() == (*this->_apiOutput)[i]["tripId"].as_string();
      });
      if (freq > 1) {
        std::cout << "ERROR!!! FREQUENCY = " << freq << std::endl;
      }
      // EOF TEST
      // Find a vehicle with an ID of x
      std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find_if(_vehicles.begin(), _vehicles.end(), [this, i] (std::unique_ptr<Vehicle> &vehicle) {
        return vehicle->GetTripId() == (*this->_apiOutput)[i]["tripId"].as_string();
      }); 
      // If found
      if (it != _vehicles.end()) {
        // Update vehicle's data and add vehicle's index to an index vector
        _vehicles[it - _vehicles.begin()]->Update(*_updateTime, (*_apiOutput)[i]);
        _updated++;
      // If not found
      } else {
        // Create new vehicle based on the data object  
        _vehicles.emplace_back(std::make_unique<Vehicle>(*_updateTime, (*_apiOutput)[i]));
        _created++;
      }
    }
    // Delete vehicles that went out of map:
    // 1. Get indexes of vehicles to be deleted
    std::vector<int> deleteIndex;;
    for (int i = 0; i < _vehicles.size(); ++i) {
      if (_vehicles[i]->GetUpdateTime() != *_updateTime) {
        deleteIndex.push_back(i);
      } 
    }
    // 2. Erase vehicle objects
    for (int i = 0; i < deleteIndex.size(); ++i) {
      _vehicles.erase(_vehicles.begin() + deleteIndex[i] - i);
      _deleted++;
    }
  // Create vehicles and push to vector
  } else {
    for (int i = 0; i < _apiOutput->size(); ++i) {
      // std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>(t, d[i]);  
      // vehicle->PrintInstance();
      _vehicles.emplace_back(std::make_unique<Vehicle>(*_updateTime, (*_apiOutput)[i]));
      _created++;
    }
  }
  // std::vector<std::unique_ptr<Vehicle>>::iterator it = std::find(allVehicles.begin(), allVehicles.end(), [](){});

  // Stop watch
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
  
  std::cout << "Updated: " << _updated << std::endl;
  std::cout << "Created: " << _created << std::endl;
  std::cout << "Deleted: " << _deleted << std::endl;
  std::cout << "Vehicles size: " << _vehicles.size() << std::endl;
  std::cout << "Data size: " << _apiOutput->size() << std::endl;
  std::cout << "Updating finished after " << duration << " milliseconds" << std::endl;
  std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
  // t0 = std::chrono::high_resolution_clock::now();
}