#include "Interface.h"

int main(int argc, char **argv)
{

	std::vector<std::string> files;
	files.push_back("res/1.jpg");
	files.push_back("res/2.jpg");
	files.push_back("res/3.jpg");
	files.push_back("res/4.jpg");
	files.push_back("res/5.jpg");
	files.push_back("res/6.bmp");
	files.push_back("res/7.jpg");
	files.push_back("res/8.jpg");
	files.push_back("res/9.jpg");
	files.push_back("res/10.jpg");
	files.push_back("res/11.jpg");



	DDRLPR::LPRInterface DDRInterface;

	for (auto file : files)
	{
		auto nums = DDRInterface.Recognize(file);

		for (auto num : nums)
		{
			printf("\nfile : %s  num: %s", file.c_str() ,num.c_str());
		}

	}

	getchar();

	return 1;
}