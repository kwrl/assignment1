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

float single_pixel_convolution(cv::Mat &pixels, const cv::Mat &kernel) {
    float sum = 0;
    auto pIt = pixels.begin<uchar>();
    auto kIt = kernel.begin<uchar>();
    auto pEnd = pixels.end<uchar>();
    for(; pIt != pEnd; ++pIt, ++kIt ) 
    {
        sum += static_cast<float>(*kIt)*static_cast<float>(*pIt);
    }
    return sum;
}

void convolution(cv::Mat &inputImg, cv::Mat &outputImg, const cv::Mat &kernel, float scalar) {
    cv::Size imgSize = inputImg.size(); 
    outputImg = cv::Mat(imgSize, CV_8UC1);

    for(int ii = 1; ii < imgSize.width-1; ii++) {
        for(int jj = 1; jj < imgSize.height-1; jj++) {
            auto submat = inputImg.rowRange(ii-1, ii+2).colRange(jj-1, jj+2);
            auto p = single_pixel_convolution(
                submat,
                kernel
            );
            auto it = submat.begin<uchar>();
            auto end = submat.end<uchar>();

            outputImg.at<uchar>(ii,jj) = static_cast<uchar>(p*scalar);
        }
    }
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        std::cout << "Too few arguments" << std::endl;
        return 1;
    }

    cv::Mat originalImg, convolutedImg, kernel, grayscale, gammaImg;
    load_image(originalImg, argv[1]);
    show_image(originalImg);
    
    convert_to_grayscale(originalImg, grayscale);
    show_image(grayscale);

    gamma(grayscale, 0.8);
    show_image(grayscale);
    
    
    /*
    uchar data[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1},
    };
    kernel = cv::Mat(3, 3, CV_8UC1, &data);
 
    load_image(originalImg, argv[1]);
    show_image(originalImg);

    for(int ii = 0; ii < 3; ii++) {
        for(int jj= 0; jj < 3; jj++) {
            auto color = originalImg.at<cv::Vec3b>(ii,jj);
            std::cout << static_cast<unsigned int>(color[2]) << "\t";
        }
        std::cout << std::endl;
    }

    std::vector<cv::Mat> channels(3);
    cv::split(originalImg, channels);

    convolution(channels[0], convolutedImg, kernel, 1.0f/16.0f);
    channels[0] = convolutedImg;
    convolution(channels[1], convolutedImg, kernel, 1.0f/16.0f);
    channels[1] = convolutedImg;
    convolution(channels[2], convolutedImg, kernel, 1.0f/16.0f);
    channels[2] = convolutedImg;

    cv::merge(channels, originalImg);

    for(int ii = 0; ii < 3; ii++) {
        for(int jj= 0; jj < 3; jj++) {
            auto color = originalImg.at<cv::Vec3b>(ii,jj);
            std::cout << static_cast<unsigned int>(color[2]) << "\t";
        }
        std::cout << std::endl;
    }

    show_image(originalImg); 
    */
    return 0;
}
