include(GroupSet)

set_group(
    TargetName_SRC 
    Source:*.cpp
    Source/States:States/*.cpp
    Header:*.h
    Header/States:States/*.h
    Content:Icons/Source/*.sfd
    Content/Source:Icons/Source/*.svg
    Content/Resource:Icons/*.qrc
)

#qt_add_resources(
#    TargetName_RES 
#    Icons/Icons.qrc
#)

include_directories(
    ${Utils_INCLUDE} 
    ${Thread_INCLUDE} 
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
    ${Thread_LIBRARY} 
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)

qt_auto_resource(${TargetName})
