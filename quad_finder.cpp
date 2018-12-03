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
  }





}




