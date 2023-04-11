include(GroupSet)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Header:*.h
    Resource:Icons/*.qrc
)

qt_add_resources(
    TargetName_RES 
    Icons/icons.qrc
)

include_directories(
    ${Utils_INCLUDE} 
    ${View_INCLUDE} 
)


add_library(
    ${TargetName} 
    ${TargetName_SRC}
    ${TargetName_RES}
)

target_link_libraries(
    ${TargetName} 
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui 
    ${Utils_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
