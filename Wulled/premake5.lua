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

		"Engine/src/core/**",
		"Engine/src/core",
		"Engine/src/commandLine",
		"Engine/src/pch",
		"Engine/src/platform",
		
		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.spdlog}",
		"../%{IncludeDir.glm}",
		"../%{IncludeDir.DXTK12}",
		"../%{IncludeDir.glatter}",
		"../%{IncludeDir.STBImage}",

		"%VULKAN_SDK%/Include",
	}

	links
	{
		"ImGui",
		"spdlog",
		"glm",
		"DXTK12",
		"glatter",
		"STBImage",
		"opengl32.lib",
		"%VULKAN_SDK%/Lib/vulkan-1.lib",
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
		runtime "Debug"
		defines 
		{
			"_DEBUG",
			"ENGINE_DEBUG",
			"DX12_ENABLE_DEBUG_LAYER",
			"EN_ENABLE_ASSERTS",
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
