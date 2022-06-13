#include "homography.hpp"
#include "image.hpp"
#include "read.hpp"
#include <opencv2/opencv.hpp>
#include <string>

const std::string pictures_dir = "../../pictures/";

std::string target_image_number = "185";

int main() {

  ///////////////////////// image input
  std::string template_image_path =
      pictures_dir + "meter_template/tempbthesis2.png";
  Image template_image(template_image_path);

  std::string target_image_path =
      pictures_dir + "bthesis/roi/pic" + target_image_number + ".png";
  Image target_image(target_image_path);

  // for visualization
  //  template_image.show();
  //  target_image.show();
  /////////////////////////

  getHomography(template_image, target_image);
  cv::waitKey();

  return 0;
}
