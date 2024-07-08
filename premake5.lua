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
IncludeDir["spdlog"]   = "Wulled/Engine/vendor/core/git/spdlog/include/"
IncludeDir["glm"]      = "Wulled/Engine/vendor/proj/git/glm/"
IncludeDir["DXTK12"]   = "Wulled/Engine/vendor/proj/git/DXTK12/"
IncludeDir["STBImage"] = "Wulled/Engine/vendor/proj/git/STB/"
filter "configurations:Debug"
	IncludeDir["Glad"]     = "Wulled/Engine/vendor/proj/source/Glad/Debug/include"
filter { "configurations:Release", "configurations:dist"}
	IncludeDir["Glad"]     = "Wulled/Engine/vendor/proj/source/Glad/main/include"
filter {}
IncludeDir["glew"] = "Wulled/Engine/vendor/proj/source/glew/include"
IncludeDir["SDL"] = "Wulled/Engine/vendor/Librarys/SDL/include"

include "Wulled/Engine/vendor/proj/git"
include "Wulled/Engine/vendor/proj/source"
include "Wulled"

pchheader "wldpch.h"
pchsource "%{prj.name}/Engine/src/pch/wldpch.cpp"

project "SandBox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	vectorextensions "AVX2"
	toolset "clang"

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
		"%{IncludeDir.STBImage}",
--		"%{IncludeDir.Glad}",
		"%{IncludeDir.glew}",
		"%{IncludeDir.SDL}",
		
		"%VULKAN_SDK%/Include",
	}

	links
	{
		"Wulled"
	}

	defines
	{
--		"WLD_DLL",
		"GLM_FORCE_SSE2",
		"GLM_FORCE_SSE3",
		"GLM_FORCE_SSSE3",
		"GLM_FORCE_SSE41",
		"GLM_FORCE_SSE42",
		"GLM_FORCE_AVX",
		"GLM_FORCE_AVX2",
		"GLM_FORCE_SWIZZLE",
		"GLM_ENABLE_EXPERIMENTAL",
		"GLM_FORCE_DEFAULT_ALIGNED_GENTYPES",
	}

	flags
	{
		"MultiProcessorCompile",
	}

	filter "system:windows"
		cppdialect "c++20"
		cdialect "c17"
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
		optimize "Speed"
		symbols "On"

	filter "configurations:dist"
		runtime "Release"
		defines
		{
			"_DIST",
			"ENGINE_DIST"
		}
		flags
		{
			"LinkTimeOptimization",
		}
		optimize "Speed"
		symbols "Off"