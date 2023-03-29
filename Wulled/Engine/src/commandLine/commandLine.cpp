// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "wldpch.h"

#include <string>
#include <iostream>

#include <windows.h>

#include <thread>

#include "commandLine.h"


void Command(bool* run)
{
	std::string input;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 13);

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
			WLD_CORE_WARNING("\"{0}\" is not a reconized command", input);
		}
	}
}
