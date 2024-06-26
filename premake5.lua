workspace "Wulled"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"dist"
	}

output = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["ImGui"]    = "Wulled/Engine/vendor/proj/git/imgui/"
IncludeDir["spdlog"]   = "Wulled/Engine/vendor/proj/git/spdlog/include/"
IncludeDir["glm"]      = "Wulled/Engine/vendor/proj/git/glm/"
IncludeDir["DXTK12"]   = "Wulled/Engine/vendor/proj/git/DXTK12/"
IncludeDir["glatter"]  = "Wulled/Engine/vendor/proj/git/glatter/include/"
IncludeDir["STBImage"] = "Wulled/Engine/vendor/proj/git/STB/"

include "Wulled/Engine/vendor/proj/git"
include "Wulled/Engine/vendor/proj/source"
include "Wulled"

pchheader "wldpch.h"
pchsource "%{prj.name}/Engine/src/pch/wldpch.cpp"

project "SandBox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. output .. "/%{prj.name}")
	objdir ("bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/src/**.h",
	}

	includedirs
	{
		"Wulled",

		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.DXTK12}",
		"%{IncludeDir.glatter}",
		"%{IncludeDir.STBImage}",
	}

	links
	{
		"Wulled"
	}

--	defines
--	{
--		"WLD_DLL",
--	}

	filter "system:windows"
		cppdialect "c++20"
		cdialect "c17"
		staticruntime "On"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime "Debug"
		defines 
		{
			"_DEBUG",
			"ENGINE_DEBUG",
			"DX12_ENABLE_DEBUG_LAYER",
			"EN_ENABLE_ASSERTS"
		}
		optimize "Off"
		symbols "On"
	
	filter "configurations:Release"
		runtime "Release"
		defines 
		{
			"_RELEASE",
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "On"
		symbols "On"

	filter "configurations:dist"
		runtime "Release"
		defines
		{
			"_DIST",
			"ENGINE_DIST"
		}
		optimize "On"
		symbols "Off"