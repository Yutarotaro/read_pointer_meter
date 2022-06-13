#include "homography.hpp"
#include "image.hpp"
#include "read.hpp"
#include <opencv2/opencv.hpp>
#include <string>

const std::string pictures_dir = "../../pictures/";
std::string target_image_number = "185";

std::string template_image_path =
    pictures_dir + "meter_template/tempbthesis2.png";
std::string target_image_path =
    pictures_dir + "bthesis/roi/pic" + target_image_number + ".png";

int main() {

  ///////////////////////// image input
  Image template_image(template_image_path);
  Image target_image(target_image_path);

  //マッチングしやすくするための地味だけど大切な努力
  //処理するのはtarget_imageの方
  target_image.preprocess(template_image);

  //特徴点検出
  template_image.detectKeyPoints();
  target_image.detectKeyPoints();

  // Homography推定 template から target へのHomography
  cv::Mat H = getHomography(template_image, target_image);

  //推定したHomographyの逆行列でtarget_imageを射影変換し、template_imageと視点を揃える
  Image warped_target_image(cv::Mat::zeros(target_image.image.rows,
                                           target_image.image.cols, CV_8UC3));
  cv::warpPerspective(target_image.image, warped_target_image.image, H.inv(),
                      warped_target_image.image.size());

  //////適応的2値化

  cv::waitKey();
  return 0;
}
