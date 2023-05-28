include(GroupSet)
set(TargetName TextEdit)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Header:*.h
)

include_directories(
    ${View_INCLUDE} 
    ${Utils_INCLUDE} 
)


add_executable(
    ${TargetName} 
    ${TargetName_SRC}
    ${View_ICON_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${View_LIBRARY} 
    ${Utils_LIBRARY} 
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)

copy_to_bin(${TargetName} ${CMAKE_SOURCE_DIR}/Bin)