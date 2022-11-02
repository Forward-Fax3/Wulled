// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "app.h"

#include <iostream>


class SandBox : public WLD::Application
{
public:
	SandBox(bool* run)
		: Application(run)
	{
		std::cout << "sand box created" << std::endl;
		PushOverlay(new WLD::ImGuiLayer);
	}

	~SandBox()
	{
	}

private:

};

WLD::Application* WLD::CreateApplication(bool* run)
{
	return new SandBox(run);
}