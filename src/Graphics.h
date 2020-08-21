#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <opencv2/core.hpp>
#include <string>
#include <vector>

class Graphics {
 public:
  // constructor / desctructor

  // getters / setters
  // void SetBgFilename(std::string filename) {
  //   _bgFilename = filename;
  // }
  // void SetTrafficObjects(std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) {
  //   _trafficObjects = trafficObjects;
  // };

  // typical behaviour methods
  void Simulate();

 private:
  // typical behaviour methods
  void LoadBackgroundImg();
  void DrawTrafficObjects();

  // member variables
  // std::vector<std::shared_ptr<TrafficObject>> _trafficObjects;
  std::string _bgFilename;
  std::string _windowName;
  std::vector<cv::UMat> _images;
};

#endif