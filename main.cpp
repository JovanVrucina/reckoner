#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<future>
#include<unistd.h>
#include<cppgpio.hpp>
#include"include/FaceBodyRecognition.hpp"
using namespace std;

int main(int argc, char *argv[]){
	//initialising variables
	cout<<"Initialising...";
	if(argc!=2){
		cout<<"Error!"<<'\n';
		return -1;
	}
	
	GPIO::DigitalOut leftGPIO(16);
	GPIO::DigitalOut rightGPIO(20);
	GPIO::DigitalOut StandbyGPIO(21);

	leftGPIO.off();
	rightGPIO.off();
	StandbyGPIO.off();

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

	//opening cascadesa and checking if the cascades have been loaded properly
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

		if(midpoint != -1){
			if(midpoint>=340){
				rightGPIO.on();
				leftGPIO.off();
			}else if(midpoint <= 300){
				rightGPIO.off();
				leftGPIO.on();
			}else{
				rightGPIO.on();
				leftGPIO.on();
			}
		}


		// future<bool> imaLedja = async(launch::async, 
		// 							[&]{return isPresent(BodyCascade,
		// 							 frame,
		// 							  backRectangle);});
		// future<bool> imaLica = async(launch::async, 
		// 							[&]{return isPresent(FaceCascade,
		// 							 frame,
		// 							  faceRectangle);});

}}
