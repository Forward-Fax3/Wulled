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
	staticruntime "off"
	location "%{prj.name}"
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

	filter { filterCofigurations.Debug }
		runtime "Debug"
		symbols "on"

	filter { filterCofigurations.Release }
		runtime "Release"
		optimize "Speed"

	filter { filterCofigurations.Dist }
		runtime "Release"
		optimize "Speed"
		symbols "off"
		flags
		{
			"LinkTimeOptimization",
		}
	
	filter { filterCofigurations.AVX512 }
	--	vectorextensions "AVX512" currently not supported need to use buildoptions instead
		buildoptions { "/arch:AVX512" }
	filter { filterCofigurations.AVX2 }
		vectorextensions "AVX2"
	filter { filterCofigurations.SSE2 }
		vectorextensions "SSE2"

project "STBImage"
	kind "StaticLib"
	language "c++"
	staticruntime "off"
	location "STB"
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

	filter { filterCofigurations.Debug }
		runtime "Debug"
		symbols "on"

	filter { filterCofigurations.Release }
		runtime "Release"
		optimize "Speed"

	filter { filterCofigurations.Dist }
		runtime "Release"
		optimize "Speed"
    	symbols "off"
		flags
		{
			"LinkTimeOptimization",
		}
	
	filter { filterCofigurations.AVX512 }
	--	vectorextensions "AVX512" currently not supported need to use buildoptions instead
		buildoptions { "/arch:AVX512" }
	filter { filterCofigurations.AVX2 }
		vectorextensions "AVX2"
	filter { filterCofigurations.SSE4 }
		vectorextensions "SSE2"
