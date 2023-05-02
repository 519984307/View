set(TestTargetName ${TargetName}Test)
include(TestDirectory)
gen_path_to_here()
include(GroupSet)

set_group(
    TestTarget_SRC
    Source:Test1.cpp
    Source:Test2.cpp
)

include_directories(
    ${Utils_INCLUDE}
    ${View_INCLUDE}
    ${ViewModel_INCLUDE}
    ${GTEST_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)

target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
    ${View_LIBRARY}
    ${ViewModel_LIBRARY}
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Test 
    Qt::Platform
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)


if (View_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()
