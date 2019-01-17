#include <windows.h>
#include <string>


class ModelLoader {

public:
	ModelLoader(int resource_id);
	~ModelLoader();

	size_t GetSize();
	void* GetAddr();

private:
	HMODULE hModule = nullptr;
	HRSRC hResource = nullptr;
	HGLOBAL hMemory = nullptr;


};