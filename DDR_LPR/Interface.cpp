#include "Interface.h"
#include <string>
#include "util.h"
#include "ModelLoader.h"
#include "resource.h"
namespace DDRLPR
{


	LPRInterface::LPRInterface()
	{
		//m_spPlateDetection = std::make_shared<DDRLPR::PlateDetection>("model/cascade.xml");
		//m_spRecognizr = std::make_shared<DDRLPR::SegmentationFreeRecognizer>("model/SegmenationFree-Inception.prototxt", "model/SegmenationFree-Inception.caffemodel");

		std::wstring moduleName = (L"DDR_LPR.dll");
		InitModel(moduleName);
		
	}
	
	LPRInterface::LPRInterface(std::wstring moduleName)
	{
		InitModel(moduleName);
	}

	void LPRInterface::InitModel(std::wstring moduleName)
	{
		ModelLoader cascade(moduleName, IDR_CASCADE);

		const char* cascade_buf = (const char*)cascade.GetAddr();
		size_t cascade_len = cascade.GetSize();
		m_spPlateDetection = std::make_shared<DDRLPR::PlateDetection>(cascade_buf, cascade_len);



		ModelLoader proto(moduleName, IDR_INCEPTION_PROTO);
		const char* proto_buf = (const char*)proto.GetAddr();
		size_t proto_len = proto.GetSize();

		ModelLoader model(moduleName, IDR_INCEPTION_MODEL);
		const char* inception_buf = (const char*)model.GetAddr();
		size_t inception_len = model.GetSize();
		m_spRecognizr = std::make_shared<DDRLPR::SegmentationFreeRecognizer>(proto_buf, proto_len, inception_buf, inception_len);

	}

	LPRInterface::~LPRInterface()
	{
	}

	std::vector<std::string> LPRInterface::Recognize(std::string filename)
	{

		cv::Mat image = cv::imread(filename.c_str());
		std::vector<DDRLPR::PlateInfo> plates;
		m_spPlateDetection->plateDetectionRough(image, plates);

		std::vector<std::string> platenums;

		for (DDRLPR::PlateInfo platex : plates)
		{
			drawRect(image, platex.getPlateRect());


			cv::Mat imagerec = platex.getPlateImage();
			std::pair<std::string, float> res = m_spRecognizr->SegmentationFreeForSinglePlate(imagerec, DDRLPR::CH_PLATE_CODE);
			platenums.push_back(res.first);
		}

		

		return platenums;
	}
}