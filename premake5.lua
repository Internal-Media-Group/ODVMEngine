workspace "ODVM"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}



	
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ODVM/libs/GLFW/include"
IncludeDir["Glad"] = "ODVM/libs/Glad/include"
IncludeDir["ImGui"] = "ODVM/libs/ImGui"
IncludeDir["glm"] = "ODVM/libs/glm/glm"

startproject "Sandbox"


	
project "ODVM"
	location "ODVM"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "odvmpch.h"
	pchsource "ODVM/src/odvmpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/libs/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"
		
		defines
		{
			"ODVM_PLATFORM_WINDOWS",
			"_WINDLL",
			"ODVM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "ODVM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ODVM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ODVM_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"ODVM/libs/spdlog/include",
		"ODVM/src"
	}

	links
	{
		"ODVM"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"
		
		defines
		{
			"ODVM_PLATFORM_WINDOWS",
		}
		
	filter "configurations:Debug"
		defines "ODVM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ODVM_RELEASE"
		runtime "Release"		
		optimize "On"

	filter "configurations:Dist"
		defines "ODVM_DIST"
		runtime "Release"
		optimize "On"

group "Dependencies"
	include "ODVM/libs/GLFW"
	include "ODVM/libs/Glad"
	include "ODVM/libs/ImGui"

	