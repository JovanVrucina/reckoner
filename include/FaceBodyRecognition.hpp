#include<cmath>
#include<vector>
#include<opencv2/dnn/dnn.hpp>
#include<opencv2/core.hpp>
#include<opencv2/objdetect.hpp>
#ifndef FACE_AND_BODY_H
#define FACE_AND_BODY_H

const float confidenceThreshold = 0.45;

struct detection{
    int class_id;
    float confidence;
    cv::Rect box;
};

std::vector<cv::Mat> pre_process(cv::Mat &input_image, cv::dnn::Net &net);
cv::Mat post_process(cv::Mat &input_image, std::vector<cv::Mat> &outputs);

#endif
