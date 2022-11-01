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

	while (run[0])
	{
		SetConsoleTextAttribute(hConsole, 13);
		std::cin >> input;

		if (input == "exit")
		{
			run[0] = false;
		}
		else if (input == "restart")
		{
			run[0] = false;
			run[1] = true;
		}
	}
}
