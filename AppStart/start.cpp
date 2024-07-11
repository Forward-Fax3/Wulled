#include <Windows.h>
#include <iostream>


#define BASE_FILEPATH L"C:\\Dev\\Projects\\personal\\c++\\Wulled\\bin\\windows-x86_64-" 

#if defined _DEBUG
#define CONFIG "Debug-"
#elif defined _RELEASE
#define CONFIG "Release-"
#elif defined _DIST
#define CONFIG "Dist-"
#else
#error "No configuration specified"
#endif

#define AVX512 "AVX512\\"
#define AVX2 "AVX2\\"
#define SEE4_2 "SEE4.2\\"

#define SANDBOX "SandBox\\SandBox.dll"

typedef void (*Start)(int, char**);


int main(int argc, char** argv)
{
	HINSTANCE dll = nullptr;
	if (IsProcessorFeaturePresent(PF_AVX512F_INSTRUCTIONS_AVAILABLE))
	{
//		const wchar_t* path = BASE_FILEPATH CONFIG AVX512 SANDBOX;
		const wchar_t* path = L"C:\\Dev\\Projects\\personal\\c++\\Wulled\\bin\\windows-x86_64-Release-AVX512\\SandBox\\SandBox.dll";;
		dll = LoadLibraryW(path);
	}
	else if (IsProcessorFeaturePresent(PF_AVX2_INSTRUCTIONS_AVAILABLE))
	{
//		const wchar_t* path = BASE_FILEPATH CONFIG AVX2 SANDBOX;
		const wchar_t* path = L"C:\\Dev\\Projects\\personal\\c++\\Wulled\\bin\\windows-x86_64-Release-AVX2\\SandBox\\SandBox.dll";
		dll = LoadLibraryW(path);
	}
	else // SEE2
	{
//		const wchar_t* path = BASE_FILEPATH CONFIG SEE4_2 SANDBOX;
		const wchar_t* path = L"C:\\Dev\\Projects\\personal\\c++\\Wulled\\bin\\windows-x86_64-Release-SSE4.2\\SandBox\\SandBox.dll";
		dll = LoadLibraryW(path);
	}

	if (dll == nullptr)
	{
		wchar_t* error = new wchar_t[1024];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error, 1024, NULL);
		std::wcout << L"error: " << error << L"Load Library" << std::endl;
		delete[] error;

		system("pause>nul");
		return 1;
	}

	Start WulledEntry = (Start)GetProcAddress(dll, "WulledEntry");
	if (WulledEntry == nullptr)
	{
		// TODO: Log error
		return 2;
	}

	WulledEntry(argc, argv);
}
