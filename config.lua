
-- Logger Config

Externals = {}

Internals = {}
Internals["Logger"]         = "%{wks.location}/Logger"
Internals["AllExemple"]     = "%{wks.location}/Exemples/AllExemple"

InternalBuilds = {}

newoption {
    trigger         = "libtype",
    value           = "STATIC_LIB",
    description     = "ce flag peut prendre les valeur {STATIC_LIB ou DYNAMIC_LIB}",
    default         = "STATIC_LIB",
    category        = "Lib",
    allowed         = {
        {"STATIC_LIB", "STATIC LIB"},
        {"DYNAMIC_LIB", "DYNAMIC LIB"}
    }
}

function getLibraryType()
	libtype = _OPTIONS["libtype"]

    if libtype == "DYNAMIC_LIB" then
        return "SharedLib"
    else
        return "StaticLib"
    end
end

libraryType = getLibraryType()
