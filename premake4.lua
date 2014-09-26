solution "tlmd"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TLMD_BUILD" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSpeed",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "tlmd"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }
excludes { "src/tlmd_server.c" }

project "tlmd-dynamic"
kind "SharedLib"
files { "src/**.c", "src/**.cpp" }
excludes { "src/tlmd_server.c" }
targetname "tlmd"

project "tlmd-server"
kind "ConsoleApp"
files { "src/tlmd_server.c" }
links { "tlmd" }
targetname "tlmd"

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "tlmd" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
