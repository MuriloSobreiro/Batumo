workspace "Batumo"
	architecture "x64"
	startproject "SandBox"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Batumo/vendor/GLFW/include"
IncludeDir["Glad"] = "Batumo/vendor/Glad/include"
IncludeDir["ImGui"] = "Batumo/vendor/ImGui"
IncludeDir["glm"] = "Batumo/vendor/glm"

group "Dependencies"
	include "Batumo/vendor/GLFW"
	include "Batumo/vendor/Glad"
	include "Batumo/vendor/ImGui"
group ""

project "Batumo"
	location "Batumo"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "btpch.h"
	pchsource "Batumo/src/btpch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.glm}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"BT_PLATAFORM_WINDOWS",
			"BT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Batumo/vendor/spdlog/include",
		"Batumo/src",
		"%{IncludeDir.glm}"
	}

	links{
		"Batumo"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"BT_PLATAFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "BT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "BT_DIST"
		runtime "Release"
		optimize "On"