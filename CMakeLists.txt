cmake_minimum_required(VERSION 3.15)
project(Widgets)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Widgets_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Widgets_SOURCE_DIR}/CMake 
  ${Widgets_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Widgets_ExternalTarget)
    set(TargetFolders ${Widgets_TargetFolders})
    set(TargetName    ${Widgets_TargetName})
    set(TargetGroup   ${Widgets_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    include(${Utils_SOURCE_DIR}/CMake/Locals.cmake)

    set(TargetFolders TRUE)
    set(TargetName Widgets)
    set(TargetGroup )

    set(Widgets_INCLUDE  ${Widgets_SOURCE_DIR})
    set(Widgets_LIBRARY  ${TargetName})
endif()

add_subdirectory(Widgets)

if (Widgets_BUILD_TEST)
    if (NOT Widgets_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
