--project "Glad"
--	kind "StaticLib"
--	language "C"
--    cdialect "c17"
--	staticruntime "on"
--    location "%{prj.name}"
--
--    filter "configurations:debug"
--        files
--        {
--            "%{prj.name}/Debug/include/**.h",
--            "%{prj.name}/Debug/src/**.c",
--        }
--
--        includedirs
--        {
--            "%{prj.name}/debug/include/",
--            "%{prj.name}/Debug/src",
--        }
--
--		runtime "Debug"
--		symbols "on"
--
--    filter "configurations:Release"
--        files
--        {
--            "%{prj.name}/main/include/**.h",
--            "%{prj.name}/main/src/**.c",
--        }
--
--        includedirs
--        {
--            "%{prj.name}/main/include/",
--            "%{prj.name}/main/src",
--        }
--
--		runtime "Release"
--		optimize "Speed"
--
--    filter "configurations:dist"
--        files
--        {
--            "%{prj.name}/main/include/**.h",
--            "%{prj.name}/main/src/**.c",
--        }
--
--        includedirs
--        {
--            "%{prj.name}/main/include/",
--            "%{prj.name}/main/src",
--        }
--
--		runtime "Release"
--		optimize "Speed"
--    	symbols "off"
        
project "glew"
	kind "StaticLib"
	language "C++"
    cdialect "c17"
    cppdialect "c++20"
	staticruntime "off"
    location "%{prj.name}"
	toolset "clang"
    
    targetdir ("%{wks.location}/bin/" .. output .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/" .. output .. "/intermediate/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.c",
    }

    includedirs
    {
        "%{prj.name}/include/",
        "%{prj.name}/src",
    }

    defines
    {
        "GLEW_STATIC",
    }

	flags
	{
		"MultiProcessorCompile",
	}

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
