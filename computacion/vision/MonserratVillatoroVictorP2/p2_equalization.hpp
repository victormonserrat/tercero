#ifndef __P2_EQUALIZATION_HPP__
#define __P2_EQUALIZATION_HPP__

#include <vector>
#include <opencv2/highgui/highgui.hpp>

void histogram(std::vector<int> &h, cv::Mat const &img, unsigned int const &channel);
void histogram(std::vector<int> &h, cv::Mat const &img, cv::Mat const &mask, unsigned int const &channel);
void accumulate(std::vector<int> &h);
void normalize(std::vector<int> &h);
void equalize(cv::Mat &img, std::vector<int> const &h, unsigned int const &channel);
void equalize(cv::Mat &img, std::vector<int> const &h, cv::Mat const &mask, unsigned int const &channel);

#endif
