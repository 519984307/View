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
#include "View/States/PushButton.h"

namespace Rt2::View::Visual
{
    PushButton::PushButton()
    {
        update();
    }

    Data& PushButton::get(const StateType type)
    {
        if (type == Pressed)
            return _pressed;
        if (type == Hover)
            return _hover;
        return _normal;
    }

    void PushButton::makeNormal()
    {
        _normal.setBackgroundColor(Style::Window::Accent);
        _normal.setForegroundColor(Style::Normal::Foreground);
        _normal.setBorderColor(Style::Normal::BorderLight);
        _normal.setBorder(Style::Normal::BorderSize);
        _normal.setBorderRadius(Style::Size::Medium);
    }

    void PushButton::makeHover()
    {
        _hover.setBackgroundColor(Style::Hover::Background);
        _hover.setForegroundColor(Style::Hover::Foreground);
        _hover.setBorderColor(Style::Hover::BorderLight);
        _hover.setBorder(Style::Hover::BorderSize);
        _hover.setBorderRadius(Style::Size::Medium);
    }

    void PushButton::makePressed()
    {
        _pressed.setBackgroundColor(Style::Pressed::Background);
        _pressed.setForegroundColor(Style::Pressed::Foreground);
        _pressed.setBorderColor(Style::Pressed::Border);
        _pressed.setBorder(Style::Pressed::BorderSize);
        _pressed.setBorderRadius(Style::Size::Medium);
    }

    void PushButton::update()
    {
        makeNormal();
        makeHover();
        makePressed();
    }

}  // namespace Rt2::View
