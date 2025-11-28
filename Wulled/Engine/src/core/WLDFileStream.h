#pragma once
#include "Engine/src/core/EngineCore.h"
#include <fstream>
#include <string>
#include <vector>


namespace WLD
{
	class WLD_API FileStream
	{
	public:
		inline static bool ReadFile(std::string filePath, std::string& result)
		{
			std::ifstream in(filePath.data(), std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				result.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(const_cast<char*>(result.c_str()), static_cast<std::streamsize>(result.size()));
				in.close();
				return true;
			}
			return false;
		}

		template<typename T>
		inline static bool ReadFile(const std::string& filePath, std::vector<T>& result)
		{
			std::ifstream in(filePath.data(), std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				result.resize(in.tellg() / sizeof(T));
				in.seekg(0, std::ios::beg);
				in.read((char*)result.data(), result.size() * sizeof(T));
				in.close();
				return true;
			}
			return false;
		}

		inline static bool WriteFile(const std::string& filePath, const std::string& data)
		{
			std::ofstream out(filePath.data(), std::ios::out | std::ios::binary);
			if (out)
			{
				out.write(data.data(), static_cast<std::streamsize>(data.size()));
				out.close();
				return true;
			}
			return false;
		}

		template<typename T>
		inline static bool WriteFile(const std::string& filePath, const std::vector<T>& data)
		{
			std::ofstream out(filePath.data(), std::ios::out | std::ios::binary);
			if (out)
			{
				out.write((char*)data.data(), data.size() * sizeof(T));
				out.close();
				return true;
			}
			return false;
		}
	};
}