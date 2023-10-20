--
-- premake_config.lua
--
-- Premake solution to build the EDK STD projects.
-- Ivan Sancho, Escuela Superior de Arte y Tecnologia (ESAT) Valencia, 2023/24
-- Algorithms & Data Structures
--
-- All rights are reserved.
--

PROJ_DIR = path.getabsolute("./..")

PROJECT_NAMES = {
  "PRXX_TestMemoryManager",
  "PR00_MemoryNode",
  --"PR01_Vector",
  --"PR02_CircularVector",
  --"PR03_MovableVector",
  --"PR04_List",
  --"PR05_DLList",
  --"PR06_CircularList",
  --"PR07_CircularDLList",
  --"PR08_Stack",
  --"PR09_Queue",
  --"PR10_Logger",
  --"PR11_Comparative",
  --"PR12_SortingAlgorithms",
}

-- Solution workspace declaration:
workspace("DS_ALG_AI1" .. _ACTION)
  location(PROJ_DIR .. "/build/")
  language "C"
  kind "ConsoleApp"
  startproject "PR00_MemoryNode"
  platforms {
    "x32",
    "x64",
    "Native",
  }
  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }
  configurations { "Debug", "Release" }

-- Workspace "Debug" configuration:
filter { "configurations:Debug" }
  defines {
    "DEBUG",
  }
  symbols "On"
  warnings "Extra"
  targetsuffix "_d"

-- Workspace "Release" configuration:
filter { "Release" }
  defines {
    "NDEBUG",
  }
  optimize "On"
  optimize "Size"
  flags {
    "No64BitChecks",
    "NoPCH",
  }


--[[********************* PROJECT GENERATOR FUNCTION *********************]]--
function GenerateProject(project_name, project_group)
  project(project_name)
    location (PROJ_DIR .. "/build/" .. project_name .. "/" .. _ACTION)
    includedirs {
      path.join(PROJ_DIR, "include/"),
      path.join(PROJ_DIR, "deps/include/"),
    }
    files {
      path.join(PROJ_DIR, "include/*.h"),
      path.join(PROJ_DIR, "include/common_def.h"),
      path.join(PROJ_DIR, "deps/include/EDK_MemoryManager/*.h"),
    }

    libdirs { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager") }

    filter { "configurations:Debug", "platforms:x32" }
      targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
      links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x32/EDK_MemoryManager_Windows_d") }
    filter { "configurations:Debug", "platforms:x64" }
      targetdir (path.join(PROJ_DIR, "bin/Debug/x64"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Debug"))
      targetsuffix "_d"
      links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x64/EDK_MemoryManager_Windows_d") }
    filter { "configurations:Release", "platforms:x32" }
      targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
      links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x32/EDK_MemoryManager_Windows") }
    filter { "configurations:Release", "platforms:x64" }
      targetdir (path.join(PROJ_DIR, "bin/Release/x64/"))
      objdir(path.join(PROJ_DIR, "build/" .. project_name .. "/Release"))
      links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x64/EDK_MemoryManager_Windows") }
end --Function "GenerateProject" ends here.

--Calling the Lua function:
for i, prj in ipairs(PROJECT_NAMES) do
  GenerateProject(prj)
end


project "PRXX_TestMemoryManager"
  files {
    path.join(PROJ_DIR, "tests/test_memory_manager.c"),
  }

project "PR00_MemoryNode"
	files {
	  path.join(PROJ_DIR, "include/adt_memory_node.h"),
	  path.join(PROJ_DIR, "src/adt_memory_node.c"),
	  path.join(PROJ_DIR, "tests/test_memory_node.c"),
  }

--[[
project "PR01_Vector"
  files {
    path.join(PROJ_DIR, "include/adt_memory_node.h"),
    path.join(PROJ_DIR, "src/adt_memory_node.c"),
    path.join(PROJ_DIR, "include/adt_vector.h"),
    path.join(PROJ_DIR, "src/adt_vector.c"),
    path.join(PROJ_DIR, "tests/test_vector.c"),
  }
]]--
