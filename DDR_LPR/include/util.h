#include <opencv2/opencv.hpp>
namespace DDRLPR{


	const std::vector<std::string> CH_PLATE_CODE = { "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "³", "ԥ", "��", "��", "��", "��",
									 "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A",
									 "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
									 "Y", "Z","��","ѧ","ʹ","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��" };


    template <class T> void swap ( T& a, T& b )
    {
        T c(a); a=b; b=c;
    }
    template <class T> T min(T& a,T& b )
    {
        return a>b?b:a;
    }

    cv::Mat cropFromImage(const cv::Mat &image,cv::Rect rect);

    cv::Mat cropBox2dFromImage(const cv::Mat &image,cv::RotatedRect rect);

    cv::Mat calcHist(const cv::Mat &image);
    
    float computeSimilir(const cv::Mat &A,const cv::Mat &B);


	int judgeCharRange(int id);
	std::pair<std::string, float> decodeResults(cv::Mat code_table, std::vector<std::string> mapping_table, float thres);


	std::string decodeResults(cv::Mat code_table, std::vector<std::string> mapping_table);

	void drawRect(cv::Mat image, cv::Rect rect);


}//namespace util
