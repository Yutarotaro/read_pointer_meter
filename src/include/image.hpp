#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Image {
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat descriptors;
  cv::Mat image;
  std::string name;

public:
  Image(std::string path, int color = cv::IMREAD_COLOR) {
    image = cv::imread(path, color);
    if (image.empty()) {
      std::cout << path << " image not found" << std::endl;
      throw 1;
    }
    name = path.substr(path.size() -
                       9); //暫定的に9にしてるだけで意味はこれっぽっちもない
  }
  void show() { cv::imshow(name, image); };
};
