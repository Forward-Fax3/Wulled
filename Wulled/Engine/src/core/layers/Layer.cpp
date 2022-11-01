// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com


#include "wldpch.h"

#include "Layer.h"


namespace WLD
{
	Layer::Layer(std::string name)
		: m_DebugName(name)
	{
	}

	Layer::~Layer()
	{
	}
}