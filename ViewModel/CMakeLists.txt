set(TargetName ViewModel)
include(GroupSet)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Header:*.h
)

include_directories(
    ${Utils_INCLUDE} 
)


add_library(
    ${TargetName} 
    ${TargetName_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${Utils_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
