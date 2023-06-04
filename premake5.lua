workspace "HorasTrabajadas"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "HorasTrabajadas"

    outputdir = "%{cfg.buildcfg}"

    IncludeDir = {}
    IncludeDir["MySQL"] = "C:/Program Files/MySQL/Connector C++ 8.0/include/jdbc"
    IncludeDir["cURL"] = "C:/curl/builds/libcurl-vc-x86-release-static-ipv6-sspi-schannel/include"

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
            "STATIC_CPPCON",
            "CURL_STATICLIB"
        }
        
        libdirs
        {
            "C:/Program Files/MySQL/Connector C++ 8.0/lib64/%{cfg.buildcfg}/vs14",
            "C:/curl/builds/libcurl-vc-x86-release-static-ipv6-sspi-schannel/lib"
        }

        links
        {
            "mysqlcppconn.lib",
            "mysqlcppconn-static.lib",
            "libcurl.lib"
        }
        
        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"
