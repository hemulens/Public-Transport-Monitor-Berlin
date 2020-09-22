#ifndef PUBLICTRANSPORT_H
#define PUBLICTRANSPORT_H

#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>

#include "Vehicle.cpp"

class PublicTransport {
  public:
    PublicTransport();
    // Getters
    std::vector<std::unique_ptr<Vehicle>> *GetVehiclesPtr();
    // Behavioral methods
    void Run();
  private:
    std::shared_ptr<Data> _data;
    web::json::value *_apiOutput;  // Raw pointer used instead of smart pointer on purpose
    std::chrono::high_resolution_clock::time_point *_updateTime;  // Raw pointer used instead of smart pointer on purpose
    std::vector<std::unique_ptr<Vehicle>> _vehicles;
    // Counters for internal checkup of data validity
    int _updated;
    int _created;
    int _deleted;
};

#endif