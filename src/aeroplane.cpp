#include "Aeroplane.h"


// Init static variable
int Aeroplane::_idCtr = 0;

// Initialize object with default or null values
Aeroplane::Aeroplane() : _icao24("undefined"), _callsign("undefined"), _origin_country("undefined"), _time_position(0), _last_contact(0), _longitude(0.0), _latitude(0.0), _baro_altitude(0.0), _on_ground(true), _velocity(0.0), _true_track(0.0), _vertical_rate(0.0), _sensors({0}), _geo_altitude(0.0), _squawk("undefined"), _spi(false), _position_source(0) {
  _id = _idCtr++;
  std::cout << "Aeroplane " << _id << " created" << std::endl;
}

// Initialize object with real API values
// Aeroplane::Aeroplane(int data) {
//   _id = _ctr++;
// }

// Destructor
Aeroplane::~Aeroplane() {
  std::cout << "Aeroplane " << _id << " deleted" << std::endl;
  _id = _idCtr--;
}

// Getters
int Aeroplane::GetID() {
  return _id;
}

int Aeroplane::GetCounter() {
  return _idCtr;
}

// Setters
