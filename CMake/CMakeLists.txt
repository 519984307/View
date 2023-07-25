
if (NOT MSVC)
    return()
endif()

include(GroupSet)
include(ExternalTarget)
set(TargetName ALL_CMAKE)
set(TargetGroup CMakePredefinedTargets)
set(GroupRoot ../)

group_common(TargetName_SRC)
group_extra(TargetName_EXT)

add_custom_target(
    ${TargetName} 
    ALL SOURCES 
    ${TargetName_SRC}
    ${TargetName_EXT}
    )


set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
