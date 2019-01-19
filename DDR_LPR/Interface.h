#ifndef Interface_h__
#define Interface_h__
#include <string>
#include <vector>
#include "PlateDetection.h"
#include "SegmentationFreeRecognizer.h"
#include "Pipeline.h"
#include "PlateInfo.h"
#if !defined(USE_DDRLPR_DLL) // inside DLL
#   define DDRLPR_API   __declspec(dllexport)
#else // outside DLL
#   define DDRLPR_API   __declspec(dllimport)
#endif 


namespace DDRLPR
{
	class  DDRLPR_API LPRInterface
	{
	public:
		LPRInterface();
		LPRInterface(std::wstring moduleName);
		~ LPRInterface();

		void InitModel(std::wstring moduleName);

		std::vector<std::string> Recognize(std::string filename);

	private:
		std::shared_ptr<DDRLPR::PlateDetection> m_spPlateDetection;
		std::shared_ptr <DDRLPR::SegmentationFreeRecognizer> m_spRecognizr;
	};

}



#endif // Interface_h__
