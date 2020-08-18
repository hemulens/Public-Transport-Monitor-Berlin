#ifndef PUBLICTRANSPORT_H
#define PUBLICTRANSPORT_H

#include <vector>
#include <memory>
#include <chrono>

#include "Vehicle.h"

class PublicTransport {
  public:
    PublicTransport();
    void Run();
  private:
    std::shared_ptr<Data> _data;
    web::json::value *_apiOutput;
    std::chrono::high_resolution_clock::time_point *_updateTime;
    std::vector<std::unique_ptr<Vehicle>> _vehicles;
    // Counters for internal checkup of data validity
    int _updated;
    int _created;
    int _deleted;
};

#endif