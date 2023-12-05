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

		if (input == "exit")
		{
			run[0] = false;
		}
		else if (input == "restart")
		{
			run[0] = false;
			run[1] = true;
		}
		else
		{
			WLD_CORE_WARNING("\"{0}\" is not a reconised command", input);
		}
	}
}
