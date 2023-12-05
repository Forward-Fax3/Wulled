project "spdlog"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	location "%{prj.name}"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}",
		"%{prj.name}/include",
		"%{prj.name}/src",
	}

	defines 
	{
		"SPDLOG_COMPILED_LIB",
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	runtime "Release"
	optimize "on"

	filter "configurations:Dist"
	runtime "Release"
	optimize "on"
    symbols "off"
	
project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	location "%{prj.name}"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/imgui_demo.cpp",
		"%{prj.name}/imgui.cpp",
		"%{prj.name}/imgui_draw.cpp",
		"%{prj.name}/imgui_widgets.cpp",
		"%{prj.name}/imgui_tables.cpp",
		"%{prj.name}/backends/imgui_impl_win32.cpp",
		"%{prj.name}/backends/imgui_impl_opengl3.cpp",
		"%{prj.name}/backends/imgui_impl_dx12.cpp",
		
		"%{prj.name}/imconfig.h",
		"%{prj.name}/imgui.h",
		"%{prj.name}/imgui_internal.h",
		"%{prj.name}/imstb_rectpack.h",
		"%{prj.name}/imstb_textedit.h",
		"%{prj.name}/imstb_truetype.h",
		"%{prj.name}/backends/imgui_impl_win32.h",
		"%{prj.name}/backends/imgui_impl_opengl3.h",
		"%{prj.name}/backends/imgui_impl_dx12.h",
	}

	includedirs
	{
		"%{prj.name}",
	}

--	defines
--	{
--		"IMGUI_API=__declspec(dllexport)"
--	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

		filter "system:windows"
			systemversion "latest"

		filter "system:linux"
			pic "On"
			systemversion "latest"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			runtime "Release"
			optimize "on"
			symbols "off"

project "glm"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	location "%{prj.name}"

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
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	runtime "Release"
	optimize "on"

	filter "configurations:Dist"
	runtime "Release"
	optimize "on"
    symbols "off"

project "DXTK12"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	location "%{prj.name}"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/Inc/**.h",
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp",
		"%{prj.name}/Inc/**.inl",
		"%{prj.name}/Src/**.inc",
	}

	removefiles
	{
		"%{prj.name}/Src/AlphaTestEffect.cpp",
		"%{prj.name}/Src/BasicEffect.cpp",
		"%{prj.name}/Src/BasicProcess.cpp",
		"%{prj.name}/Src/BasicPostProcess.cpp",
		"%{prj.name}/Src/DebugEffect.cpp",
		"%{prj.name}/Src/DualPostProcess.cpp",
		"%{prj.name}/Src/DualTextureEffect.cpp",
		"%{prj.name}/Src/EnvironmentMapEffect.cpp",
		"%{prj.name}/Src/NormalMapeffect.cpp",
		"%{prj.name}/Src/PBREffect.cpp",
		"%{prj.name}/Src/ResourceUploadBatch.cpp",
		"%{prj.name}/Src/SkinnedEffect.cpp",
		"%{prj.name}/Src/SpriteBatch.cpp",
		"%{prj.name}/Src/ToneMapPostProcess.cpp",
		"%{prj.name}/Src/XboxDDSTextureLoader.cpp",

		"%{prj.name}/Inc/XboxDDSTextureLoader.h",
	}

	includedirs
	{
		"%{prj.name}",
		"%{prj.name}/Inc/",
		"%{prj.name}/Src/",
		"%{prj.name}/Src/**",
	}

	links
	{
		"d3d12.lib",
		"dxgi.lib",
		"d3dcompiler.lib"
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	runtime "Release"
	optimize "on"

	filter "configurations:Dist"
	runtime "Release"
	optimize "on"
    symbols "off"

project "glatter"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	location "%{prj.name}"

	targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"%{prj.name}/include",
	}

	systemversion "latest"
	cdialect "c17"
	cppdialect "c++20"

	filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	runtime "Release"
	optimize "on"

	filter "configurations:Dist"
	runtime "Release"
	optimize "on"
    symbols "off"