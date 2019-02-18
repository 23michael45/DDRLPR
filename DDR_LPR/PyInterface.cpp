#include "PyInterface.h"
#include "ModelLoader.h"
#include "resource.h"
std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}


void Init()
{
	std::string moduleName = ("ddrlpr.pyd");
	ModelLoader cascade(moduleName,IDR_CASCADE);

	const char* cascade_buf = (const char*)cascade.GetAddr();
	size_t cascade_len = cascade.GetSize();
	auto sp = std::make_shared<DDRLPR::PlateDetection>(cascade_buf, cascade_len);



}

bool Load(std::string fn)
{
	cv::Mat image = cv::imread(fn.c_str());
	if (!image.data)
	{
		return false;
	}
	return true;
}

cv::Mat GetImage(std::string fn)
{
	cv::Mat image = cv::imread(fn.c_str());
	if (!image.data)
	{
		return cv::Mat();
	}
	return image;
}


py::str Recognize(std::string filename)
{
	std::string moduleName = ("ddrlpr.pyd");
	DDRLPR::LPRInterface lpinterface(moduleName);
	auto vec = lpinterface.Recognize(filename);

	const std::string str = string_To_UTF8(vec[0]);
	printf("\n rec:%s", str.c_str());

	py::str py_s(str);
	return py_s;
}
int add(int i, int j)
{
	return i + j;
}

PYBIND11_MODULE(ddrlpr, m)
{
	// optional module docstring
	m.doc() = "Recognize LPR";

	m.def("Init", &Init, "Init LPR");
	m.def("Load", &Load, "Load Image");
	m.def("Recognize", &Recognize, "Recognize LPR");

	m.def("add", &add, "A function which adds two numbers", py::arg("i") = 1, py::arg("j") = 2);


	m.def("GetImage", &GetImage);

	py::class_<cv::Mat>(m, "Image", py::buffer_protocol())
		.def_buffer([](cv::Mat& im) -> py::buffer_info {
		return py::buffer_info(
			// Pointer to buffer
			im.data,
			// Size of one scalar
			sizeof(unsigned char),
			// Python struct-style format descriptor
			py::format_descriptor<unsigned char>::format(),
			// Number of dimensions
			3,
			// Buffer dimensions
			{ im.rows, im.cols, im.channels() },
			// Strides (in bytes) for each index
				{
					sizeof(unsigned char) * im.channels() * im.cols,
					sizeof(unsigned char) * im.channels(),
					sizeof(unsigned char)
				}
				);
	});

}