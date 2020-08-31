#include "Graphics.h"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void Graphics::SetBgFilename(std::string filename) {
  _bgFilename = filename;
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
    // TODO: Wait for Request thread to finish fetching and parsing data (finishes by itself now)

    transport.Run();
    // update graphics
    this->SetVehicles(transport.GetVehiclesPtr());
    this->DrawVehicles();
    // sleep at every iteration to reduce CPU usage
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void Graphics::LoadBackgroundImg() {
  // create window
  _windowName = "Berlin Public Transport Monitor";
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

  // create overlay from all traffic objects
  for (auto &it : *_vehicles) {
    double latitude, longitude;
    it->GetPosition(latitude, longitude);
    // Set vehicle color according to its type
    if (it->GetVehicleType() == VehicleType::null) {
      cv::Scalar nullColor = cv::Scalar(0, 255, 0);  // green; red: cv::Scalar(0, 0, 255)
      cv::circle(_images.at(1), cv::Point2d(latitude, longitude), 20, nullColor, -1);
    } else if (it->GetVehicleType() != VehicleType::null) {
      cv::RNG rng(stoi(it->GetTripId()));
      int b = rng.uniform(0, 255);
      int g = rng.uniform(0, 255);
      int r = sqrt(255 * 255 - g * g - r * r);  // ensure that length of color vector is always 255
      cv::Scalar vehicleColor = cv::Scalar(b, g, r);
      cv::circle(_images.at(1), cv::Point2d(latitude, longitude), 15, vehicleColor, -1);
    }
  }

  float opacity = 0.85;
  cv::addWeighted(_images.at(1), opacity, _images.at(0), 1.0 - opacity, 0, _images.at(2));

  // display background and overlay image
  cv::imshow(_windowName, _images.at(2));
  cv::waitKey(33);
}
