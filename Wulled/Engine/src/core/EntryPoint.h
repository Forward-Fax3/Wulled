#pragma once
#include "Engine/src/Core/application.h"
#include "Engine/src/core/graphics/Renderer/RendererAPI.h"

#include "Engine/src/commandLine/commandLine.h"
#include "Engine/src/Core/Log.h"


extern WLD::Application* WLD::CreateApplication(bool* run, int argc, char** argv);

int main(int argc, char** argv)
{
	WLD::Log::Init();
	bool* run = new bool[4]; // 0 - run, 1 - restart, 2 - APISet, 3 - APIReset
	std::thread command(Command, run);
	command.detach();
	run[2] = false;
	run[3] = false;

	do 
	{
		WLD::Graphics::Renderer::RendererAPI::updateAPI();
		run[0] = true;  // set run to true
		run[1] = false; // set restart to false
		WLD::Application* application = WLD::CreateApplication(run, argc, argv);
		application->run();
		delete application;
	
	} while (run[1]);

	command.~thread();
	delete[] run;
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
