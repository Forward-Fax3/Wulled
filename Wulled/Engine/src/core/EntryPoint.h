#pragma once
#include "Engine/src/Core/application.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"

#include "Engine/src/commandLine/commandLine.h"
#include "Engine/src/Core/Log.h"
#include "Engine/src/core/WLDMem.h"

#include <winbase.h>


extern WLD::Application* WLD::CreateApplication(bool* run, int argc, char** argv);

void memoryCheck()
{
	size_t memory = WLD::GetAllocatedTotalMemory();
	size_t memorySmart = WLD::GetAllocatedSmartMemory();
	size_t memoryManual = WLD::GetAllocatedMemory();

	if (memory || memorySmart || memoryManual || !WLD::Memory::Map.empty())
	{
		for (auto& data : WLD::Memory::Map)
		{
			WLD_CORE_CRITICAL("Memory Leak at {0}", data.first);
			if (data.second.WasCreatedManually)
				WLD_CORE_CRITICAL("Was Manually created");
			else
				WLD_CORE_CRITICAL("Was Smartly created");
			WLD_CORE_CRITICAL("{0} bytes", data.second.Map);
			WLD_CORE_CRITICAL("Number of allocations {0}", data.second.numberOfAllocations);
#ifdef _DEBUG
			WLD_CORE_CRITICAL("Was created at {0}\n", data.second.Location);
#endif
		}
		WLD_CORE_FATAL("Total Memory Leak {0} bytes, smart {1}, manual {2}", memory, memorySmart, memoryManual);
	}
}

int main(int argc, char** argv)
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WLD::Log::Init();
	bool* run = CreateArray(bool, 4); // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset
	std::thread command(Command, run);
	command.detach();
	run[2] = false;
	run[3] = false;

	// just testin shite
//	WLD::Ref<int> ref(nullptr);
//	std::shared_ptr<int> shared(nullptr);
//	LOG_TRACE("size of ref {0}", sizeof(ref));
//	LOG_TRACE("size of Ref {0}", sizeof(WLD::Ref<int>));
//	LOG_TRACE("size of shared {0}", sizeof(shared));
//	LOG_TRACE("size of shared_ptr {0}", sizeof(std::shared_ptr<int>));
//	WLD::Ref ref2(shared);

	do 
	{
		WLD::Graphics::Renderer::RendererAPI::updateAPI();
		run[0] = true;  // set run to true
		run[1] = false; // set restart to false
		WLD::Application* application = WLD::CreateApplication(run, argc, argv);
//		WLD::Application* application = WLD::CreateApplication(run, NULL, (char**)nullptr);
		application->run();
		application = DestroyMemory(application);
	
	} while (run[1]);

	command.~thread();
	run = DestroyMemory(run);
	memoryCheck();
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
// 		WLD_CORE_INFO(applicationThread.get_id());
// 
// 		applicationThread.detach();
// 
// 		Command(appRun.run);
// 
// 		while (!appRun.appClosed);
// 		applicationThread.~thread();
// 	} while (appRun.run[1]);
// }
