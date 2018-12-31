workspace "Rubr"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder
	IncludeDir = {}
	IncludeDir["GLFW"] = "Rubr/vendor/GLFW/include"

	include "Rubr/vendor/GLFW"
	project "Rubr"

		location "Rubr"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "rubrpch.h"
		pchsource "Rubr/src/rubrpch.cpp"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs {
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}"
		}

		links {
			"GLFW",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"RUBR_PLATFORM_WINDOWS",
				"RUBR_BUILD_DLL"
			}

			postbuildcommands {
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Stats")
			}

	filter "configurations:Debug"
		defines "RUBR_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "RUBR_RELEASE"
		buildoptions "/MD"
		symbols "On"
		
	filter "configurations:Dist"
		defines "RUBR_DIST"
		buildoptions "/MD"
		symbols "On"


	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs {
			"Rubr/vendor/spdlog/include",
			"Rubr/src"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"RUBR_PLATFORM_WINDOWS"
			}

	links {
		"Rubr"
	}

	filter "configurations:Debug"
		defines "RUBR_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "RUBR_RELEASE"
		buildoptions "/MD"
		symbols "On"
		
	filter "configurations:Dist"
		defines "RUBR_DIST"
		buildoptions "/MD"
		symbols "On"



		
	project "Stats"
		location "Stats"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs {
			"Rubr/vendor/spdlog/include",
			"Rubr/vendor/Eigen",
			"Rubr/src",
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"RUBR_PLATFORM_WINDOWS"
			}

	links {
		"Rubr"
	}

	filter "configurations:Debug"
		defines "RUBR_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "RUBR_RELEASE"
		buildoptions "/MD"
		symbols "On"
		
	filter "configurations:Dist"
		defines "RUBR_DIST"
		buildoptions "/MD"
		symbols "On"
