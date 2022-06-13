#pragma once

#include "json.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using json = nlohmann::json;

cv::Mat read(cv::Mat thinned_image) {
  cv::Mat ret;
  thinned_image.copyTo(ret);
  cv::cvtColor(ret, ret, CV_GRAY2BGR);

  std::vector<cv::Vec3f> lines; //ハフ変換で検出された直線たち
  int votes = 10;
  cv::HoughLines(thinned_image, lines, 1, 0.0001 /*CV_PI / 720.*/, votes, 0, 0);

  std::cout << "Number of detected lines: " << lines.size() << std::endl;

  int tmp = 0;
  int index = 0;
  double value = 0.; //読み取り値
  double rad = 0.;   //針の角度

  cv::Point pt1, pt2; //検出された直線の端点が入る

  if (lines.size()) {
    for (size_t i = 0; i < lines.size(); ++i) {
      //投票数が一番多い直線を選ぶ
      if (lines[i][1] && lines[i][0] &&
          lines[i][2] > tmp /*&& std::abs(lines[i][1] - CV_PI / 2.) > eps*/) {
        index = i;
        tmp = lines[i][2];
      }
    }

    float rho = lines[index][0], theta = lines[index][1];
    double a = std::cos(theta), b = std::sin(theta);
    double x0 = a * rho, y0 = b * rho;
    pt1.x = cvRound(x0 + 1000 * (-b));
    pt1.y = cvRound(y0 + 1000 * (a));
    pt2.x = cvRound(x0 - 1000 * (-b));
    pt2.y = cvRound(y0 - 1000 * (a));

    cv::line(ret, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    rad = lines[index][1];
  }

  std::ifstream i("../setting.json");
  json params;
  i >> params;

  auto front_value = params["meter_params"]["front_value"].get<double>();
  auto k = params["meter_params"]["k"].get<double>();
  auto front_rad = params["meter_params"]["front_rad"].get<double>();

  value = front_value + k * (rad - front_rad);

  std::cout << "読み取り結果: " << value << std::endl;

  return ret;
}
