project "AllExemple"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ( build .. outputdir .. "/%{prj.name}" )
    objdir ( build_int .. outputdir .. "/%{prj.name}" )

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "./src/",
        "%{Internals.Logger}/src"
    }

    links {
        "Logger"
    }

    if libraryType == "StaticLib" then
		defines
		{
			"NKENTSUU_STATIC"
		}
	end

    filter "system:windows"
        systemversion "latest"
		optimize "off"

        if libraryType == "SharedLib" then
            postbuildcommands {
                ("{COPY} " .. build .. outputdir .. "/Logger/Logger.dll " .. build .. outputdir .. "/%{prj.name}")
            }
        end
    
    filter "system:macosx"

    filter "system:linux"

    filter "configurations:Debug"
        defines {  "NKENTSUU_DEBUG", "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NKENTSUU_RELEASE" }
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines { "NKENTSUU_DIST" }
        runtime "Release"
        optimize "on"

    filter {}
