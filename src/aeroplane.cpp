#include "Aeroplane.h"


// Init static variable
int Aeroplane::_idCtr = 0;

// Initialize object with default or null values
Aeroplane::Aeroplane() : _icao24("undefined"), 
                         _callsign("undefined"), 
                         _origin_country("undefined"), 
                         _time_position(0), 
                         _last_contact(0), 
                         _longitude(0.0), 
                         _latitude(0.0), 
                         _baro_altitude(0.0), 
                         _on_ground(true), 
                         _velocity(0.0), 
                         _true_track(0.0), 
                         _vertical_rate(0.0), 
                         _sensors(0),
                         _geo_altitude(0.0), 
                         _squawk("undefined"), 
                         _spi(false), 
                         _position_source(0),
                         _updated_at(0) {
  _id = _idCtr++;
  std::cout << "Aeroplane " << _id << " created" << std::endl;
}

Aeroplane::Aeroplane(int time, web::json::value planeData)  : _icao24(planeData[states::icao24].serialize()), 
                                                              _callsign(planeData[states::callsign].serialize()), 
                                                              _origin_country(planeData[states::origin_country].serialize()), 
                                                              _time_position(stoi(planeData[states::time_position].serialize())),
                                                              _last_contact(stoi(planeData[states::last_contact].serialize())),
                                                              _longitude(stod(planeData[states::longitude].serialize())),
                                                              _latitude(stod(planeData[states::latitude].serialize())),
                                                              _baro_altitude(stod(planeData[states::baro_altitude].serialize())),
                                                              _on_ground(true),  // add method
                                                              _velocity(stod(planeData[states::velocity].serialize())),
                                                              _true_track(stod(planeData[states::true_track].serialize())),
                                                              _vertical_rate(stod(planeData[states::vertical_rate].serialize())),
                                                              _sensors(planeData[states::sensors]),  // research what data is retrieved – so far null
                                                              _geo_altitude(stod(planeData[states::geo_altitude].serialize())),
                                                              _squawk(planeData[states::squawk].serialize()),
                                                              _spi(false),  // add method
                                                              _position_source(stoi(planeData[states::position_source].serialize())),
                                                              _updated_at(time) 
                                                              {
  
  // Update counter
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
std::string Aeroplane::GetIcao() {
  return _icao24;
};

// Setters
void Aeroplane::Update(int time, web::json::value planeData) {
  // API data variables
  _icao24 = planeData[states::icao24].serialize(); 
  _callsign = planeData[states::callsign].serialize();
  _origin_country = planeData[states::origin_country].serialize();
  _time_position = stoi(planeData[states::time_position].serialize());
  _last_contact = stoi(planeData[states::last_contact].serialize());
  _longitude = stod(planeData[states::longitude].serialize());
  _latitude = stod(planeData[states::latitude].serialize());
  _baro_altitude = stod(planeData[states::baro_altitude].serialize());
  _on_ground = true;  // add method
  _velocity = stod(planeData[states::velocity].serialize());
  _true_track = stod(planeData[states::true_track].serialize());
  _vertical_rate = stod(planeData[states::vertical_rate].serialize());
  _sensors = planeData[states::sensors];  // research what data is retrieved – so far null
  _geo_altitude = stod(planeData[states::geo_altitude].serialize());
  _squawk = planeData[states::squawk].serialize();
  _spi = false;  // add method
  _position_source = stoi(planeData[states::position_source].serialize());
  // Time of the last update
  _updated_at = time;
}