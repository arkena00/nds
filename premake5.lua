require('cmake')

workspace "nds"
	configurations { "release"}

project "nds"
	location "./"
	kind "ConsoleApp"
	language "C++"
	targetname "nds"
	targetdir "bin"


	flags { "C++14" }

	files { "source/**.cpp" }

	includedirs { "include" }