#ifndef __P1_MASK_HPP__
#define __P1_MASK_HPP__

#include <opencv2/highgui/highgui.hpp>

cv::Mat applyMask(cv::Mat img, cv::Mat mask){
  for(int i = 0; i < mask.rows; i++) {
    for(int j = 0; j < mask.cols; j++) {
      int px = mask.at<uchar>(i, j);
      if(px == 255){
        mask.at<uchar>(i, j) = img.at<uchar>(i, j);
      }
    }
  }
  return mask;
}

#endif
