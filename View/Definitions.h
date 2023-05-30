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
#include <QEvent>
#include "Utils/Definitions.h"
#include "ViewModel/Property.h"

namespace Rt2::View
{
    using ObserverDirection = ViewModel::Direction;

    using BoolModel       = ViewModel::BoolModel;
    using IntModel        = ViewModel::IntModel;
    using FloatModel      = ViewModel::FloatModel;
    using DoubleModel     = ViewModel::DoubleModel;
    using StringModel     = ViewModel::StringModel;
    using StringListModel = ViewModel::StringListModel;

    class IconButtonView;
    class TextEditView;
    class StringListView;
    class FlagView;
    class CheckBoxView;
    class PushButtonView;

    enum States
    {
        NONE     = 0x00,
        PRESSED  = 0x01,
        RELEASED = 0x02,
        ENTER    = 0x04,
        ON       = 0x08,
    };

    enum EventCodes
    {
        // EC_<idx++>: to prevent conflicts custom events
        // should add new codes here to reserve global codes.
        // ++ (Document where it is used.)
        EC_001 = QEvent::Type::User + 1,  // DirListEventCode
        EC_002,                           // DirPushEventCode
        EC_003,                           // DirClickEventCode
        EC_004,                           // reserved
        EC_005,                           // reserved
        EC_006,                           // unused
        EC_007,                           // unused
        EC_008,                           // unused
        EC_009,                           // unused
        EC_010,                           // unused, etc...
    };

}  // namespace Rt2::View
