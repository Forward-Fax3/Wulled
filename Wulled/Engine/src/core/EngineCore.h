#pragma once
#define CORE
#include <memory>

#if WLD_DLL
#if WLD_BUILD_DLL
	#define WLD_API __declspec(dllexport)
#else
	#define WLD_API __declspec(dllimport)
#endif
#else
	#define WLD_API
#endif

namespace WLD
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
}

#ifdef EN_ENABLE_ASSERTS
#include "Engine/src/core/Log.h"
	#define GAME_ASSERT(x, ...) { if(!(x)) { LOG_FATAL("Assertion Failed: " __VA_ARGS__); } } // second input must be a string
	#define WLD_CORE_ASSERT(x, ...) { if(!(x)) { WLD_CORE_FATAL("Assertion Failed: " __VA_ARGS__); } } // second input must be a string
#else
#include "Engine/src/core/Log.h"
	#define GAME_ASSERT(x, ...) { if(!(x)) { LOG_CRITICAL("Assertion Failed: " __VA_ARGS__); } }
	#define WLD_CORE_ASSERT(x, ...) { if(!(x)) { WLD_CORE_CRITICAL("Assertion Failed: " __VA_ARGS__); } }
#endif


#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)