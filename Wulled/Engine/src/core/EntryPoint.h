#pragma once
#include "Engine/src/Core/application.h"

#include "Engine/src/commandLine/commandLine.h"
#include "Engine/src/Core/Log.h"


extern WLD::Application* WLD::CreateApplication(bool* run);

int main()
{
	WLD::Log::Init();
	bool run[2] = { true, false };
	std::thread command = std::thread(Command, run);
	command.detach();

	do 
	{
		run[0] = true;
		run[1] = false;
		WLD::Application* application = WLD::CreateApplication(run);
		application->run();
		delete application;	
	
	} while (run[1]);
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
