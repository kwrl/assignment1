#include "utils.h"

void convert_to_grayscale(cv::Mat &colorImage, cv::Mat &grayscaleImage) {
    cv::Vec3b color;
    grayscaleImage = cv::Mat(colorImage.size(), CV_8UC1);
    for(int ii = 0; ii < grayscaleImage.size().width; ii++) {
        for(int jj= 0; jj < grayscaleImage.size().height; jj++) {
            color = colorImage.at<cv::Vec3b>(ii, jj); 
            grayscaleImage.at<uchar>(ii, jj) = (color[0] 
                                                + color[1] 
                                                + color[2])/3;
        }
    }

}
void convert_to_grayscale_weighted(cv::Mat &colorImage, cv::Mat &grayscaleImage, cv::Vec3f &weights) {
    cv::Vec3b color;
    grayscaleImage = cv::Mat(colorImage.size(), CV_8UC1);
    for(int ii = 0; ii < grayscaleImage.size().width; ii++) {
        for(int jj= 0; jj < grayscaleImage.size().height; jj++) {
            color = colorImage.at<cv::Vec3b>(ii, jj); 
            grayscaleImage.at<uchar>(ii, jj) = (color[0]*weights[0] 
                                                + color[1]*weights[1] 
                                                + color[2]*weights[2]);
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

