#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include <chrono>

#include "ApiData.cpp"

// Helper templates – parser and safeguard against "no conversion abort trap" when JSON data equals NULL
// General template
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


class Vehicle {
  public:
    // Constructors:
    Vehicle();
    Vehicle(std::chrono::system_clock::time_point time, web::json::value data);
    // Destructor
    ~Vehicle();
    // Getters:
    int GetVehicleID();
    int GetVehicleCounter();
    std::string GetTripID();  // temporary 
    // Setters:
    void Update(std::chrono::system_clock::time_point &time, web::json::value &data);
  protected:
    // Counter
    int _id;
    static int _idCtr;  // global variable for counting object ids
  private:
    // API data variables
    std::string _tripId;
    std::string _lineMode;
    std::string _lineProduct;
    bool _lineMetro;
    double _locationLatitude; // create a vectore instead?
    double _locationLongitude;
    // Time of the last update
    std::chrono::system_clock::time_point _updatedAt;
};


#endif /* VEHICLE_H */