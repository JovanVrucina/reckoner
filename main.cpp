#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<future>
#include<unistd.h>
#include"include/FaceBodyRecognition.hpp"
using namespace std;

int main(int argc, char *argv[]){
	//initialising variables
	cout<<"Initialising...";
	if(argc!=2){
		cout<<"Error!"<<'\n';
		return -1;
	}
	


	cv::Mat frame;
	cv::Rect backRectangle; //rectangle representing the first detected back
	cv::Rect faceRectangle; //rectangle representing the first detected face
	cout<<"done"<<'\n';

	//opening camera and checking if the camera is opened
	cout<<"Opening capturing device...";
	cv::VideoCapture camera(strtol(argv[1], NULL, 10)); //opening camera with index given from the command line
	if(!camera.isOpened()){
		cout<<"Error!"<<'\n';
		return -1;
	}
	cout<<"done"<<'\n';

	//opening neural network and checking if the cascades have been loaded properly
	cout<<"Loading cascades...";
	cv::dnn::Net faceNetwork = cv::dnn::readNetFromONNX("neuralNet/version-RFB-640.onnx");
	cv::dnn::Net bodyNetwork = cv::dnn::readNetFromONNX("neuralNet/yolov5n.onnx");
	if(faceNetwork.empty()||bodyNetwork.empty()){
		cout<<"Error!"<<'\n';
		return -1;
	}
	cout<<"done"<<'\n'<<"ready."<<'\n';
	//Start of the main code loop
	while(true){
		camera>>frame;
		vector<cv::Mat> networkOutputsBody = pre_processYOLO(frame, bodyNetwork);
		cv::Rect bodyRectangle = post_processYOLO(frame, networkOutputsBody);
		
	
		int midpoint = bodyRectangle.x+(bodyRectangle.width/2);
		
		cout<<midpoint<<" "<<bodyRectangle.x<<'\n';

		if(bodyRectangle.x != -1){
			if(midpoint>=420){
				system("python3 ./left.py");
			}else if(midpoint <= 256){
				system("python3 ./right.py");
			}else{
				system("python3 ./straight.py");
			}
		}else{
			system("python3 ./stop.py");
		}

}}
