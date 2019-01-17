#include "ModelLoader.h"
ModelLoader::ModelLoader(int resource_id)
{
	const std::wstring resource_class = L"MODELS";

	hModule = GetModuleHandle(L"DDR_LPR.dll"); // get the handle to the current module (the executable file)
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

