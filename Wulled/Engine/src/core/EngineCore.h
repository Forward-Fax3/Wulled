#pragma once
#define CORE
#include <memory>
#include <stdint.h>
#include <glm/glm.hpp>


#ifdef WLD_DLL
#ifdef WLD_BUILD_DLL
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
	#define GAME_ASSERT(x, ...) { if(!(x)) { LOG_FATAL("Assertion Failed: " __VA_ARGS__); } } // second input MUST be a string
	#define WLD_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_FATAL("Assertion Failed: " __VA_ARGS__); } } // second input MUST be a string
#else
#include "Engine/src/core/Log.h"
	#define GAME_ASSERT(x, ...) { if(!(x)) { LOG_CRITICAL("Assertion Failed: " __VA_ARGS__); } }
	#define WLD_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_CRITICAL("Assertion Failed: " __VA_ARGS__); } }
#endif

#ifdef __clang__
#define WLD_UNUSED __attribute__((unused))
#else
#define WLD_UNUSED
#endif


#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
#define GLM_DEFINE_ALL_TYPES_FLOAT(CLASS)\
/* packed */ \
	template class CLASS<float, glm::packed_highp>;\
	template class CLASS<float, glm::packed_mediump>;\
	template class CLASS<float, glm::packed_lowp>;\
\
	template class CLASS<double, glm::packed_highp>;\
	template class CLASS<double, glm::packed_mediump>;\
	template class CLASS<double, glm::packed_lowp>;\
\
/* aligned */ \
	template class CLASS<float, glm::aligned_highp>;\
	template class CLASS<float, glm::aligned_mediump>;\
	template class CLASS<float, glm::aligned_lowp>;\
\
	template class CLASS<double, glm::aligned_highp>;\
	template class CLASS<double, glm::aligned_mediump>;\
	template class CLASS<double, glm::aligned_lowp>


#define GLM_DEFINE_ALL_TYPES_INT(CLASS)\
/* packed */ \
	template class CLASS<int8_t, glm::packed_highp>;\
	template class CLASS<int8_t, glm::packed_mediump>;\
	template class CLASS<int8_t, glm::packed_lowp>;\
\
	template class CLASS<int16_t, glm::packed_highp>;\
	template class CLASS<int16_t, glm::packed_mediump>;\
	template class CLASS<int16_t, glm::packed_lowp>;\
\
	template class CLASS<int32_t, glm::packed_highp>;\
	template class CLASS<int32_t, glm::packed_mediump>;\
	template class CLASS<int32_t, glm::packed_lowp>;\
\
	template class CLASS<int64_t, glm::packed_highp>;\
	template class CLASS<int64_t, glm::packed_mediump>;\
	template class CLASS<int64_t, glm::packed_lowp>;\
\
/* aligned */ \
	template class CLASS<int8_t, glm::aligned_highp>;\
	template class CLASS<int8_t, glm::aligned_mediump>;\
	template class CLASS<int8_t, glm::aligned_lowp>;\
\
	template class CLASS<int16_t, glm::aligned_highp>;\
	template class CLASS<int16_t, glm::aligned_mediump>;\
	template class CLASS<int16_t, glm::aligned_lowp>;\
\
	template class CLASS<int32_t, glm::aligned_highp>;\
	template class CLASS<int32_t, glm::aligned_mediump>;\
	template class CLASS<int32_t, glm::aligned_lowp>;\
\
	template class CLASS<int64_t, glm::aligned_highp>;\
	template class CLASS<int64_t, glm::aligned_mediump>;\
	template class CLASS<int64_t, glm::aligned_lowp>

#else
#define GLM_DEFINE_ALL_TYPES_FLOAT(CLASS)\
	template class CLASS<float, glm::packed_highp>;\
	template class CLASS<float, glm::packed_mediump>;\
	template class CLASS<float, glm::packed_lowp>;\
\
	template class CLASS<double, glm::packed_highp>;\
	template class CLASS<double, glm::packed_mediump>;\
	template class CLASS<double, glm::packed_lowp>


#define GLM_DEFINE_ALL_TYPES_INT(CLASS)\
	template class CLASS<int8_t, glm::packed_highp>;\
	template class CLASS<int8_t, glm::packed_mediump>;\
	template class CLASS<int8_t, glm::packed_lowp>;\
\
	template class CLASS<int16_t, glm::packed_highp>;\
	template class CLASS<int16_t, glm::packed_mediump>;\
	template class CLASS<int16_t, glm::packed_lowp>;\
\
	template class CLASS<int32_t, glm::packed_highp>;\
	template class CLASS<int32_t, glm::packed_mediump>;\
	template class CLASS<int32_t, glm::packed_lowp>;\
\
	template class CLASS<int64_t, glm::packed_highp>;\
	template class CLASS<int64_t, glm::packed_mediump>;\
	template class CLASS<int64_t, glm::packed_lowp>
#endif

#define GLM_DEFINE_ALL_TYPES(CLASS)\
	GLM_DEFINE_ALL_TYPES_FLOAT(CLASS);\
	GLM_DEFINE_ALL_TYPES_INT(CLASS)
