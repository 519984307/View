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
#include <QColor>
#include <QEvent>
#include <QVariant>
#include "Utils/Definitions.h"
#include "ViewModel/Property.h"

class QVBoxLayout;
class QHBoxLayout;
class QBoxLayout;
class QLabel;
class QSplitter;
class QLineEdit;
class QWidget;
class QTextEdit;

namespace Rt2::View
{
    using ObserverDirection = ViewModel::Direction;

    using VoidModel       = ViewModel::VoidModel;
    using BoolModel       = ViewModel::BoolModel;
    using IntModel        = ViewModel::IntModel;
    using FloatModel      = ViewModel::FloatModel;
    using DoubleModel     = ViewModel::DoubleModel;
    using StringModel     = ViewModel::StringModel;
    using StringListModel = ViewModel::StringListModel;
    using VariantModel    = ViewModel::ViewModel<QVariant>;

    class StyleSheetWriter;
    class IconButtonView;
    class TextEditView;
    class StringListView;
    class FlagView;
    class CheckBoxView;
    class PushButtonView;
    class LabelView;

    namespace Visual
    {
        class Data;
        class State;
        class Layout;

        enum StateType
        {
            None,
            Normal,
            Hover,
            Pressed,
            Disabled,
            Focused,
            Error,
            On,
            Off,
        };

        enum StateAttribute
        {
            NoAttribute,
            NoBackground = 0x00000001,
            ToggleOn     = 0x00000002,
            ToggleOff    = 0x00000003,
            Dirty        = 0x10000000,
        };

        enum EventFlag
        {
            HoverState        = 0x01,
            ApplyOnShow       = 0x02,
            LeftClickActive   = 0x04,
            LeftReleaseActive = 0x08,
        };
    }  // namespace Visual

    using VisualState     = Visual::State;
    using VisualLayout    = Visual::Layout;
    using VisualData      = Visual::Data;
    using VisualType      = Visual::StateType;
    using VisualFlag      = Visual::EventFlag;
    using VisualAttribute = Visual::StateAttribute;

    enum States
    {
        NONE     = 0x00,
        PRESSED  = 0x01,
        RELEASED = 0x02,
        ENTER    = 0x04,
        ON       = 0x08,
        OFF      = 0x10,
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
        EC_006,                           // ViewConstruction
        EC_007,                           // unused
        EC_008,                           // unused
        EC_009,                           // unused
        EC_010,                           // unused, etc...
    };

    struct Stops
    {
        qreal  offs{0};
        QColor color{0, 0, 0};
    };

    struct GradientBox
    {
        qreal x1, y1, x2, y2;
    };

    using GradientStops = SimpleArray<Stops>;

    constexpr GradientBox GradientHor = {0, 0, 1, 0};
    constexpr GradientBox GradientVer = {0, 0, 0, 1};

}  // namespace Rt2::View
