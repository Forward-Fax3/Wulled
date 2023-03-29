project "Wulled"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. output .. "/%{prj.name}")
	objdir ("bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"Engine/src/**.cpp",
		"Engine/src/**.h",

		"app.h"
	}

	includedirs
	{
		"../%{prj.name}",

		"Engine/src/**",

		"../%{IncludeDir.GLFW}",
		"../%{IncludeDir.Glad}",
		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.spdlog}",
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
			("{copy} %{cfg.buildtarget.relpath} ../DLL")
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
