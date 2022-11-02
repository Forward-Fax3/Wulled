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

include "Wulled/Engine/vendor/proj/git"
include "Wulled/Engine/vendor/proj/source"

project "Wulled"
	location "Wulled"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. output .. "/%{prj.name}")
	objdir ("bin/" .. output .. "/intermediate/%{prj.name}")

	pchheader "wldpch.h"
	pchsource "%{prj.name}/Engine/src/core/pch/wldpch.cpp"

	files
	{
		"%{prj.name}/Engine/src/**.cpp",
		"%{prj.name}/Engine/src/**.h",

		"%{prj.name}/app.h"
	}

	includedirs
	{
		"%{prj.name}",

		"%{prj.name}/Engine/src/**",

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"spdlog",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "c++20"
		cdialect "c17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
		}

		postbuildcommands
		{
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. output .. "/SandBox")
		}
	
	filter "configurations:Debug"
		defines 
		{
			"ENGINE_DEBUG",
			"EN_ENABLE_ASSERTS",
		}
		symbols "On"
		buildoptions "/MDd"
	
	filter "configurations:Release"
		defines 
		{
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "On"
		buildoptions "/MD"

	filter "configurations:dist"
		defines "ENGINE_DIST"
		optimize "On"
		symbols "Off"
		buildoptions "/MD"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

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
	}

	links
	{
		"Wulled"
	}

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
		buildoptions "/MDd"
	
	filter "configurations:Release"
		defines 
		{
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "On"
		buildoptions "/MD"

	filter "configurations:dist"
		defines "ENGINE_DIST"
		optimize "On"
		symbols "Off"
		buildoptions "/MD"