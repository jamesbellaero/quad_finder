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
  std::ifstream descriptorReader("/mnt/c/Users/James/Desktop/imgs/descriptors.txt");
  std::string line;
  cv::Mat descriptorLib(1,128,CV_32F);
  bool first = true;
  char comma_int = ',';

  while(getline(descriptorReader,line)){
    std::string buff = ""; 
    cv::Mat row(1,128,CV_32F);
    int iter = 0;
    
    for(int i=0;i<line.length();i++){
      char curr = line.at(i);
      // std::cout<<comma_int<<"\t"<<curr<<std::endl;
      if(i==line.length()-1){ // End of line
        float value = atof(buff.c_str());
        row.data[iter] = value;
        buff = "";
        continue;
      }
      if(curr == comma_int){
        float value = atof(buff.c_str());
        row.data[iter++] = value;
        buff = "";
        continue;
      }
      buff.push_back(curr);
    }
    if(first){
      row.copyTo(descriptorLib);
      first = false;
      continue;
    }
    descriptorLib.push_back(row);
  }
  std::cout<<"Loaded "<<descriptorLib.rows<<" descriptors into the library";
   // Grab image (this will be ros in the future)
  cv::Mat img = cv::imread("/mnt/c/Users/James/Desktop/imgs/verification/img.jpg");
  cv::Mat imgGray;
  cv::cvtColor(img,imgGray,cv::COLOR_BGR2GRAY);

  //Suspicious maths below
  cv::Ptr<cv::Feature2D> sifter = cv::xfeatures2d::SIFT::create();
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




