#pragma once
#include "Engine/vendor/proj/git/spdlog/include/spdlog/spdlog.h"
#include "Engine/vendor/proj/git/spdlog/include/spdlog/fmt/ostr.h"

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
#define WLD_CORE_TRACE(...)		::WLD::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WLD_CORE_INFO(...)		::WLD::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WLD_CORE_WARNING(...)	::WLD::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WLD_CORE_ERROR(...)		::WLD::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WLD_CORE_CRITICAL(...)	::WLD::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define WLD_CORE_FATAL(...)		::WLD::Log::GetCoreLogger()->critical(__VA_ARGS__); __debugbreak()
								
// CLIENT						
#define LOG_TRACE(...)			::WLD::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)			::WLD::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...)		::WLD::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)			::WLD::Log::GetClientLogger()->error(__VA_ARGS__)
#define WLD_CORE_CRITICAL(...)	::WLD::Log::GetClientLogger()->critical(__VA_ARGS__)
#define WLD_CORE_FATAL(...)		::WLD::Log::GetClientLogger()->critical(__VA_ARGS__); __debugbreak()