#include<memory>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/dnn/dnn.hpp>
#include<vector>
#include"FaceBodyRecognition.hpp"

std::vector<cv::Mat> preProcess(cv::Mat &inputImage, cv::dnn::Net &net){
	cv::Mat blob;
	cv::dnn::blobFromImage(inputImage, blob, 1./255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false);
	net.setInput(blob);

	std::vector<cv::Mat> outputs;
	net.forward(outputs, net.getUnconnectedOutLayersNames());

	return outputs;
} 

bool isPresent(cv::Mat &inputImage, cv::dnn::Net &neuralNetwork, float &xCoordinates){
	std::vector<cv::Mat> outputs = preProcess(inputImage, neuralNetwork);
	
	std::vector<cv::Mat>::iterator it = outputs.begin();

	for(it; it!=outputs.end(); it++){
		//Iterate over cv::Mat vector, then unwrap the values...TBD
	}

}