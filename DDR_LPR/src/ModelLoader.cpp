#include "ModelLoader.h"
ModelLoader::ModelLoader(std::string modulename, int resource_id)
{
	const std::string resource_class = "MODELS";

	hModule = GetModuleHandle(modulename.c_str()); // get the handle to the current module (the executable file)
	hResource = FindResource(hModule, MAKEINTRESOURCE(resource_id), resource_class.c_str()); // substitute RESOURCE_ID and RESOURCE_TYPE.
	hMemory = LoadResource(hModule, hResource);
}

ModelLoader::~ModelLoader()
{
	if (hMemory)
	{
		FreeResource(hMemory);
	}
}

size_t ModelLoader::GetSize()
{
	DWORD dwSize = SizeofResource(hModule, hResource);
	return dwSize;
}

void* ModelLoader::GetAddr()
{
	return LockResource(hMemory);;
}

