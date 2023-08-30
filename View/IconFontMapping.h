/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#pragma once

namespace Rt2::View
{
    enum IconMap
    {
        IconNone,
        IconFlagOn,
        IconFlagOff,
        IconsStart = ' ' - 1,
        //
        IconAdd,
        IconEdit,
        IconDelete,
        IconClear,
        IconBack,
        IconUp,
        IconForward,
        IconDown,
        IconTriLeft,
        IconTriUp,
        IconTriRight,
        IconTriDown,
        IconMenu1,
        IconMenu2,
        IconMenu3,
        IconBox,
        IconCheck0,
        IconCheck1,
        IconMinimize,
        IconMaximize,
        IconClose,
        IconSettings,
        IconSettings2,
        IconExit,
        IconRefresh,
        IconRefresh2,
        IconUndo,
        IconRedo,
        IconExpand,
        IconContract,
        IconFile1,
        IconFile2,
        IconFolder1,
        IconFolder2,
        IconLink,
        IconPointRight,
        IconPointUp,
        IconPointLeft,
        IconPointDown,
        IconPointStop,
        IconDownload,
        IconUpload,
        IconSortVert,
        IconSortHor,
        IconLogIn,
        IconLogOut,
        IconWindow,
        IconHome,
        IconCopy,
        //
        IconsEnd,
        // Note: additions need to be synchronized
        // in EmitterUtils::validateIcon 
    };

    class Qiu
    {
    public:
        static QString to(const IconMap& ico)
        {
            return {QChar(ico)};
        }
    };

}  // namespace Rt2::View
