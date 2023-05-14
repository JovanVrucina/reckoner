#include<memory>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/dnn/dnn.hpp>
#include<vector>
#include"FaceBodyRecognition.hpp"



bool isPresent(cv::CascadeClassifier Cascade, cv::Mat Frame, cv::Rect &destinationRectangle){
	cv::Mat temp;
	std::vector<cv::Rect> faces;
	cv::cvtColor(Frame, temp, cv::COLOR_RGB2GRAY);
	Cascade.detectMultiScale(temp, faces, 1.25);

	if(faces.empty()){
		return false;
	}
	else{
		destinationRectangle = faces[0];
		return true;
	}

}

bool isPresent(cv::CascadeClassifier Cascade, cv::Mat stream[], cv::Rect &destinationRectangle){
	int positiveCounter = 0;
	cv::Rect tempRect;
	for(int i=0; i<samplesTaken; i++){
		if(isPresent(Cascade, stream[i], tempRect)){
			positiveCounter++;
		}
	}
	if(positiveCounter>=minConfirmed()){
		destinationRectangle = tempRect;
		return true;
	}
	else{
		return false;
	}	
}
