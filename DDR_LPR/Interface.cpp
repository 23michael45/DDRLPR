#include "Interface.h"
#include <string>
#include "util.h"
namespace DDRLPR
{


	LPRInterface::LPRInterface():m_PlateDetection("model/cascade.xml"), m_Recognizr("model/SegmenationFree-Inception.prototxt", "model/SegmenationFree-Inception.caffemodel")
	{
	}


	LPRInterface::~LPRInterface()
	{
	}

	std::vector<std::string> LPRInterface::Recognize(std::string filename)
	{

		cv::Mat image = cv::imread(filename.c_str());
		std::vector<DDRLPR::PlateInfo> plates;
		m_PlateDetection.plateDetectionRough(image, plates);

		std::vector<std::string> platenums;

		for (DDRLPR::PlateInfo platex : plates)
		{
			drawRect(image, platex.getPlateRect());


			cv::Mat imagerec = platex.getPlateImage();
			std::pair<std::string, float> res = m_Recognizr.SegmentationFreeForSinglePlate(imagerec, DDRLPR::CH_PLATE_CODE);
			platenums.push_back(res.first);
		}

		

		return platenums;
	}
}