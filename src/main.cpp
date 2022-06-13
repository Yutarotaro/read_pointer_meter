#include "homography.hpp"
#include "image.hpp"
#include "json.hpp"
#include "read.hpp"
#include "threshold.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include <string>

using json = nlohmann::json;

const std::string pictures_dir = "../../pictures/";

int main() {
  ///////////////////////// json input
  std::ifstream i("../setting.json");
  json params;
  i >> params;

  std::string target_image_number =
      params["meter_params"]["target_image_number"].get<string>();

  ///////////////////////// image input
  std::string template_image_path =
      pictures_dir + "meter_template/tempbthesis2.png";
  std::string target_image_path =
      pictures_dir + "bthesis/roi/pic" + target_image_number + ".png";

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
  Image warped_target_image(cv::Mat::zeros(template_image.image.rows,
                                           template_image.image.cols, CV_8UC3));
  cv::warpPerspective(target_image.image, warped_target_image.image, H.inv(),
                      warped_target_image.image.size());

  //////適応的2値化
  /// https://github.com/phryniszak/AdaptiveIntegralThresholding
  template_image.cvtToGray(template_image.image);
  cv::Mat b_template =
      cv::Mat::zeros(template_image.gray_image.size(), CV_8UC1);
  thresholdIntegral(template_image.gray_image, b_template);

  warped_target_image.cvtToGray(warped_target_image.image);
  cv::Mat b_target =
      cv::Mat::zeros(warped_target_image.gray_image.size(), CV_8UC1);
  thresholdIntegral(warped_target_image.gray_image, b_target);

  ///////// 差分画像 diff_tmpを生成 (排他的論理和 XOR)
  cv::Mat diff_tmp;
  cv::bitwise_xor(b_template, b_target, diff_tmp);

  ///////// meter領域のみ残した差分画像 diff_imageを生成 メータの輪郭でくり抜く
  int d = 90; //ノリで決めた
  cv::Mat mask_for_diff = cv::Mat::zeros(diff_tmp.rows, diff_tmp.cols, CV_8UC1);
  cv::circle(mask_for_diff, cv::Point(diff_tmp.cols / 2, diff_tmp.rows / 2),
             diff_tmp.cols / 2 - d / 2, cv::Scalar(255), -1, 0);
  cv::Mat diff_image;
  diff_tmp.copyTo(diff_image, mask_for_diff);

  ///////// 収縮・膨張
  const int itr = 3; //回数お好みで調整
  cv::erode(diff_image, diff_image, cv::Mat(), cv::Point(-1, -1), itr);
  cv::dilate(diff_image, diff_image, cv::Mat(), cv::Point(-1, -1), itr);

  ///////// 細線化
  cv::Mat thinned_diff_image;
  cv::ximgproc::thinning(diff_image, thinned_diff_image, cv::ximgproc::WMF_EXP);

  ///////// 読み取り
  cv::imshow("pointer detection", read(thinned_diff_image));

  cv::waitKey();
  return 0;
}
