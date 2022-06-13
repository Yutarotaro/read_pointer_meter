#include "homography.hpp"
#include "read.hpp"
#include <opencv2/opencv.hpp>
#include <string>

const std::string pictures_dir = "../../pictures/";

int main() {

  cv::Mat template_image = cv::imread(pictures_dir + "lena.jpg", 1);
  cv::imshow("D", template_image);
  cv::waitKey();

  return 0;
}
