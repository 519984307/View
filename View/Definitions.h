#pragma once
#include "Utils/Definitions.h"
#include "ViewModel/Property.h"

namespace Rt2::View
{
    using ObserverDirection = ViewModel::Direction;

    using BoolModel       = ViewModel::BoolModel;
    using IntModel        = ViewModel::IntModel;
    using FloatModel      = ViewModel::FloatModel;
    using StringModel     = ViewModel::StringModel;
    using StringListModel = ViewModel::StringListModel;

    class IconButtonView;
    class TextEditView;
    class StringListView;
    class FlagView;
    class CheckBoxView;

    enum States
    {
        NONE     = 0x00,
        PRESSED  = 0x01,
        RELEASED = 0x02,
        ENTER    = 0x04,
        ON       = 0x08,
    };

}  // namespace Rt2::View
