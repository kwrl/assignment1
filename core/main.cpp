#include <iostream>
#include "utils.h"

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

void task1a(int argc, char** argv) {
    cv::Mat original_img, grayscale;
    load_image(original_img, argv[1]);
    show_image(original_img);
    //First equation.
    convert_to_grayscale(original_img, grayscale);
    show_image(grayscale);

    //Second equation.
    cv::Vec3f weights = cv::Vec3f(0.2126f, 0.7152f, 0.0722f);
    convert_to_grayscale_weighted(original_img, grayscale, weights);
    show_image(grayscale); 
}

void task2a(int argc, char** argv) {
    cv::Mat original_img, grayscale;   
    load_image(original_img, argv[1]);  
    convert_to_grayscale(original_img, grayscale);

    show_image(grayscale);  //Show the image before inverting it.
    invert(grayscale);
    show_image(grayscale);  //Show the image after inverting it.
}

void task2b(int argc, char** argv) {
    cv::Mat original_img, grayscale;   
    load_image(original_img, argv[1]);  
    convert_to_grayscale(original_img, grayscale);

    show_image(grayscale);  //Show the image before transforming it.
    
    gamma(grayscale, 1.0f);  
       
    show_image(grayscale);  //Show the image after transforming it.
}

void task3a(int argc, char** argv) {
}

void task3b(int argc, char** argv) {
    cv::Mat original_img, temp, kernel, convoluted_img;   
    load_image(original_img, argv[1]);  
    show_image(original_img);  //Show the image before transforming it.

    uchar data[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1},
    };

    kernel = cv::Mat(3, 3, CV_8UC1, &data);

    std::vector<cv::Mat> channels(3);
    cv::split(original_img, channels); //Split channels into three separate images.

    convolution(channels[0], temp, kernel, 1.0f/16.0f); 
    channels[0] = temp;
    convolution(channels[1], temp, kernel, 1.0f/16.0f);
    channels[1] = temp;
    convolution(channels[2], temp, kernel, 1.0f/16.0f);
    channels[2] = temp;

    cv::merge(channels, convoluted_img); //Merge channels after applying convolution.

    show_image(convoluted_img); //Show the image after transforming it.
}

void task3c(int argc, char** argv) {
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        std::cout << "Too few arguments" << std::endl;
        return 1;
    }

    task3b(argc, argv);
    return 0;

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
