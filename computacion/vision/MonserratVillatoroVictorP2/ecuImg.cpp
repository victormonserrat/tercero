#include <string>
#include <cstdlib>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv/cv.h"

#include "p2_getopt.hpp"
#include "p2_equalization.hpp"

int channel = 0;

int main(int argc, char *argv[]){
  bool rflag, bflag, sflag, iflag, oflag, mflag;
  std::string input, output, mask;
  unsigned int rvalue = 0, svalue;
  std::vector<int> h(256);
  cv::Mat m;
  if(p2::getoptions(argc, argv, rflag, rvalue, bflag, sflag, svalue, iflag, input, oflag, output, mflag, mask) == EXIT_SUCCESS){
    cv::Mat in = cv::imread(input, -1);
    if(!in.data){
      std::cout << "No se puede abrir la imagen" << std::endl;
      return EXIT_FAILURE;
    }
    if(mflag){
      m = cv::imread(mask, 0);
      if(!m.data){
        std::cout << "No se puede abrir la máscara" << std::endl;
        return EXIT_FAILURE;
      }
    }
    if(in.channels() >= 3){
      cv::cvtColor(in, in, CV_BGR2HSV);
      channel = 2;
    }
    std::vector<cv::Mat> channels;
    cv::split(in, channels);
    if(rvalue == 0){
      if(mflag){
        histogram(h, in, m, channel);
        accumulate(h);
        normalize(h);
        equalize(in, h, m, channel);
      }else{
        histogram(h, in, channel);
        accumulate(h);
        normalize(h);
        equalize(in, h, channel);
      }
    }else{
      cv::Mat aux = in.clone();
      if(mflag){
        for(int x = rvalue; x < channels[2].rows-rvalue; x++){
          for(int y = rvalue; y < channels[2].cols-rvalue; y++){
            cv::Mat window(aux, cv::Rect(y-rvalue, x-rvalue, 2*rvalue+1, 2*rvalue+1));
            cv::Mat windowMask(m, cv::Rect(y-rvalue, x-rvalue, 2*rvalue+1, 2*rvalue+1));
            histogram(h, window, windowMask, channel);
            accumulate(h);
            normalize(h);
            if(m.at<uchar>(x, y) != 0){
              in.at<cv::Vec3b>(x, y)[channel] = h[aux.at<cv::Vec3b>(x, y)[channel]];
            }
          }
        }
      }else{
        for(int x = rvalue; x < channels[2].rows-rvalue; x++){
          for(int y = rvalue; y < channels[2].cols-rvalue; y++){
            cv::Mat window(aux, cv::Rect(y-rvalue, x-rvalue, 2*rvalue+1, 2*rvalue+1));
            histogram(h, window, channel);
            accumulate(h);
            normalize(h);
            in.at<cv::Vec3b>(x, y)[channel] = h[aux.at<cv::Vec3b>(x, y)[channel]];
          }
        }
      }
    }
    if(in.channels() >= 3){
      cv::cvtColor(in, in, CV_HSV2BGR);
    }
    imwrite(output+".png", in);
    imshow("image", in);
    cv::waitKey(0);
    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}
