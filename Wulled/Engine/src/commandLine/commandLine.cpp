#include "wldpch.h"

#include <string>
#include <iostream>

#include <windows.h>

#include <thread>

#include "commandLine.h"


void Command(bool* run)
{
	std::string input;

	HANDLE consoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleOutHandle, 13);

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
		else if (input == "pause")
		{
			std::cout << 
				"The program is paused\n"
				"please press enter to resume...";
			system("pause<nul");
		}
		else
		{
			WLD_CORE_WARNING("\"{0}\" is not a reconised command", input);
		}
	}
}
