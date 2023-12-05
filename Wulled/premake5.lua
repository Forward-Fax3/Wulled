project "Wulled"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

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

		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.spdlog}",
		"../%{IncludeDir.glm}",
		"../%{IncludeDir.DXTK12}",
		"../%{IncludeDir.glatter}",
	}

	links
	{
		"ImGui",
		"spdlog",
		"glm",
		"DXTK12",
		"glatter",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "c++20"
		cdialect "c17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
--			"WLD_DLL",
--			"WLD_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
		}

--		postbuildcommands
--		{
--			("{copy} $(OutputPath)/Wulled.dll ../bin/" .. output .. "/sandbox")
--		}
	
	filter "configurations:Debug"
		defines 
		{
			"_DEBUG",
			"ENGINE_DEBUG",
			"EN_ENABLE_ASSERTS",
		}
		symbols "On"
	
	filter "configurations:Release"
		defines 
		{
			"_RELEASE",
			"ENGINE_RELEASE",
			"EN_ENABLE_ASSERTS"
		}
		optimize "On"

	filter "configurations:dist"
		defines
		{
			"_DIST",
			"ENGINE_DIST"
		}
		optimize "On"
		symbols "Off"
