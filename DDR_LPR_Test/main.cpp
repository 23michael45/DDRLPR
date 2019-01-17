#include "Interface.h"

int main(int argc, char **argv)
{

	std::vector<std::string> files;
	files.push_back("res/1.jpg");
	files.push_back("res/2.jpg");
	files.push_back("res/3.jpg");
	files.push_back("res/4.jpg");
	files.push_back("res/5.jpg");



	DDRLPR::LPRInterface DDRInterface;

	for (auto file : files)
	{
		auto nums = DDRInterface.Recognize(file);

		for (auto num : nums)
		{
			printf("\n%s", num.c_str());
		}

	}



	return 1;
}