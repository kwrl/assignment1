#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#define WINDOW_NAME "Coolio"

void load_image(cv::Mat &image, char* name) {
    image = cv::imread(name, CV_LOAD_IMAGE_COLOR);
}

void show_image(cv::Mat &image) {
    cv::namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
    cv::imshow(WINDOW_NAME, image);
    cv::waitKey(0);
    cv::destroyWindow(WINDOW_NAME);
} 
void convert_to_grayscale(cv::Mat &colorImage, cv::Mat &grayscaleImage) {
    cv::Vec3b color;
    grayscaleImage = cv::Mat(colorImage.size(), CV_8UC1);
    for(int ii = 0; ii < grayscaleImage.size().width; ii++) {
        for(int jj= 0; jj < grayscaleImage.size().height; jj++) {
            color = colorImage.at<cv::Vec3b>(ii, jj); 
            grayscaleImage.at<uchar>(ii, jj) = (color[0] + color[1] + color[2])/3;
        }
    }
}

void invert(cv::Mat &image) {
    cv::MatIterator_<uchar> it, end; 
    for( it = image.begin<uchar>(), end = image.end<uchar>(); it != end; ++it) {
        *it = 255 -*it; 
    }
}

void gamma(cv::Mat &image, float y) {
    cv::MatIterator_<uchar> it, end; 
    for( it = image.begin<uchar>(), end = image.end<uchar>(); it != end; ++it) {
        *it = std::pow(*it, y);
    }
}

void convolute(cv::Mat &inputImage, cv::Mat &convolutedImg) {
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        std::cout << "Too few arguments" << std::endl;
        return 1;
    }

    cv::Mat originalImg, convolutedImg;
    std::vector<cv::Mat> channels(3);

    load_image(originalImg, argv[1]);
    show_image(originalImg);

    cv::split(originalImg, channels);

    uchar data[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1},
    };
    
    auto kernel = cv::Mat(3, 3, &data);

    cv::merge(channels, originalImg);

    show_image(originalImg); 

    return 0;
}
