#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Image {
  std::string name;

public:
  cv::Mat image, original;
  // Homography計算用
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat descriptors;
  cv::Ptr<cv::Feature2D> feature;

  Image(cv::Mat temp) {
    image = temp;
    original = temp;
    name = "temp";
  }

  Image(std::string path, int color = cv::IMREAD_COLOR) {
    image = cv::imread(path, color);
    if (image.empty()) {
      std::cout << path << " image not found" << std::endl;
      throw 1;
    }
    image.copyTo(original);
    name = path.substr(path.size() -
                       9); //暫定的に9にしてるだけで意味はこれっぽっちもない
  }

  //可視化用
  void show() { cv::imshow(name, image); };

  //特徴点計算
  void detectKeyPoints() {
    feature = cv::AKAZE::create();
    feature->detectAndCompute(image, cv::Mat(), keypoints, descriptors);
  }

  //前処理(読み取り対象target_imageにしか使わない(と思っているがどう使うかは自由))
  void preprocess(Image template_image) {

    // template_imageとtarget_imageの大きさを揃える（その方がマッチングの精度が上がったので）
    double rate = std::max((double)template_image.image.cols / image.cols,
                           (double)template_image.image.rows / image.rows);
    cv::resize(image, image, cv::Size(), rate, rate);
    ////////////////////////////////////////

    //先鋭化
    double k = 3.;
    cv::Mat kernel =
        (cv::Mat_<float>(3, 3) << 0, -k, 0, -k, 4 * k + 1., -k, 0, -k, 0);

    cv::filter2D(image, image, -1, kernel, cv::Point(-1, -1), 0,
                 cv::BORDER_DEFAULT);
    ////////////////////////////////////////
  }
};
