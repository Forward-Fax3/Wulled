#pragma once
#include "Engine/src/Core/application.h"

#include "Engine/src/commandLine/commandLine.h"
#include "Engine/src/Core/Log.h"


extern WLD::Application* WLD::CreateApplication(bool* run);

int main()
{
	WLD::Log::Init();
	WLD_CORE_WARNING("initialied log");
	LOG_INFO("hello world");
	bool run[2];

	do 
	{
		run[0] = true;
		run[1] = false;
		WLD::Application* application = WLD::CreateApplication(run);
		std::thread command = std::thread(Command, run);
		command.detach();
		application->run();
		delete application;		
	} while (run[1]);
}
