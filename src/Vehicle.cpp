#include "Vehicle.h"

// Templates to parse data and protect types against NULL
template <typename Type>
void Assign(Type &variable, web::json::value &data) {
  variable = data;  // conversion for web::json::value
}
// Template specializations
template <>
void Assign(int &variable, web::json::value &data) {
  if (data.is_null()) {
    variable = 0;
    return;
  }
  variable = data.as_integer();
}
template <>
void Assign(double &variable, web::json::value &data) {
  if (data.is_null()) {
    variable = 0.0;
    return;
  }
  variable = data.as_double();
}
void Assign(bool &variable, web::json::value &data) {
  if (data.is_null()) {
    variable = false;
    return;
  }
  data.as_bool();
}
template <>
void Assign(std::string &variable, web::json::value &data) {
  variable = data.serialize();
}

// Initialize static Vehicle counter
int Vehicle::_idCtr = 0;

// Initialize object with default or null values
Vehicle::Vehicle() : _tripId("undefined"), 
                     _updatedAt(std::chrono::system_clock::now()) {
  _id = _idCtr++;
  std::cout << "Vehicle " << _id << " created" << std::endl;
}

Vehicle::Vehicle(std::chrono::system_clock::time_point time, web::json::value data) {
  // Set variables
  this->Update(time, data);
  // Update counter
  _id = _idCtr++;
  std::cout << "Vehicle " << _id << " created" << std::endl;
}

// Destructor
Vehicle::~Vehicle() {
  // std::cout << "Vehicle " << _id << " deleted" << std::endl;
  _id = _idCtr--;
}

// Getters
int Vehicle::GetVehicleID() {
  return _id;
}
int Vehicle::GetVehicleCounter() {
  return _idCtr;
}
std::string Vehicle::GetTripID() {  // temporary 
  return _tripId;
}

void Vehicle::PrintInstance() {  // temporary 
  std::cout << "Vehicle id = " << _id << std::endl;
  std::cout << "_tripId = " << _tripId << std::endl;
  std::cout << "_mode = " << _mode << std::endl;
  std::cout << "_product = " << _product << std::endl;
  std::cout << "_metro = " << _metro << std::endl;
  std::cout << "_latitude = " << _latitude << std::endl;
  std::cout << "_longitude = " << _longitude << std::endl;
  std::cout << "_updatedAt = " << std::chrono::system_clock::to_time_t(_updatedAt) << std::endl;
  std::cout << "***" << std::endl;
}

// Setters
void Vehicle::Update(std::chrono::system_clock::time_point &time, web::json::value &data) {
  // API data variables
  Assign(_tripId, data["tripId"]);
  Assign(_mode, data["line"]["mode"]);
  Assign(_product, data["line"]["product"]);
  Assign(_metro, data["line"]["metro"]);
  Assign(_latitude, data["location"]["latitude"]);
  Assign(_longitude, data["location"]["longitude"]);
  // Time of the last update
  if (_updatedAt != time) {
    _updatedAt = time;
  }
}

