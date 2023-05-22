#include<memory>
#include<opencv2/opencv.hpp>
#include<opencv2/dnn/dnn.hpp>
#include<vector>
#include<iostream>
#include"FaceBodyRecognition.hpp"

std::vector<cv::Mat> pre_process(cv::Mat &input_image, cv::dnn::Net &net)
{
// Convert to blob.
    cv::Mat blob;
    cv::dnn::blobFromImage(input_image, blob, 1./255., cv::Size(640.0, 640.0), cv::Scalar(), true, false);

    net.setInput(blob);
    
    // Forward propagate.
    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    
    return outputs;

}

cv::Mat post_process(cv::Mat &input_image, std::vector<cv::Mat> &outputs)
{
// Initialize vectors to hold respective outputs while unwrapping detections.
    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    // Resizing factor.
    float x_factor = input_image.cols / 640.0;
    float y_factor = input_image.rows / 640.0;
    
    float *data = (float *)outputs[0].data;
    
    const int dimensions = 85;
    const int rows = 25200;
    // Iterate through 25200 detections.
    for (int i = 0; i < rows; ++i) 
    {
        float confidence = data[4];
        // Discard bad detections and continue.
        if (confidence >= 0.45) 
        {
            float * classes_scores = data + 5;
            // Create a 1x85 Mat and store class scores of 80 classes.
            cv::Mat scores(1, 80, CV_32FC1, classes_scores);
            
            // Perform minMaxLoc and acquire index of best class score.
            cv::Point class_id;
            double max_class_score;
            minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
            // Continue if the class score is above the threshold.
            if (max_class_score > 0.45) 
            {
                // Store class ID and confidence in the pre-defined respective vectors.
    
                confidences.push_back(confidence);
                class_ids.push_back(class_id.x);
    
                // Center.
                float cx = data[0];
                float cy = data[1];
                // Box dimension.
                float w = data[2];
                float h = data[3];
                // Bounding box coordinates.
                int left = int((cx - 0.5 * w) * x_factor);
                int top = int((cy - 0.5 * h) * y_factor);
                int width = int(w * x_factor);
                int height = int(h * y_factor);
                // Store good detections in the boxes vector.
                boxes.push_back(cv::Rect(left, top, width, height));
            }
    
        }
        // Jump to the next column.
        data += 85;
    }
    
    // Perform Non Maximum Suppression and draw predictions.
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, 0.45, 0.45, indices);
    for (int i = 0; i < indices.size(); i++) 
    {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
    
        int left = box.x;
        int top = box.y;
        int width = box.width;
        int height = box.height;
        // Draw bounding box.
        rectangle(input_image, cv::Point(left, top), cv::Point(left + width, top + height), cv::Scalar(0, 0, 255));

        
    }
    return input_image;

}