workspace "Wulled"
	architecture "x64"

	configurations
	{
		"Debug-AVX512",
		"Debug-AVX2",
		"Debug-SSE2",
		"Release-AVX512",
		"Release-AVX2",
		"Release-SSE2",
		"Dist-AVX512",
		"Dist-AVX2",
		"Dist-SSE2"
	}
 
-- Filter configurations
filterCofigurations = {}
filterCofigurations["AVX512"] = "configurations:Debug-AVX512 or configurations:Release-AVX512 or configurations:Dist-AVX512"
filterCofigurations["AVX2"] = "configurations:Debug-AVX2 or configurations:Release-AVX2 or configurations:Dist-AVX2"
filterCofigurations["SSE2"] = "configurations:Debug-SSE2 or configurations:Release-SSE2 or configurations:Dist-SSE2"
filterCofigurations["Debug"] = "configurations:Debug-AVX512 or configurations:Debug-AVX2 or configurations:Debug-SSE2"
filterCofigurations["Release"] = "configurations:Release-AVX512 or configurations:Release-AVX2 or configurations:Release-SSE2"
filterCofigurations["Dist"] = "configurations:Dist-AVX512 or configurations:Dist-AVX2 or configurations:Dist-SSE2"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["ImGui"]    = "Wulled/Engine/vendor/proj/git/imgui/"
IncludeDir["STBImage"] = "Wulled/Engine/vendor/proj/git/STB/"
filter { filterCofigurations.Debug }
	IncludeDir["Glad"]     = "Wulled/Engine/vendor/proj/source/Glad/Debug/include"
filter { filterCofigurations.Release .. " or " .. filterCofigurations.Dist}
	IncludeDir["Glad"]     = "Wulled/Engine/vendor/proj/source/Glad/main/include"
filter {}
IncludeDir["glm"]    = "Wulled/Engine/vendor/core/git/glm/"
IncludeDir["spdlog"] = "Wulled/Engine/vendor/core/git/spdlog/include/"
IncludeDir["glew"]   = "Wulled/Engine/vendor/proj/source/glew/include"
IncludeDir["SDL"]    = "Wulled/Engine/vendor/Librarys/SDL/include"

output = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "Wulled/Engine/vendor/proj/git"
include "Wulled/Engine/vendor/proj/source"
include "Wulled"

-- disabled for now
-- pchheader "WLDPCH.h"
-- pchsource "%{prj.name}/Engine/PCH/WLDPCH.cpp"

project "SandBox"
	location "%{prj.name}"
--	kind "ConsoleApp"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	toolset "clang"
--	toolset "msc"

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
	
	filter { filterCofigurations.Debug }
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
	
	filter { filterCofigurations.Release }
		runtime "Release"
		defines 
		{
			"_RELEASE",
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "Speed"
		symbols "On"

	filter { filterCofigurations.Dist }
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
	
	filter { filterCofigurations.AVX512 }
--		vectorextensions "AVX512" currently not supported need to use buildoptions instead
		buildoptions { "/arch:AVX512" }
		defines { "GLM_FORCE_AVX2" } -- GLM doesnt seem to support AVX512 anymore so we use AVX2 instead though the compiler should still compile it with AVX512
	filter { filterCofigurations.AVX2 }
		vectorextensions "AVX2"
		defines { "GLM_FORCE_AVX2" }
	filter { filterCofigurations.SSE2 }
		vectorextensions "SSE2"
		defines { "GLM_FORCE_SSE2" }

project "AppStart"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	toolset "clang"
	cppdialect "c++20"
	cdialect "c17"
	systemversion "latest"
	
	targetdir ("bin/" .. output .. "/%{prj.name}")
	objdir ("bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/start.cpp",
	}

	filter {filterCofigurations.Debug}
		defines { "_DEBUG" }
		optimize "off"
		symbols "On"

	filter {filterCofigurations.Release}
		defines { "_RELEASE" }
		optimize "off"
		symbols "On"
		
	filter {filterCofigurations.Dist}
		defines { "_DIST" }
		optimize "off"
		symbols "on"
