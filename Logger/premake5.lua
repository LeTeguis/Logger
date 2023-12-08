project "Logger"
    kind (libraryType)
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
        "./src"
    }

    libdirs {
    }

    defines {
		"NKENTSUU_EXPORTS", "_CRT_SECURE_NO_WARNINGS"
    }

    links {
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
        links {
        }

        linkoptions { "-lpthread" }

    filter "system:macosx"
        xcodebuildsettings
        {
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["USeModernBuildSystem"] = "NO"
        }

        links {
        }

        -- Ajout d'options de compilation pour toutes les configurations sous macOS
        buildoptions { "-stdlib=libc++", "-fPIC", "-pthread" }

    filter "system:linux"
        links {
        }

        -- Ajout d'options de compilation pour toutes les configurations sous Linux
        buildoptions { "-fPIC", "-pthread" }

    filter "configurations:Debug"
        defines {  "NKENTSUU_DEBUG" , "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH "}
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
