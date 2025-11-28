#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>


#define AVX512 L"AVX512\\"
#define AVX2 L"AVX2\\"
#define SSE2 L"SSE2\\"

#define SANDBOX L"SandBox\\Sandbox.dll"

#define SDL_DLL L"SDL2.dll"
#define SDL_START_PATH L"..\\..\\..\\SDL\\DLLs\\"

static const wchar_t* SDL_DESTINATION_PATH = /*L"..\\bin\\windows\\Release\\AppStart\\"*/ SDL_DLL;

using Start = void (*)(int, char**);


inline void copyFile(std::wstring srcPath, std::wstring dstPath)
{
	std::ifstream src(srcPath.c_str(), std::ios::binary);
	std::ofstream dst(dstPath.c_str(), std::ios::binary);

	dst << src.rdbuf();
}

int main(int argc, char** argv)
{
	std::wstring path(L"..\\");

	if (IsProcessorFeaturePresent(PF_AVX512F_INSTRUCTIONS_AVAILABLE))
	{
		path += AVX512 SANDBOX;
		copyFile(SDL_START_PATH AVX512 SDL_DLL, SDL_DESTINATION_PATH);
	}
	else if (IsProcessorFeaturePresent(PF_AVX2_INSTRUCTIONS_AVAILABLE))
	{
		path += AVX2 SANDBOX;
		copyFile(SDL_START_PATH AVX2 SDL_DLL, SDL_DESTINATION_PATH);
	}
	else // SEE2
	{
		path += SSE2 SANDBOX;
		copyFile(SDL_START_PATH SSE2 SDL_DLL, SDL_DESTINATION_PATH);
	}

	HMODULE dll = LoadLibraryW(path.c_str());
	if (dll == nullptr)
	{
		wchar_t* error = new wchar_t[1024];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error, 1024, nullptr);
		std::wcout << L"error: " << error << L"Load Library" << std::endl;
		delete[] error;

		system("pause>nul");
		return 1;
	}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type"
	Start WulledEntry = reinterpret_cast<Start>(GetProcAddress(dll, "WulledEntry"));
#pragma clang diagnostic pop
	if (WulledEntry == nullptr)
	{
		wchar_t* error = new wchar_t[1024];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error, 1024, nullptr);
		std::wcout << L"error: " << error << L"Load Wulled entry" << std::endl;
		delete[] error;

		system("pause>nul");
		return 2;
	}

	WulledEntry(argc, argv);
}
