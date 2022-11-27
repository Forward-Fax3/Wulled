#pragma once
#include "Engine/src/Core/application.h"

#include "Engine/src/commandLine/commandLine.h"
#include "Engine/src/Core/Log.h"


extern WLD::Application* WLD::CreateApplication(bool* run);

int main()
{
	WLD::Log::Init();
<<<<<<< HEAD
	bool run[2] = { true, false };
	std::thread command = std::thread(Command, run);
	command.detach();

	do
=======
	WLD_CORE_WARNING("initialied log");
	LOG_INFO("hello world");
	bool run[2];

	do 
>>>>>>> 80383ae7499a6d4517d3792745d7aebde7548779
	{
		run[0] = true;
		run[1] = false;
		WLD::Application* application = WLD::CreateApplication(run);
		application->run();
		delete application;	
	
	} while (run[1]);
}
