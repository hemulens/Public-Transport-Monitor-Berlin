#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include <chrono>
#include <map>

#include "ApiData.cpp"

// Enum of vehicle types – sorted according to VBB docs: https://github.com/public-transport/hafas-client/blob/5/docs/radar.md. See updated API structure here: https://v5.vbb.transport.rest/radar?north=52.557396&west=13.287704&south=52.483175&east=13.505750. Comments below reflect values for the keys "mode" and "product"
enum VehicleType { 
  null,           // no type (null)
  bus,            // bus bus
  tram,           // train tram
  subwayTrain,    // train subway
  suburbanTrain,  // train suburban
  expressTrain,   // train express
  regionalTrain   // train regional
};

// Helper templates – parser and safeguard against "no conversion abort trap" when JSON data equals NULL
// Generic template
template <typename Type>
void Assign(Type &variable, web::json::value &data);
// Template specializations
template <>
void Assign(int &variable, web::json::value &data);
template <>
void Assign(double &variable, web::json::value &data);
template <>
void Assign(std::string &variable, web::json::value &data);
template <>
void Assign(bool &variable, web::json::value &data);
template <>
void Assign(VehicleType &variable, web::json::value &data);


class Vehicle {
  public:
    // Constructors:
    Vehicle();
    Vehicle(std::chrono::high_resolution_clock::time_point time, web::json::value data);
    // Destructor
    ~Vehicle();
    // Getters:
    int GetVehicleId();
    int GetVehicleCounter();
    VehicleType GetVehicleType();
    void GetNormalizedPosition(double &lat, double &lon, int resX, int resY);  // Geo position normalization
    std::chrono::high_resolution_clock::time_point GetUpdateTime();
    std::string GetTripId();  // temporary 
    void PrintInstance();  // temporary
    // Setters:
    void Update(std::chrono::high_resolution_clock::time_point &time, web::json::value &data);
  protected:
    // ID counter
    int _id;
  private:
    VehicleType _type;
    // API data variables
    std::string _tripId;  // tripId
    std::string _mode;    // line -> mode
    std::string _product; // line -> product
    bool _metro;          // line -> metro
    double _latitude;     // location -> latitude
    double _longitude;    // location -> longitude
    // Time of the last update
    std::chrono::high_resolution_clock::time_point _updatedAt;
    // Global ID counter (auxiliary)
    static int _idCounter;  
};


#endif /* VEHICLE_H */