set(TestTargetName ${TargetName}Test)
include(TestDirectory)
gen_path_to_here()
include(GroupSet)

set_group(
    TestTarget_SRC
    Source:Test1.cpp
)

include_directories(
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
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)


if (View_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()


include_directories(
    ${Utils_INCLUDE}
    ${View_INCLUDE}
    ${ViewModel_INCLUDE}
    ${GTEST_INCLUDE}
)
add_qt_test_file(
    Test2 
    ${TestTargetName}.Widgets
    FALSE
)

target_link_libraries(
    ${TestTargetName}.Widgets
    ${Utils_LIBRARY}
    ${View_LIBRARY}
    ${ViewModel_LIBRARY}
    ${GTEST_LIBRARY}
)