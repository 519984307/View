cmake_minimum_required(VERSION 3.22)
project(View)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${View_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${View_SOURCE_DIR}/CMake 
  ${View_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (View_ExternalTarget)
    set(TargetFolders ${View_TargetFolders})
    set(TargetName    ${View_TargetName})
    set(TargetGroup   ${View_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    include(${Utils_SOURCE_DIR}/CMake/Locals.cmake)

    set(TargetFolders TRUE)
    set(TargetName View)
    set(TargetGroup )

    set(View_INCLUDE  ${View_SOURCE_DIR})
    set(View_LIBRARY  ${TargetName})
endif()

add_subdirectory(View)
add_subdirectory(ViewModel)

if (View_BUILD_SAMPLES)
    set(TargetGroup Samples)
    add_subdirectory(Samples)
endif()

if (View_BUILD_TEST)
    if (NOT View_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
