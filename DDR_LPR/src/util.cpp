#include "util.h"

cv::Mat DDRLPR::cropFromImage(const cv::Mat &image, cv::Rect rect)
{
	int w = image.cols - 1;
	int h = image.rows - 1;
	rect.x = std::max(rect.x, 0);
	rect.y = std::max(rect.y, 0);
	rect.height = std::min(rect.height, h - rect.y);
	rect.width = std::min(rect.width, w - rect.x);
	cv::Mat temp(rect.size(), image.type());
	cv::Mat cropped;
	temp = image(rect);
	temp.copyTo(cropped);
	return cropped;
}

cv::Mat DDRLPR::cropBox2dFromImage(const cv::Mat &image, cv::RotatedRect rect)
{
	cv::Mat M, rotated, cropped;
	float angle = rect.angle;
	cv::Size rect_size(rect.size.width, rect.size.height);
	if (rect.angle < -45.) {
		angle += 90.0;
		swap(rect_size.width, rect_size.height);
	}
	M = cv::getRotationMatrix2D(rect.center, angle, 1.0);
	cv::warpAffine(image, rotated, M, image.size(), cv::INTER_CUBIC);
	cv::getRectSubPix(rotated, rect_size, rect.center, cropped);
	return cropped;
}

cv::Mat DDRLPR::calcHist(const cv::Mat &image)
{
	cv::Mat hsv;
	std::vector<cv::Mat> hsv_planes;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	cv::split(hsv, hsv_planes);
	cv::Mat hist;
	int histSize = 256;
	float range[] = { 0,255 };
	const float* histRange = { range };
	cv::calcHist(&hsv_planes[0], 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, true);
	return hist;
}

float DDRLPR::computeSimilir(const cv::Mat &A, const cv::Mat &B)
{
	cv::Mat histA, histB;
	histA = calcHist(A);
	histB = calcHist(B);
	return cv::compareHist(histA, histB, CV_COMP_CORREL);
}

int DDRLPR::judgeCharRange(int id)
{
	return id < 31 || id>63;
}

std::string DDRLPR::decodeResults(cv::Mat code_table, std::vector<std::string> mapping_table)
{
	cv::MatSize mtsize = code_table.size;
	int sequencelength = mtsize[2];
	int labellength = mtsize[1];
	cv::transpose(code_table.reshape(1, 1).reshape(1, labellength), code_table);
	std::string name = "";
	std::vector<int> seq(sequencelength);
	for (int i = 0; i < sequencelength; i++) {
		float *fstart = ((float *)(code_table.data) + i * labellength);
		int id = std::max_element(fstart, fstart + labellength) - fstart;
		seq[i] = id;
	}
	for (int i = 0; i < sequencelength; i++)
	{
		if (seq[i] != labellength - 1 && (i == 0 || seq[i] != seq[i - 1]))
			name += mapping_table[seq[i]];
	}
	return name;
}

void DDRLPR::drawRect(cv::Mat image, cv::Rect rect)
{
	cv::Point p1(rect.x, rect.y);
	cv::Point p2(rect.x + rect.width, rect.y + rect.height);
	cv::rectangle(image, p1, p2, cv::Scalar(0, 255, 0), 1);
}

std::pair<std::string, float> DDRLPR::decodeResults(cv::Mat code_table, std::vector<std::string> mapping_table, float thres)
{
	cv::MatSize mtsize = code_table.size;
	int sequencelength = mtsize[2];
	int labellength = mtsize[1];
	cv::transpose(code_table.reshape(1, 1).reshape(1, labellength), code_table);
	std::string name = "";
	std::vector<int> seq(sequencelength);
	std::vector<std::pair<int, float>> seq_decode_res;
	for (int i = 0; i < sequencelength; i++) {
		float *fstart = ((float *)(code_table.data) + i * labellength);
		int id = std::max_element(fstart, fstart + labellength) - fstart;
		seq[i] = id;
	}

	float sum_confidence = 0;
	int plate_lenghth = 0;
	for (int i = 0; i < sequencelength; i++)
	{
		if (seq[i] != labellength - 1 && (i == 0 || seq[i] != seq[i - 1]))
		{
			float *fstart = ((float *)(code_table.data) + i * labellength);
			float confidence = *(fstart + seq[i]);
			std::pair<int, float> pair_(seq[i], confidence);
			seq_decode_res.push_back(pair_);
		}
	}
	int  i = 0;
	if (seq_decode_res.size() > 1 && judgeCharRange(seq_decode_res[0].first) && judgeCharRange(seq_decode_res[1].first))
	{
		i = 2;
		int c = seq_decode_res[0].second < seq_decode_res[1].second;
		name += mapping_table[seq_decode_res[c].first];
		sum_confidence += seq_decode_res[c].second;
		plate_lenghth++;
	}

	for (; i < seq_decode_res.size(); i++)
	{
		name += mapping_table[seq_decode_res[i].first];
		sum_confidence += seq_decode_res[i].second;
		plate_lenghth++;
	}
	std::pair<std::string, float> res;
	res.second = sum_confidence / plate_lenghth;
	res.first = name;
	return res;
}

