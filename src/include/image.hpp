#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Image {
  std::string name;

public:
  cv::Mat image;
  // Homography計算用
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat descriptors;
  cv::Ptr<cv::Feature2D> feature;

  Image(std::string path, int color = cv::IMREAD_COLOR) {
    image = cv::imread(path, color);
    if (image.empty()) {
      std::cout << path << " image not found" << std::endl;
      throw 1;
    }
    name = path.substr(path.size() -
                       9); //暫定的に9にしてるだけで意味はこれっぽっちもない

    detectKeyPoints();
  }

  //可視化用
  void show() { cv::imshow(name, image); };

  //特徴点計算　コンストラクタから呼び出す
  void detectKeyPoints() {
    feature = cv::AKAZE::create();
    feature->detectAndCompute(image, cv::Mat(), keypoints, descriptors);
  }
};
