#include "SegmentationFreeRecognizer.h"
#include "util.h"

namespace DDRLPR {
    SegmentationFreeRecognizer::SegmentationFreeRecognizer(std::string prototxt, std::string caffemodel) {
        net = cv::dnn::readNetFromCaffe(prototxt, caffemodel);
    }


	SegmentationFreeRecognizer::SegmentationFreeRecognizer(const char *bufferProto, size_t lenProto, const char *bufferModel, size_t lenModel)
	{
		net = cv::dnn::readNetFromCaffe(bufferProto, lenProto,bufferModel,lenModel);

	}

	std::pair<std::string, float> SegmentationFreeRecognizer::SegmentationFreeForSinglePlate(cv::Mat Image, std::vector<std::string> mapping_table) {
        cv::transpose(Image,Image);
        cv::Mat inputBlob = cv::dnn::blobFromImage(Image, 1 / 255.0, cv::Size(40,160));
        net.setInput(inputBlob, "data");
        cv::Mat char_prob_mat = net.forward();
        return decodeResults(char_prob_mat,mapping_table,0.00);
    }
}
