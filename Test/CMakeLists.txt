set(TestTargetName ${TargetName}Test)
include(TestDirectory)
gen_path_to_here()
include(GroupSet)

set_group(
    TestTarget_SRC
    Source:Test1.cpp
)

include_directories(
    .
    ${GTEST_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)

target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)


if (View_AUTO_RUN_TEST)
    run_test(${TestTargetName})
endif()


add_qt_test_file(
    Test2 
    ${TestTargetName}.Test2
    ${View_AUTO_RUN_TEST}
)
