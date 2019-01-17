#ifndef SWIFTPR_PIPLINE_H
#define SWIFTPR_PIPLINE_H

#include "PlateDetection.h"
#include "PlateSegmentation.h"
#include "CNNRecognizer.h"
#include "PlateInfo.h"
#include "FastDeskew.h"
#include "FineMapping.h"
#include "Recognizer.h"
#include "SegmentationFreeRecognizer.h"

namespace DDRLPR {


	const int SEGMENTATION_FREE_METHOD = 0;
	const int SEGMENTATION_BASED_METHOD = 1;

	class PipelinePR {
	public:
		GeneralRecognizer *generalRecognizer;
		PlateDetection *plateDetection;
		PlateSegmentation *plateSegmentation;
		FineMapping *fineMapping;
		SegmentationFreeRecognizer *segmentationFreeRecognizer;

		PipelinePR(std::string detector_filename,
			std::string finemapping_prototxt, std::string finemapping_caffemodel,
			std::string segmentation_prototxt, std::string segmentation_caffemodel,
			std::string charRecognization_proto, std::string charRecognization_caffemodel,
			std::string segmentationfree_proto, std::string segmentationfree_caffemodel
		);
		~PipelinePR();



		std::vector<std::string> plateRes;
		std::vector<PlateInfo> RunPiplineAsImage(cv::Mat plateImage, int method);







	};


}
#endif //SWIFTPR_PIPLINE_H
