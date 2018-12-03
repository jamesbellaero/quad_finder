//Some code borrowed from here: https://stackoverflow.com/questions/27533203/how-do-i-use-sift-in-opencv-3-0-with-c
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>





int main(int argc, char** argv){
  
  // Load the ilbrary
  ifstream descriptorReader("/mnt/c/Users/James/Desktop/imgs/descriptors.txt");
  string line;
  cv::Mat descriptorLib(1,128,CV_8UC1);
  bool first = true;

  while(getline(descriptorReader,line)){
    string buff = ""; 
    cv::Mat row(1,128,CV_8UC1);
    int iter = 0;

    for(int i=0;i<line.length();i++){
      char curr = line.at(i);

      if(i==line.length()-1){ // End of line
        int value = atoi(buff);
        row(iter) = value;
        buff = "";
        continue;
      }
      if(curr == ","){
        int value = atoi(buff);
        row(iter++) = value;
        buff = "";
        continue;
      }
      buff = buff + std::string(curr);
    }
    if(first){
      row.copyTo(descriptorLib);
      first = false;
      continue;
    }
    descriptorLib.push_back(row);


    // Grab image (this will be ros in the future)
    cv::Mat img = imread("/mnt/c/Users/James/Desktop/imgs/verification/img.jpg");
    cv::Mat imgGray;
    cv::cvtColor(img,imgGray,cv::COLOR_BGR2GRAY);

    std::vector<cv::KeyPoint> keypoints;    
    sifter->detect( imgGray, keypoints);
    //-- Step 2: Calculate descriptors (feature vectors)    
    cv::Mat descriptors;    
    sifter->compute( imgGray, keypoints, descriptors );

    cv::BFMatcher matcher;
    std::vector< cv::DMatch > matches;
    matcher.match( descriptors, descriptorLib, matches );
    
    std::vector<cv::KeyPoint> kpMatched; 
    for(int i=0;i<matches.size();i++){
      kpMatched.push_back(keypoints[matches[i].queryIdx]);
    }

    cv::Mat imgKp;
    cv::drawKeypoints(imgGray,kpMatched,imgKp);
    imshow("Keypoints",imgKp);

  }





}




