#include<cmath>
#include<vector>
#include<opencv2/dnn/dnn.hpp>
#include<opencv2/core.hpp>
#include<opencv2/objdetect.hpp>
#ifndef FACE_AND_BODY_H
#define FACE_AND_BODY_H

std::vector<cv::Mat> pre_processYOLO(cv::Mat &input_image, cv::dnn::Net &net);
cv::Rect post_processYOLO(cv::Mat &input_image, std::vector<cv::Mat> &outputs);

#endif
