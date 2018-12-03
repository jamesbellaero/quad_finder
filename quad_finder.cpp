





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




