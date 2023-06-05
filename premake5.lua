workspace "HorasTrabajadas"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "HorasTrabajadas"

    outputdir = "%{cfg.buildcfg}"

    SolutionDir = "$(SolutionDir)"
    
    IncludeDir = {}
    IncludeDir["MySQL"] = "C:/Program Files/MySQL/Connector C++ 8.0/include/jdbc"
    IncludeDir["cURL"] = SolutionDir .. "vendor/curl/builds/libcurl-vc14-x64-release-dll-ipv6-sspi-schannel"
    IncludeDir["VersionControl"] = SolutionDir .. "lib"

    project "HorasTrabajadas"
        location "HorasTrabajadas"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        
        targetdir (SolutionDir .. "bin/" .. outputdir)
        objdir (SolutionDir .. "bin-int/")
        
        files
        { 
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/libraries/**.h"
        }

        includedirs
        {
            "%{prj.location}/libraries",
            "%{IncludeDir.MySQL}",
            "%{IncludeDir.cURL}/include",
            SolutionDir .. "HTVersionControl/libraries"
        }
        
        defines
        {
            "STATIC_CPPCON",
            "CURL_STATICLIB"
        }
        
        libdirs
        {
            "C:/Program Files/MySQL/Connector C++ 8.0/lib64/%{cfg.buildcfg}/vs14",
            "%{IncludeDir.cURL}/lib",
            "%{IncludeDir.VersionControl}/" .. outputdir
        }

        links
        {
            "mysqlcppconn.lib",
            "mysqlcppconn-static.lib",
            "libcurl.lib",
            "HTVersionControl.lib",
            "HTVersionControl"
        }
        
        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"

    project "HTVersionControl"
        location "HTVersionControl"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
            
        targetdir (SolutionDir .. "lib/" .. outputdir)
        objdir (SolutionDir .. "bin-int/")
            
        files
        { 
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/libraries/**.h"
        }

        includedirs
        {
            "%{prj.location}/libraries",
            "%{IncludeDir.cURL}/include"
        }
            
        defines
        {
            "CURL_STATICLIB"
        }

        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"
            defines "WL_DIST"