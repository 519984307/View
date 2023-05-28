if (WIN32)
    include(GroupSet)
    set_group(View_ICON_SRC 
       Generated/Win32:${View_DIRECTORY}/Extras/AppIcon/Win32/Resource.rc
       Generated/Win32:${View_DIRECTORY}/Extras/AppIcon/Win32/AppIcon.ico
    )
endif()
