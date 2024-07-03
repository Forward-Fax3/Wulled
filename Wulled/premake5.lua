project "Wulled"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

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
		"Engine/src/platform/*",
		
		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.spdlog}",
		"../%{IncludeDir.glm}",
		"../%{IncludeDir.DXTK12}",
		"../%{IncludeDir.STBImage}",
--		"../%{IncludeDir.Glad}",
		"../%{IncludeDir.glew}",
		"../%{IncludeDir.SDL}",

		"%VULKAN_SDK%/Include",
	}

	links
	{
		-- propject links
		"ImGui",
--		"spdlog",
		"glm",
		"DXTK12",
		"STBImage",
--		"Glad",
		"glew",

		-- Windows built in links
		"opengl32.lib",
		"winmm.lib",
		"setupapi.lib",
		"version.lib",
--		"Imm32.lib",

		-- Vulkan link
		"%VULKAN_SDK%/Lib/vulkan-1.lib",

		-- SDL links
		"Engine/vendor/Librarys/SDL/lib/SDL2.lib",
		"Engine/vendor/Librarys/SDL/lib/SDL2main.lib",
		"Engine/vendor/Librarys/SDL/lib/SDL2test.lib",
	}

	defines
	{
		"GLM_FORCE_SSE2",
		"GLM_FORCE_SSE3",
		"GLM_FORCE_SSSE3",
		"GLM_FORCE_SSE41",
		"GLM_FORCE_SSE42",
		"GLM_FORCE_AVX",
		"GLM_FORCE_AVX2",
		"GLM_FORCE_SWIZZLE",
		"GLM_ENABLE_EXPERIMENTAL",
	}

	flags
	{
		"MultiProcessorCompile",
	}

	filter "system:windows"
		cppdialect "c++20"
		cdialect "c17"
		systemversion "latest"

		defines
		{
--			"WLD_DLL",
--			"WLD_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
			"GLEW_STATIC",
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
		links
		{
			"%VULKAN_SDK%/Lib/spirv-cross-cored.lib",
			"%VULKAN_SDK%/Lib/spirv-cross-glsld.lib",
			"%VULKAN_SDK%/Lib/shaderc_combinedd.lib",
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
		links
		{
			"%VULKAN_SDK%/Lib/spirv-cross-core.lib",
			"%VULKAN_SDK%/Lib/spirv-cross-glsl.lib",
			"%VULKAN_SDK%/Lib/shaderc_combined.lib",
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
		links
		{
			"%VULKAN_SDK%/Lib/spirv-cross-core.lib",
			"%VULKAN_SDK%/Lib/spirv-cross-glsl.lib",
			"%VULKAN_SDK%/Lib/shaderc_combined.lib",
		}

		flags
		{
			"LinkTimeOptimization",
		}
		optimize "Speed"
		symbols "Off"
