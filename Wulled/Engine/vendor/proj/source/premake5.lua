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
	language "C"
    cdialect "c17"
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

    filter "configurations:debug"
		runtime "Debug"
		symbols "on"

    filter "configurations:Release"
		runtime "Release"
		optimize "Speed"

    filter "configurations:dist"
		runtime "Release"
		optimize "Speed"
    	symbols "off"
	    flags
	    {
	    	"LinkTimeOptimization",
	    }
