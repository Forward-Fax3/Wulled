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
IncludeDir["GLFW"] = "Wulled/Engine/vendor/proj/git/GLFW/include/"
IncludeDir["Glad"] = "Wulled/Engine/vendor/proj/source/Glad/include/"
IncludeDir["ImGui"] = "Wulled/Engine/vendor/proj/git/imgui/"
IncludeDir["spdlog"] = "Wulled/Engine/vendor/proj/git/spdlog/include/"
IncludeDir["glm"] = "Wulled/Engine/vendor/proj/git/glm/"

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

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
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
		defines 
		{
			"ENGINE_DEBUG",
			"EN_ENABLE_ASSERTS"
		}
		symbols "On"
	
	filter "configurations:Release"
		defines 
		{
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "On"

	filter "configurations:dist"
		defines "ENGINE_DIST"
		optimize "On"
		symbols "Off"