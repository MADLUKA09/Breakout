workspace "Breakout"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	IncludeDir = {}
	IncludeDir["SDL2"] = "Breakout/vendor/SDL2"
	IncludeDir["SDL2Mixer"] = "Breakout/vendor/SDL2_Mixer"

project "Breakout"
	location "Breakout"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/tinyxml2/tinyxml2.h",
		"%{prj.name}/vendor/tinyxml2/tinyxml2.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/tinyxml2",
		"%{IncludeDir.SDL2}/include",
		"%{IncludeDir.SDL2Mixer}/include"
	}

	libdirs
	{
		"%{IncludeDir.SDL2}/lib/x64",
		"%{IncludeDir.SDL2Mixer}/lib"
	}

	links
	{
		"SDL2",
		"SDL2main",
		"SDL2_mixer"
	}

	filter "configurations:Debug"
		defines "BO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BO_RELEASE"
		optimize "On"