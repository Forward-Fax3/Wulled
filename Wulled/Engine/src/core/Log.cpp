#include "wldpch.h"
#include "WLDMem.h"

#include "Log.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextra"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma clang diagnostic pop
#pragma clang diagnostic pop

#include <iostream>


namespace WLD
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Engine");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::NewLine()
	{
		std::cout << "\n";
	}
}
