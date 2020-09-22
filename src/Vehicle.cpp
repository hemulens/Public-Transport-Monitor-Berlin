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
template <>
void Assign(bool &variable, web::json::value &data) {
  if (data.is_null()) {
    variable = false;
    return;
  }
  data.as_bool();
}
template <>
void Assign(std::string &variable, web::json::value &data) {
  variable = data.as_string();
}
template <>
void Assign(VehicleType &variable, web::json::value &data) { 
  // Temporary variables for the sake of DRY
  std::string mode = data["mode"].as_string();  // See comments near enum VehicleType in Vehicle.h to understand what the keys "mode" and "product" describe
  std::string product = data["product"].as_string();
  if (mode == "bus") {
    variable = VehicleType::bus;
  } else if (mode == "train") {
    if (product == "tram") {
      variable = VehicleType::tram;
    } else if (product == "subway") {
      variable = VehicleType::subwayTrain;
    } else if (product == "suburban") {
      variable = VehicleType::suburbanTrain;
    } else if (product == "express") {
      variable = VehicleType::expressTrain;
    } else if (product == "regional") {
      variable = VehicleType::regionalTrain;
    }
  } else if (mode == "watercraft") {
    if (product == "ferry") {
      variable = VehicleType::ferry;
    }  // other watercrafts (to be added)
  } else {
    std::cout << "NULL vehcile! Mode = " << mode << "; Product = " << product << std::endl;  // for debugging
    variable = VehicleType::null;
  }
}


// Initialize static Vehicle counter
int Vehicle::_idCounter = 0;

// Initialize object with default or null values
Vehicle::Vehicle() : _type(VehicleType::null),
                     _tripId("null"), 
                     _updatedAt(std::chrono::high_resolution_clock::now()) {
  _id = ++_idCounter;
  // std::cout << "Vehicle " << _id << " created" << std::endl;
}

Vehicle::Vehicle(std::chrono::high_resolution_clock::time_point time, web::json::value data) : _updatedAt(time) {
  // Set variables
  this->Update(time, data);
  // Update counter
  _id = ++_idCounter;
  // std::cout << "Vehicle " << _id << " created" << std::endl;
}

// Destructor
Vehicle::~Vehicle() {
  // std::cout << "Vehicle " << _id << " deleted" << std::endl;
  _id = --_idCounter;
}

// Getters
int Vehicle::GetVehicleId() {
  return _id;
}
int Vehicle::GetVehicleCounter() {
  return _idCounter;
}
std::string Vehicle::GetTripId() {  // temporary 
  return _tripId;
}
std::chrono::high_resolution_clock::time_point Vehicle::GetUpdateTime() {
  return _updatedAt;
}


// Geo position normalization
void Vehicle::GetNormalizedPosition(double &lon, double &lat, int resX, int resY) {
  lat = resY - (_latitude - geo["south"]) / (geo["north"] - geo["south"]) * resY;  // In OpenCV, Y is computed counterclockwise
  lon = (_longitude - geo["west"]) / (geo["east"] - geo["west"]) * resX;
}

void Vehicle::PrintInstance() {  // temporary 
  std::cout << "_id = " << _id << std::endl;
  std::cout << "_type = " << _type << std::endl;
  std::cout << "_tripId = " << _tripId << std::endl;
  std::cout << "_mode = " << _mode << std::endl;
  std::cout << "_product = " << _product << std::endl;
  std::cout << "_metro = " << _metro << std::endl;
  std::cout << "_latitude = " << _latitude << std::endl;
  std::cout << "_longitude = " << _longitude << std::endl;
  // std::cout << "_updatedAt = " << std::chrono::system_clock::to_time_t(_updatedAt) << std::endl;
  std::cout << "***" << std::endl;
}

VehicleType Vehicle::GetVehicleType() {
  return _type;
}

// Setters
void Vehicle::Update(std::chrono::high_resolution_clock::time_point &time, web::json::value &data) {
  // Vehicle type
  Assign(_type, data["line"]);
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

