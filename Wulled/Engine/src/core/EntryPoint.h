#pragma once
#include "Engine/src/Core/application.h"

#include "Engine/src/commandLine/commandLine.h"
#include "Engine/src/Core/Log.h"


extern WLD::Application* WLD::CreateApplication(bool* run);

int main()
{
	WLD::Log::Init();
	bool* run = new bool[2]; // 0 - run, 1 - restart
	std::thread command(Command, run);
	command.detach();

	do 
	{
		run[0] = true; // set run to true
		run[1] = false; // set restart to false console will set it to true if restart is needed
		WLD::Application* application = WLD::CreateApplication(run);
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
