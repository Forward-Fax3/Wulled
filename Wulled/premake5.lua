project "Wulled"
	kind "StaticLib"
	language "C++"
	staticruntime "off"
	toolset "clang"
	linker "lld"
--	warnings "Everything"
	fatalwarnings "ALL"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"Engine/src/**.cpp",
		"Engine/src/**.h",

		"../%{IncludeDir.glm}**.hpp",
		"../%{IncludeDir.glm}**.inl",
		
		"%VULKAN_SDK%/Include",

		"App.h"
	}

	includedirs
	{
		"../%{prj.name}",

		"Engine/src/Core/**",
		"Engine/src/Core",
		"Engine/src/PCH",
		"Engine/src/Platform/*",
		
		"../%{IncludeDir.ImGui}",
		"../%{IncludeDir.spdlog}",
		"../%{IncludeDir.glm}",
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
		"STBImage",
--		"Glad",
		"glew",

		-- Windows built in links
		"opengl32.lib",

		-- Vulkan link
		"%VULKAN_SDK%/Lib/vulkan-1.lib",

		-- SDL links
		"Engine/vendor/Librarys/SDL/lib/SDL2.lib",
		"Engine/vendor/Librarys/SDL/lib/SDL2main.lib",
		"Engine/vendor/Librarys/SDL/lib/SDL2test.lib",
	}

	defines
	{
		"GLM_FORCE_SWIZZLE",
		"GLM_ENABLE_EXPERIMENTAL",
		"GLM_FORCE_DEFAULT_ALIGNED_GENTYPES",
		"WLD_CORE",
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
		cppdialect "c++17"
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
	
	filter { "configurations:Debug" }
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
	
	filter { "configurations:Release" }
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

	filter { "configurations:Dist" }
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
		linktimeoptimization "on"
		optimize "Speed"
		symbols "Off"
	
	filter { "platforms:AVX512" }
	--	vectorextensions "AVX512" currently not supported need to use buildoptions instead
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
