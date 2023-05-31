workspace "HorasTrabajadas"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "HorasTrabajadas"

    outputdir = "%{cfg.buildcfg}"

    IncludeDir = {}
    IncludeDir["MySQL"] = "C:/Program Files/MySQL/Connector C++ 8.0/include/jdbc"

    project "HorasTrabajadas"
        location "HorasTrabajadas"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        
        targetdir ("bin/" .. outputdir)
        objdir ("bin-int/" .. outputdir)
        
        files
        { 
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/libraries/**.h"
        }

        includedirs
        {
            "%{prj.location}/libraries",
            "%{IncludeDir.MySQL}"
        }
        
        defines
        {
            "STATIC_CPPCON"
        }
        
        libdirs
        {
            "C:/Program Files/MySQL/Connector C++ 8.0/lib64/%{cfg.buildcfg}/vs14"
        }

        links
        {
            "mysqlcppconn.lib",
            "mysqlcppconn-static.lib"
        }
        
        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"
