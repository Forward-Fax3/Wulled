#include "wldpch.h"

#include <string>
#include <iostream>

#include <windows.h>
#include <thread>

#include "commandLine.h"
#include "Log.h"


// simple command line interface for the program
void Command(bool* run)
{
	std::string input;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

	while (run[0] || run[1])
	{
		std::cin >> input;

		for (char& c : input)
			c = ::tolower(c);

		if (strcmp(input.c_str(), "exit"))
		{
			run[0] = false;
		}
		else if (strcmp(input.c_str(), "restart"))
		{
			run[0] = false;
			run[1] = true;
		}
		else if (strcmp(input.c_str(), "help"))
		{
			WLD_CORE_INFO("Commands:");
			WLD_CORE_INFO("exit - exits the program");
			WLD_CORE_INFO("restart - restarts the program");
		}
		else
		{
			WLD_CORE_WARNING("\"{0}\" is not a reconised command", input);
		}
	}
}
