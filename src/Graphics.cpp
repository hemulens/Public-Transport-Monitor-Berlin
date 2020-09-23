#include "Graphics.h"

#include <iostream>
#include <chrono>
#include <string>
#include <future>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void Graphics::SetBgFilename(std::string filename) {
  _bgFilename = filename;
}

void Graphics::SetBgSize(int x, int y) {
  _resX = x;
  _resY = y;
}

void Graphics::SetVehicles(std::vector<std::unique_ptr<Vehicle>> *vehicles) {
  _vehicles = vehicles;
  // or 
  // pass &transport
  // _vehicles = transport.GetVehiclesPtr();
}

void Graphics::Simulate(PublicTransport &transport) {
  this->LoadBackgroundImg();
  while (true) {
    std::cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    transport.Run();
    // update graphics
    std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
    this->DrawVehicles();
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << duration << " milliseconds – drawing vehicles" << std::endl;
    // sleep at every loop cycle (server returns real updates approx. once in 8-10 seconds)
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n" << std::endl;
  }
}

void Graphics::LoadBackgroundImg() {
  // create window
  _windowName = "Berlin Public Transport Monitor (Realtime)";
  cv::namedWindow(_windowName, cv::WINDOW_NORMAL);

  // load image and create copy to be used for semi-transparent overlay
  cv::UMat background;  // GPU mode
  cv::imread(_bgFilename).copyTo(background);
  _images.push_back(background);          // first element is the original background
  _images.push_back(background.clone());  // second element will be the transparent overlay
  _images.push_back(background.clone());  // third element will be the result image for display
}

void Graphics::DrawVehicles() {
  // reset images
  _images.at(1) = _images.at(0).clone();
  _images.at(2) = _images.at(0).clone();
  // declaring lo and la variables for further vehicle position normalization
  double longitude, latitude;
  cv::Scalar vehicleColor;
  // Concurrent setup with the linear (deferred) execution. std::launch::deferred performs poor on the small dataset (i = 500); 
  std::vector<std::future<void>> futures;
  for (auto &v : *_vehicles) {
    futures.emplace_back(std::async(std::launch::deferred, [this, &v, &vehicleColor, &longitude, &latitude](){
      v->GetNormalizedPosition(longitude, latitude, _resX, _resY);
      // Set vehicle color according to its type
      if (v->GetVehicleType() == VehicleType::null) {  // black
        // std::cout << "Vehicle of type NULL! TripId = " << v->GetTripId() << std::endl;  // for debugging
        vehicleColor = cv::Scalar(0, 0, 0); 
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 20, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::bus) {  // orange
        vehicleColor = cv::Scalar(0, 128, 255);  
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 10, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::tram) {  // red
        vehicleColor = cv::Scalar(0, 0, 204);  
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 10, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::subwayTrain) {  // light blue
        vehicleColor = cv::Scalar(255, 153, 51);  
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 10, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::suburbanTrain) {  // green
        vehicleColor = cv::Scalar(76, 153, 0);  
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 10, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::expressTrain) {  // dark blue
        vehicleColor = cv::Scalar(153, 76, 0);  
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 10, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::regionalTrain) {  // purple
        vehicleColor = cv::Scalar(255, 0, 127);  
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 10, vehicleColor, -1);
      } else if (v->GetVehicleType() == VehicleType::ferry) {  // brown
        vehicleColor = cv::Scalar(0, 76, 153); 
        cv::circle(_images.at(1), cv::Point2d(longitude, latitude), 15, vehicleColor, -1);
      }
      // Printing function used for debugging
      // std::cout << "Vehicle type = " << v->GetVehicleType() << " id = " << v->GetTripId() << ": Lat = " << latitude << ", Long = " << longitude << std::endl;
    }));
  }

  for (const std::future<void> &ftr : futures) {
    ftr.wait();
  }

  float opacity = 0.95;
  cv::addWeighted(_images.at(1), opacity, _images.at(0), 1.0 - opacity, 0, _images.at(2));

  // Display background and overlay image
  cv::imshow(_windowName, _images.at(2));
  cv::waitKey(33);
}
