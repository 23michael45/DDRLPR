#ifndef SWIFTPR_SEGMENTATIONFREERECOGNIZER_H
#define SWIFTPR_SEGMENTATIONFREERECOGNIZER_H

#include "Recognizer.h"
namespace DDRLPR{


    class SegmentationFreeRecognizer{
    public:
        const int CHAR_INPUT_W = 14;
        const int CHAR_INPUT_H = 30;
        const int CHAR_LEN = 84;

		SegmentationFreeRecognizer(const char *bufferProto, size_t lenProto, const char *bufferModel, size_t lenModel);
		SegmentationFreeRecognizer(std::string prototxt, std::string caffemodel);
        std::pair<std::string,float> SegmentationFreeForSinglePlate(cv::Mat plate,std::vector<std::string> mapping_table);


    private:
        cv::dnn::Net net;

    };

}
#endif //SWIFTPR_SEGMENTATIONFREERECOGNIZER_H
