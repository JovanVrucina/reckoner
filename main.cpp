#include<opencv2/core.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<fstream>
#include<future>
#include<unistd.h>
//#include<cppgpio.hpp>
#include"include/FaceBodyRecognition.hpp"
using namespace std;

int main(int argc, char *argv[]){
	//initialising variables
	cout<<"Initialising...";
	if(argc!=2){
		cout<<"Error!"<<'\n';
		return -1;
	}
	//GPIO::DigitalOut bit1(02);
	//GPIO::DigitalOut bit2(03);
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
	cv::namedWindow("out", cv::WINDOW_AUTOSIZE);
	//Start of the main code loop
	while(true){
		camera>>frame;

		vector<cv::Mat> outputs = pre_process(frame, bodyNetwork);
		cv::Mat dispImg = post_process(frame, outputs);
		
		cv::imshow("out", dispImg);
		cv::waitKey(5);

		// future<bool> imaLedja = async(launch::async, 
		// 							[&]{return isPresent(BodyCascade,
		// 							 frame,
		// 							  backRectangle);});
		// future<bool> imaLica = async(launch::async, 
		// 							[&]{return isPresent(FaceCascade,
		// 							 frame,
		// 							  faceRectangle);});
	// // 	if(imaLica.get()){
	// // 		cout<<"Face detected"<<'\n';
	// // 		//bit1.off();
	// // 		//bit2.off();
	// // 		//send message through GPIO pins to stop the motors
	// // 	}
	// // 	else if(imaLedja.get()){
	// // 		cout<<backRectangle.x+(backRectangle.width/2);
	// // 		//bit1.on();
	// // 		//bit2.on();
	// // 		//send message to follow depending on where is the body
	// // 	}
	// // 	else{
	// // 		cout<<"Nothing detected"<<'\n';
	// // 		//bit1.off();
	// // 		//bit2.off();
	// // 		//send message to stop through GPIO pins
	// // 	}
	// // }
}}