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
	IncludeDir["Glad"] = "Rubr/vendor/Glad/include"
	IncludeDir["ImGui"] = "Rubr/vendor/imgui"
	IncludeDir["Eigen"] = "Rubr/vendor/Eigen"
		
	include "Rubr/vendor/GLFW"
	include "Rubr/vendor/Glad"
	include "Rubr/vendor/imgui"

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
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.Eigen}",
			"%{IncludeDir.ImGui}"
		}

		links {
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"RUBR_PLATFORM_WINDOWS",
				"RUBR_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
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
			"Rubr/vendor/matplotlib-cpp",
			"Rubr/vendor/",
			"C:/Python37/include",
			"C:/Python37/Lib/site-packages/numpy/core/include",
			"Rubr/src"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
				"RUBR_PLATFORM_WINDOWS"
			}

	libdirs {
		"C:/Python37/libs"
	}

	links {
		"Rubr",
		"python37.lib"
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
