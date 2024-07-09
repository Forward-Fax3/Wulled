--project "spdlog"
--	kind "StaticLib"
--	language "c++"
--	staticruntime "on"
--	location "%{prj.name}"
--
--	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
--	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")
--
--	files
--	{
--		"%{prj.name}/include/**.h",
--		"%{prj.name}/src/**.cpp",
--	}
--
--	includedirs
--	{
--		"%{prj.name}",
--		"%{prj.name}/include",
--		"%{prj.name}/src",
--	}
--
--	defines 
--	{
--		"SPDLOG_COMPILED_LIB",
--	}
--
--	systemversion "latest"
--	cdialect "c17"
--	cppdialect "c++20"
--
--	filter "configurations:Debug"
--		runtime "Debug"
--		symbols "on"
--
--	filter "configurations:Release"
--		runtime "Release"
--		optimize "Speed"
--
--	filter "configurations:Dist"
--		runtime "Release"
--		optimize "Speed"
--    	symbols "off"

project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	location "%{prj.name}"
	vectorextensions "AVX2"
	toolset "clang"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/imgui_demo.cpp",
		"%{prj.name}/imgui.cpp",
		"%{prj.name}/imgui_draw.cpp",
		"%{prj.name}/imgui_widgets.cpp",
		"%{prj.name}/imgui_tables.cpp",
		"%{prj.name}/backends/imgui_impl_SDL2.cpp",
		"%{prj.name}/backends/imgui_impl_opengl3.cpp",
		"%{prj.name}/backends/imgui_impl_dx12.cpp",
		"%{prj.name}/backends/imgui_impl_vulkan.cpp",
		
		"%{prj.name}/imconfig.h",
		"%{prj.name}/imgui.h",
		"%{prj.name}/imgui_internal.h",
		"%{prj.name}/imstb_rectpack.h",
		"%{prj.name}/imstb_textedit.h",
		"%{prj.name}/imstb_truetype.h",
		"%{prj.name}/backends/imgui_impl_SDL2.h",
		"%{prj.name}/backends/imgui_impl_opengl3.h",
		"%{prj.name}/backends/imgui_impl_dx12.h",
		"%{prj.name}/backends/imgui_impl_vulkan.h",

--		"%{_WORKING_DIR}/%{IncludeDir.SDL}",
	}

	includedirs
	{
		"%{prj.name}",
		"%{prj.name}/%{_WORKING_DIR}/%{IncludeDir.SDL}",
		"%VULKAN_SDK%/Include",
	}

--	defines
--	{
--		"IMGUI_API=__declspec(dllexport)"
--	}

	flags
	{
		"MultiProcessorCompile",
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
		symbols "off"
		flags
		{
			"LinkTimeOptimization",
		}

project "glm"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	location "%{prj.name}"
	vectorextensions "AVX2"
	toolset "clang"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/glm/**.hpp",
		"%{prj.name}/glm/**.h",
		"%{prj.name}/glm/detail/glm.cpp",
		"%{prj.name}/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/",
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
		"GLM_FORCE_DEFAULT_ALIGNED_GENTYPES",
	}

	flags
	{
		"MultiProcessorCompile",
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
    	symbols "off"
		flags
		{
			"LinkTimeOptimization",
		}

project "STBImage"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	location "STB"
	vectorextensions "AVX2"
	toolset "clang"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"STB/*.h",
		"STB/*.c",
		"STB/*.cpp",
	}

	includedirs
	{
		"STB",
	}

	flags
	{
		"MultiProcessorCompile",
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

	filter "configurations:Dist"
		runtime "Release"
		optimize "Speed"
    	symbols "off"
		flags
		{
			"LinkTimeOptimization",
		}
