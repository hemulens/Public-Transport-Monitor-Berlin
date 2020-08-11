#include "Aeroplane.cpp"
// #include "ApiData.cpp"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {
  Data data;
  data.Fetch();
  std::cout << data.GetTime() << std::endl;
  std::cout << data.GetStates() << std::endl;
  std::cout << "***" << std::endl;

  std::vector<std::unique_ptr<Aeroplane>> planes;
  for (int i = 0; i < data.GetStates().size(); i++) {
    std::unique_ptr<Aeroplane> p = std::make_unique<Aeroplane>(data.GetTime(), data.GetStates()[i]);
    std::cout << "Plane's ICAO = " << p->GetIcao() << std::endl;
    planes.emplace_back(std::move(p));
  }

  // Experiment with deletion of NEW on the heap + deallocation of smart pointers
  // std::unique_ptr<Aeroplane> aeroplane = std::make_unique<Aeroplane>();
  // Aeroplane *aeroplane2 = new Aeroplane();
  // std::cout << "Aeroplane instance counter = " << aeroplane->GetCounter() << std::endl;
  // delete aeroplane2;
  // std::cout << "Aeroplane instance counter = " << aeroplane->GetCounter() << std::endl;

  return 0;
}