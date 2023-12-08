include "config.lua"

workspace "Logger"
	architecture "x86_64"
	startproject "AllExemple"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
build = "%{wks.location}/build/"
build_int = "%{wks.location}/build-int/"

group "Core"
	include "Logger"
group ""

group "Exemples"
	include "Exemples/AllExemple"
group ""