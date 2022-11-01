#pragma once
#include "Engine/vendor/raw/logging/include/spdlog/spdlog.h"
#include "Engine/vendor/raw/logging/include/spdlog/fmt/ostr.h"

#include "Engine/src/core/EngineCore.h"



namespace WLD
{
	class WLD_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// CORE
#define WLD_CORE_TRACE(...)   ::WLD::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WLD_CORE_INFO(...)    ::WLD::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WLD_CORE_WARNING(...) ::WLD::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WLD_CORE_ERROR(...)   ::WLD::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WLD_CORE_FATAL(...)     WLD_CORE_ERROR(__VA_ARGS__); __debugbreak()

// CLIENT
#define LOG_TRACE(...)		  ::WLD::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)		  ::WLD::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...)	  ::WLD::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		  ::WLD::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)		    LOG_ERROR(__VA_ARGS__); __debugbreak()