#include<cmath>
#include<opencv2/dnn/dnn.hpp>
#include<opencv2/core.hpp>
#include<opencv2/objdetect.hpp>
#ifndef FACE_AND_BODY_H
#define FACE_AND_BODY_H

/*NEW CONFIGURATION*/
const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.5;
const float NMS_THRESHOLD = 0.45;
const float CONFIDENCE_THRESHOLD = 0.45;
/*END NEW CONFIGURATION*/


std::vector<cv::Mat> preProces(cv::Mat &input_image, cv::dnn::Net &net);
bool isPresent(cv::CascadeClassifier Cascade, cv::Mat Frame, cv::Rect &destinationRectangle);

#endif
