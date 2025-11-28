newoption
{
	trigger = "cleanType",
	allowed =
	{
		"vs2022",
		"gmake"
	},
	description = "select what type of clean you want to do."
}

workspace "Wulled"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

	platforms
	{
		"AVX512",
		"AVX2",
		"SSE2"
	}

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["ImGui"]    = "Wulled/Engine/vendor/proj/git/imgui/"
IncludeDir["STBImage"] = "Wulled/Engine/vendor/proj/git/STB/"
filter { "configurations:Debug" }
	IncludeDir["Glad"]     = "Wulled/Engine/vendor/proj/source/Glad/Debug/include"
filter { "configurations:Release or configurations:Dist" }
	IncludeDir["Glad"]     = "Wulled/Engine/vendor/proj/source/Glad/main/include"
filter {}
IncludeDir["glm"]    = "Wulled/Engine/vendor/core/git/glm/"
IncludeDir["spdlog"] = "Wulled/Engine/vendor/core/git/spdlog/include/"
IncludeDir["glew"]   = "Wulled/Engine/vendor/proj/source/glew/include"
IncludeDir["SDL"]    = "Wulled/Engine/vendor/Librarys/SDL/include"

if _ACTION == "clean" then
	os.rmdir("bin");
	filter { "options:cleanType=vs2022" }
		os.remove("Wulled.sln")
		
		os.remove("Wulled/wulled.vcxproj")
		os.remove("Sandbox/sandbox.vcxproj")
		os.remove("AppStart/Appstart.vcxproj")
		
		os.remove("Wulled/wulled.vcxproj.filters")
		os.remove("Sandbox/sandbox.vcxproj.filters")
		os.remove("AppStart/Appstart.vcxproj.filters")
		
		os.remove("Wulled/wulled.vcxproj.user")
		os.remove("Sandbox/sandbox.vcxproj.user")
		os.remove("AppStart/Appstart.vcxproj.user")

		os.remove("Wulled/Engine/vendor/proj/git/imgui/ImGui.vcxproj")
		os.remove("Wulled/Engine/vendor/proj/git/STB/STBImage.vcxproj")
		os.remove("Wulled/Engine/vendor/proj/source/glew/glew.vcxproj")

		os.remove("Wulled/Engine/vendor/proj/git/imgui/ImGui.vcxproj.filters")
		os.remove("Wulled/Engine/vendor/proj/git/STB/STBImage.vcxproj.filters")
		os.remove("Wulled/Engine/vendor/proj/source/glew/glew.vcxproj.filters")
	filter{}
end

output = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}"

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
	cppdialect "c++17"
	cdialect "c17"
	staticruntime "off"
	toolset "clang"
	linker "LLD"
--	warnings "Everything"
	fatalwarnings "ALL"

	targetdir ("Bin/" .. output .. "/%{prj.name}")
	objdir ("Bin/intermediate/" .. output .. "/%{prj.name}")

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
		"%{IncludeDir.SDL}",
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

	buildoptions
	{
		"-Wno-c++98-compat",
		"-Wno-c++98-compat-pedantic",
		"-Wno-extra-semi-stmt"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter { "configurations:Debug" }
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
	
	filter { "configurations:Release" }
		runtime "Release"
		defines 
		{
			"_RELEASE",
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "Speed"
		symbols "On"

	filter { "configurations:Dist" }
		runtime "Release"
		defines
		{
			"_DIST",
			"ENGINE_DIST"
		}
		linktimeoptimization "on"
		optimize "Speed"
		symbols "Off"
	
	filter { "platforms:AVX512" }
--		vectorextensions "AVX512" currently not supported need to use buildoptions instead
		buildoptions { "/arch:AVX512" }
		defines
		{
			"GLM_FORCE_AVX2", -- GLM doesnt seem to support AVX512 anymore so we use AVX2 instead though the compiler should still compile it with AVX512
			"GLM_FORCE_FMA"
		} 
	filter { "platforms:AVX2" }
		vectorextensions "AVX2"
		defines
		{
			"GLM_FORCE_AVX2",
			"GLM_FORCE_FMA"
		} 
	filter { "platforms:SSE2" }
		vectorextensions "SSE2"
		defines { "GLM_FORCE_SSE2" }

project "AppStart"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	toolset "clang"
	cppdialect "c++17"
	cdialect "c17"
	systemversion "latest"
	warnings "Everything"
	fatalwarnings "ALL"
	debugdir "bin/%{cfg.system}/%{cfg.buildcfg}/%{prj.name}"

	removeplatforms
	{
		"AVX512",
		"AVX2",
		"SSE2"
	}
	
	targetdir ("bin/%{cfg.system}/%{cfg.buildcfg}/%{prj.name}")
	objdir ("bin/intermediate/%{cfg.system}/%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"%{prj.name}/start.cpp",
	}

	flags
	{
		"MultiProcessorCompile",
	}

	buildoptions
	{
		"-Wno-c++98-compat",
		"-Wno-c++98-compat-pedantic",
		"-Wno-extra-semi-stmt"
	}

	postbuildcommands 
	{
		"xcopy /s /e /h /i /y \"%{_WORKING_DIR}\\Wulled\\Engine\\vendor\\Librarys\\SDL\\lib\\DLLs\" \"%{_WORKING_DIR}\\bin\\SDL\\DLLs\""
	}

	filter { "configurations:Debug" }
		defines { "_DEBUG" }
		optimize "off"
		symbols "On"

	filter { "configurations:Release" }
		defines { "_RELEASE" }
		optimize "off"
		symbols "On"
		
	filter { "configurations:Dist" }
		defines { "_DIST" }
		optimize "off"
		symbols "on"
