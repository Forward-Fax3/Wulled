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
