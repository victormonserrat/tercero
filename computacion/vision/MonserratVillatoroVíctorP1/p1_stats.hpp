#ifndef __P1_STATS_HPP__
#define __P1_STATS_HPP__

#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>

void stats(cv::Mat roi_img, bool mflag, cv::Mat mask){
  std::cout << "Canales: " << roi_img.channels() << std::endl;
  std::cout << "Ancho: " << roi_img.cols << std::endl;
  std::cout << "Alto: " << roi_img.rows << std::endl;
  std::vector<cv::Mat> channels;
  cv::split(roi_img, channels);
  int min[roi_img.channels()];
  int max[roi_img.channels()];
  double sum[roi_img.channels()];
  double sum2[roi_img.channels()];
  int n0[roi_img.channels()];
  int pa[roi_img.channels()];
  int na[roi_img.channels()];
  double n = 0;
  for(int c = 0; c < roi_img.channels(); c++){
    min[c] = 255;
    max[c] = 0;
    sum[c] = 0;
    sum2[c] = 0;
    n0[c] = 0;
    pa[c] = 0;
    na[c] = 0;
  }
  for(int i = 0; i < roi_img.rows; i++){
    for(int j = 0; j < roi_img.cols; j++){
      if(!mflag or mask.at<uchar>(i, j) == 255){
        for(int c = 0; c < roi_img.channels(); c++){
          double px = channels[c].at<uchar>(i, j);
          if(px < min[c]){
            min[c] = px;
          }
          if(px > max[c]){
            max[c] = px;
          }
          sum[c] += px;
          sum2[c] += px * px;
          if(px == 0){
            n0[c] += 1;
          }else if(px > 0){
            pa[c] += 1;
          }else{
            na[c] += 1;
          }
        }
        n += 1;
      }
    }
  }
  double av[roi_img.channels()];
  double var[roi_img.channels()];
  double ske[roi_img.channels()];
  double skeNum[roi_img.channels()];
  double skeDen[roi_img.channels()];
  for(int c = 0; c < roi_img.channels(); c++){
    std::cout << std::endl;
    std::cout << "Canal: " << c+1 << std::endl;
    std::cout << "Valor mínimo: " << min[c] << std::endl;
    std::cout << "Valor máximo: " << max[c] << std::endl;
    av[c] = sum[c]/ n;
    std::cout << "Valor medio: " << av[c] << std::endl;
    var[c] = 0;
    skeNum[c] = 0;
    skeDen[c] = 0;
    for(int i = 0; i < roi_img.rows; i++){
      for(int j = 0; j < roi_img.cols; j++){
        if(!mflag or mask.at<uchar>(i, j) == 255){
          double px = channels[c].at<uchar>(i, j);
          var[c] += (px - av[c]) * (px - av[c]);
          skeNum[c] += (px - av[c]) * (px - av[c]) * (px - av[c]);
        }
      }
    }
    var[c] = var[c] / n;
    skeDen[c] = n * pow(var[c], (float)3/2);
    ske[c] = skeNum[c] / skeDen[c];
    std::cout << "Varianza: " << var[c] << std::endl;
    std::cout << "Sumatorio: " << sum[c] << std::endl;
    std::cout << "Sumatorio de cuadrados: " << sum2[c] << std::endl;
    std::cout << "Área positiva: " << pa[c] << std::endl;
    std::cout << "Área negativa: " << na[c] << std::endl;
    std::cout << "Número de ceros: " << n0[c] << std::endl;
    std::cout << "Coeficiente de asimetría: " << ske[c] << std::endl;
  }
}

#endif
