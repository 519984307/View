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
#include "View/States/Flag.h"

namespace Rt2::View::Visual
{
    Flag::Flag()
    {
        update();
    }

    Data& Flag::get(const StateType type)
    {
        if (type == Pressed)
        {
            if (isToggleOn())
                return _pressedOn;
            return _pressed;
        }
        if (type == Hover)
        {
            if (isToggleOn())
                return _hoverOn;
            return _hover;
        }

        if (isToggleOn())
            return _normalOn;

        return _normal;
    }

    void Flag::makeNormal()
    {
        _normal.setBackgroundColor(Style::Misc::Transparent);
        _normal.setForegroundColor(Style::PressedPrimary::Background);


        _normalOn.setBackgroundColor(Style::Misc::Transparent);
        _normalOn.setForegroundColor(Style::PressedPrimary::Border);
    }

    void Flag::makeHover()
    {
        _hover.setBackgroundColor(Style::Misc::Transparent);
        _hover.setForegroundColor(Style::PressedSecondary::Border);

        _hoverOn.setBackgroundColor(Style::Misc::Transparent);
        _hoverOn.setForegroundColor(Style::PressedSecondary::Border);
    }

    void Flag::makePressed()
    {
        _pressed.setBackgroundColor(Style::PressedPrimary::Background);
        _pressed.setForegroundColor(Style::PressedPrimary::Border);

        _pressedOn.setBackgroundColor(Style::PressedSecondary::Background);
        _pressedOn.setForegroundColor(Style::PressedSecondary::Border);
    }

    void Flag::update()
    {
        makeNormal();
        makeHover();
        makePressed();
    }

}  // namespace Rt2::View::Visual
