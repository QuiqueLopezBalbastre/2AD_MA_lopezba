PROJ_DIR = path.getabsolute("./")

workspace("TestSolution")
  location(PROJ_DIR .. "/build/")
  language "C++"
  kind "ConsoleApp"
  startproject "TestProject"
  platforms {
    "x32",
    "x64",
  }
  configurations {
    "Debug",
  }

project "TestProject"
  targetdir (path.join(PROJ_DIR, "bin/"))
  filter "Debug"
    warnings "Extra"
    symbols "On"
    targetsuffix "_d"
    flags {
      "NoPCH",
    }
    defines {
      "DEBUG",
      "_CRT_SECURE_NO_WARNINGS",
    }

  includedirs {
    "./",
  }

  files {
    "./test.cc",
  }
