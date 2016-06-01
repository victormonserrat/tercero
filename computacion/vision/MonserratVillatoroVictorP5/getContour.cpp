#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <vector>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "p5_getopt.hpp"

int main(int argc, char *argv[]){
  bool oflag = false, nflag = false, iflag = true;
  std::string ivalue, ovalue;
  int nvalue;
  if(p5::getoptions(argc, argv, oflag, ovalue, nflag, nvalue, iflag, ivalue) == EXIT_SUCCESS){
    cv::Mat input = cv::imread(ivalue, -1);
    if(!input.data){
      std::cout << "No ha sido posible leer la imagen" << std::endl;
      return EXIT_FAILURE;
    }
    if(!nflag){
      nvalue = 10;
    }
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(input, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    if(oflag){
      std::ofstream ofile;
      ofile.open(ovalue.c_str());
      for(size_t i = 0; i < contours.size(); i++){
        for(size_t j = 0; j < contours[i].size(); j++){
          ofile << contours[i][j].x << " " << contours[i][j].y << std::endl;
        }
      }
      ofile.close();
    }
    std::vector<double> lengths;
    std::vector<double> diameters;
    std::vector<double> areas;
    std::vector<cv::RotatedRect> rectangles;
    //std::vector<cv::RotatedRect> ellipses;
    for(size_t i = 0; i < contours.size(); i++){
      lengths.push_back(cv::arcLength(contours[i], true));
      areas.push_back(cv::contourArea(contours[i]));
      diameters.push_back(sqrt(4 * areas[i] / M_PI));
      rectangles.push_back(cv::minAreaRect(contours[i]));
      //ellipses.push_back(cv::fitEllipse(contours[i]));
    }
    for(size_t i = 0; i < contours.size(); i++){
      std::cout << "Longitud\t\t: " << lengths[i] << std::endl;

      std::cout << "Diámetro\t\t: " << diameters[i] << std::endl;

      std::cout << "Área\t\t\t: " << areas[i] << std::endl;

      std::cout << "Rectángulo básico\t: ángulo: " << rectangles[i].angle << " centro: " << rectangles[i].center;
      std::cout << " lados: [" << rectangles[i].size.width << " x " << rectangles[i].size.height << "]" << std::endl;

      std::cout << "Excentricidad\t\t: ";
      //std::cout << sqrt(1 - (pow(std::min(ellipses[i].size.width, ellipses[i].size.height), 2) / pow(std::max(ellipses[i].size.width, ellipses[i].size.height), 2))) << std::endl;
      std::cout << std::max(rectangles[i].size.width, rectangles[i].size.height) / std::min(rectangles[i].size.width, rectangles[i].size.height) << std::endl;

      cv::Rect bounding_rect = cv::boundingRect(contours[i]);
      std::cout << "Ocupación\t\t: " << areas[i] / (bounding_rect.width * bounding_rect.height) << std::endl;

      std::cout << "Compacidad\t\t: " << areas[i] / pow(lengths[i], 2) << std::endl;

      std::vector<cv::Point> convex_hull;
      cv::convexHull(contours[i], convex_hull, false);
      std::cout << "Ocupación convexa\t: " << cv::contourArea(convex_hull) / (bounding_rect.width * bounding_rect.height) << std::endl;

      std::cout << "Solidez\t\t\t: " << areas[i] / cv::contourArea(convex_hull) << std::endl;

      std::cout << "Descriptores de Fourier\t: [";
      int optimalDFTSize = cv::getOptimalDFTSize(contours[i].size());
      std::vector<cv::Point2f> optimalDFTcontour;
      for(int j = 0; j < optimalDFTSize; j++){
        optimalDFTcontour.push_back(contours[i][j%contours[i].size()]);
      }
      cv::dft(optimalDFTcontour, optimalDFTcontour);
      std::vector<double> fourier_descriptors;
      double max_fourier_descriptor = 0;
      for(size_t j = 0; j < optimalDFTcontour.size(); j++){
        //Rotation
        fourier_descriptors.push_back(sqrt(pow(optimalDFTcontour[j].x, 2) + pow(optimalDFTcontour[j].y, 2)));
        max_fourier_descriptor = std::max(max_fourier_descriptor, fourier_descriptors[j]);
      }
      // Normalize (scale) and show
      fourier_descriptors[1] /= max_fourier_descriptor;
      std::cout << fourier_descriptors[1];
      for(size_t j = 2; (int) j < nvalue+1 and j < contours[i].size(); j++){
        fourier_descriptors[j] /= max_fourier_descriptor;
        std::cout << " " << fourier_descriptors[j];
      }
      std::cout << "]" << std::endl;
    }

    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}
