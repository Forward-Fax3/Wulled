#include "Engine/src/Core/Application.h"
#include "Engine/src/Core/Graphics/Renderer/RendererAPI.h"

#include "Engine/src/Core/Log.h"
#include "Engine/src/Core/WLDMem.h"

#include <winbase.h>
#include <iostream>                                                                                                                                                                                                                         

#include <random>

#undef main // This is needed to avoid SDL2 from overriding the main function


extern WLD::Application* WLD::CreateApplication(bool* run, int argc, char** argv);

#ifndef _DIST
void memoryCheck()
{
	size_t memory = WLD::GetAllocatedTotalMemory();
	size_t memorySmart = WLD::GetAllocatedSmartMemory();
	size_t memoryManual = WLD::GetAllocatedMemory();

	if (memory || memorySmart || memoryManual || !WLD::Memory::Map.empty())
	{
		for (const auto& data : WLD::Memory::Map)
		{
			LOG_CORE_CRITICAL("Memory Leak at {0}", data.first);
			if (data.second.WasCreatedManually)
				LOG_CORE_CRITICAL("Was Manually created");
			else
				LOG_CORE_CRITICAL("Was Smartly created");
			LOG_CORE_CRITICAL("{0} bytes", data.second.Map);
			LOG_CORE_CRITICAL("Number of allocations {0}", data.second.numberOfAllocations);
#ifdef _DEBUG
			LOG_CORE_CRITICAL("Was created at {0}\n", data.second.Location);
#endif
		}
		LOG_CORE_FATAL("Total Memory Leak {0} bytes, smart {1}, manual {2}", memory, memorySmart, memoryManual);
	}
}
#endif

extern "C" __declspec(dllexport) void __stdcall WulledEntry(int argc, char** argv)
//int main(int argc, char** argv)
{
	WLD::Log::Init();
	bool* run = CreateArray(bool, 4); // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset
	run[2] = false;
	run[3] = false;

	do
	{
		WLD::RendererAPI::UpdateAPI();
		run[0] = true;
		run[1] = false;
		WLD::Application* application = WLD::CreateApplication(run, argc, argv);
		application->run();
		DestroyMemory(application);
		application = nullptr;
	
	} while (run[1]);

	DestroyArray(run);
#ifndef _DIST
	memoryCheck();
#endif
	uint8_t API = (uint8_t)WLD::RendererAPI::GetAPI();
	uint8_t VulkanAPI = (uint8_t)WLD::RendererAPI::API::Vulkan;

	if (API == VulkanAPI)
		system("pause>nul");
}

// struct AppRun
// {
// 	bool run[2];
// 	bool appClosed;
// 	WLD::Application* application;
// };
// 
// void appTheadRun(AppRun* appRun)
// {
// 	appRun->application = WLD::CreateApplication(appRun->run);
// 	appRun->application->run();
// 	delete appRun->application;
// 	appRun->appClosed = true;
// }
// 
// int main()
// {
// 	WLD::Log::Init();
// 	std::thread applicationThread;
// 	AppRun appRun;
// 
// 	do
// 	{
// 		appRun.run[0] = true;
// 		appRun.run[1] = false;
// 		appRun.appClosed = false;
// 
// 		applicationThread = std::thread(appTheadRun, &appRun);
// 		LOG_CORE_INFO(applicationThread.get_id());
// 
// 		applicationThread.detach();
// 
// 		Command(appRun.run);
// 
// 		while (!appRun.appClosed);
// 		applicationThread.~thread();
// 	} while (appRun.run[1]);
// }
