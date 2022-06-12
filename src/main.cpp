#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
  cv::Mat image = cv::imread("../lena.jpg", 1);
  cv::imshow("Display", image);

  cv::waitKey(0);
  return 0;
}
