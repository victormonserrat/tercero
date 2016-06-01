#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "p4_getopt.hpp"

int main(int argc, char *argv[]){
  bool tflag = false, iflag = false, oflag = false;
  int tvalue;
  std::string ivalue, ovalue;
  if(p4::getoptions(argc, argv, tflag, tvalue, iflag, ivalue, oflag, ovalue) == EXIT_SUCCESS){

    cv::VideoCapture input;
    input.open(ivalue);
    if(!input.isOpened()){
      std::cout << "No es posible abrir el video" << std::endl;
      return EXIT_FAILURE;
    }

    if(!tflag){
      tvalue = 0;
    }

    cv::VideoWriter output;
    int ex = static_cast<int>(input.get(CV_CAP_PROP_FOURCC)); //Get Codec Type- Int form
    cv::Size S = cv::Size((int)input.get(CV_CAP_PROP_FRAME_WIDTH), (int)input.get(CV_CAP_PROP_FRAME_HEIGHT));
    output.open(ovalue, ex, 30, S, true);
    if(!output.isOpened()){
      std::cout << "No es posible crear el video de salida" << std::endl;
      return EXIT_FAILURE;
    }

    cv::Mat actual_frame, gs_actual_frame;
    cv::Mat previous_frame, gs_previous_frame;
    cv::Mat gs_absdiff;
    input >> previous_frame;
    cv::namedWindow("input", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Umbral T", "input", &tvalue, 255);
    cv::imshow("input", previous_frame);
    cv::cvtColor(previous_frame, gs_previous_frame, CV_BGR2GRAY);
    cv::Mat gs_planes = gs_previous_frame.clone();
    int nFrame = 1;
    while(true){
      if(input.read(actual_frame)){
        cv::Mat planes = actual_frame.clone();
        cv::cvtColor(actual_frame, gs_actual_frame, CV_BGR2GRAY);
        cv::imshow("input", actual_frame);
        cv::absdiff(gs_actual_frame, gs_previous_frame, gs_absdiff);
        for(int i = 0; i < gs_actual_frame.rows; i++){
          for(int j = 0; j < gs_actual_frame.cols; j++){
            if(gs_absdiff.at<uchar>(i, j) > tvalue){
              gs_planes.at<uchar>(i, j) = 255;
            }else{
              for(int k = 0; k < planes.channels(); k++){
                planes.at<cv::Vec3b>(i, j)[k] = 0;
              }
              gs_planes.at<uchar>(i, j) = 0;
            }
          }
        }
        cv::imshow("planes", planes);
        output << planes;
        cv::imshow("gs_planes", gs_planes);
        int k = cv::waitKey(30);
        if(k == 27){
          break;
        }else if(k == 32){
          cv::imwrite("sal_" + std::to_string(nFrame) + ".png", planes);
        }
        gs_previous_frame = gs_actual_frame.clone();
        nFrame++;
      }else{
        break;
      }
    }

    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}
