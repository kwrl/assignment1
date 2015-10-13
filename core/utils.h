#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

void convert_to_grayscale(cv::Mat &colorImage, cv::Mat &grayscaleImage);

void convert_to_grayscale_weighted(cv::Mat &colorImage, cv::Mat &grayscaleImage, cv::Vec3f &weights);

void invert(cv::Mat &image);

void gamma(cv::Mat &image, float y);

float single_pixel_convolution(cv::Mat &pixels, const cv::Mat &kernel);

void convolution(cv::Mat &inputImg, cv::Mat &outputImg, const cv::Mat &kernel, float scalar);
#endif
