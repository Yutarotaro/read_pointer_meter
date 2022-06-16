#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;

void thresholdIntegral(cv::Mat &inputMat, cv::Mat &outputMat);
