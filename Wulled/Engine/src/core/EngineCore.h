#pragma once
#define CORE

#if WLD_DLL
#if WLD_BUILD_DLL
	#define WLD_API __declspec(dllexport)
#else
	#define WLD_API __declspec(dllimport)
#endif
#else
	#define WLD_API
#endif

#ifdef EN_ENABLE_ASSERTS
	#define WLD_ASSERT(x, ...) { if(!(x)) { WLD_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); } }
	#define WLD_CORE_ASSERT(x, ...) { if(!(x)) { WLD_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); } }
#else
	#define WLD_ASSERT(x, ...)
	#define WLD_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)