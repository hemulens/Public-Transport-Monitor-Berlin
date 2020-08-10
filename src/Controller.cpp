#include "Aeroplane.cpp"
// #include "ApiData.cpp"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
  Data data;
  data.Fetch();
  std::cout << data.GetTime() << std::endl;
  std::cout << data.GetStates() << std::endl;
  std::cout << "***" << std::endl;
  std::unique_ptr<Aeroplane> aeroplane = std::make_unique<Aeroplane>();
  Aeroplane *aeroplane2 = new Aeroplane();
  std::cout << "Aeroplane instance counter = " << aeroplane->GetCounter() << std::endl;
  delete aeroplane2;
  std::cout << "Aeroplane instance counter = " << aeroplane->GetCounter() << std::endl;

  return 0;
}