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

		"../%{IncludeDir.GLFW}",
		"../%{IncludeDir.Glad}",
		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.spdlog}",
		"../%{IncludeDir.glm}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"spdlog",
		"glm",
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
			"ENGINE_DEBUG",
			"EN_ENABLE_ASSERTS",
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
