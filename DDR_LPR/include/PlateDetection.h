#ifndef SWIFTPR_PLATEDETECTION_H
#define SWIFTPR_PLATEDETECTION_H

#include <opencv2/opencv.hpp>
#include "PlateInfo.h"
#include <vector>
namespace DDRLPR{
    class PlateDetection{
    public:
        PlateDetection(std::string filename_cascade);
        PlateDetection();
        void LoadModel(std::string filename_cascade);
        void plateDetectionRough(cv::Mat InputImage,std::vector<DDRLPR::PlateInfo>  &plateInfos,int min_w=36,int max_w=800);
//        std::vector<DDRLPR::PlateInfo> plateDetectionRough(cv::Mat InputImage,int min_w= 60,int max_h = 400);


//        std::vector<DDRLPR::PlateInfo> plateDetectionRoughByMultiScaleEdge(cv::Mat InputImage);



    private:
        cv::CascadeClassifier cascade;


    };

}// namespace DDRLPR

#endif //SWIFTPR_PLATEDETECTION_H
