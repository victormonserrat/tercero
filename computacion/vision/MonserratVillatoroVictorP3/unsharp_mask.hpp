#ifndef __UNSHARP_MASK_HPP__
#define __UNSHARP_MASK_HPP__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

void shiftDFT(cv::Mat &fImage);
void create_butterworth_lowpass_filter(cv::Mat &dft_Filter, float D, int n);
cv::Mat create_spectrum_magnitude_display(cv::Mat &complexImg, bool rearrange);

#endif
