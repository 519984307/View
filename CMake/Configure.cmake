include(GitUpdate)
if (NOT GitUpdate_SUCCESS)
    return()
endif()

include(StaticRuntime)
include(GTestUtils)
include(ExternalTarget)
include(ConfigureQt)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER "CMakePredefinedTargets/Qt")

option(View_BUILD_TEST          "Build the unit test program." ON)
option(View_AUTO_RUN_TEST       "Automatically run the test program." ON)
option(View_BUILD_SAMPLES       "Build test samples." ON)

set_dynamic_runtime()

DefineExternalTargetEx(
    Utils Extern
    ${View_SOURCE_DIR}/Internal/Utils 
    ${View_SOURCE_DIR}/Internal/Utils
    ${View_BUILD_TEST}
    ${View_AUTO_RUN_TEST}
)

configure_gtest(${View_SOURCE_DIR}/Test/googletest 
                ${View_SOURCE_DIR}/Test/googletest/googletest/include)

configure_qt_windows(Core Widgets Gui Test)
qt_standard_project_setup()

set(Configure_SUCCEEDED TRUE)