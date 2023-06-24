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
#include "View/States/CheckBox.h"

namespace Rt2::View::Visual
{
    using namespace Style;

    CheckBox::CheckBox()
    {
        update();
    }
    

    Data& CheckBox::get(const StateType type)
    {
        if (type == Hover)
            return _hover;
        if (type == Pressed)
            return _pressed;
        return _normal;
    }

    void CheckBox::makeNormal()
    {
        _normal.setFontSize(Icon::Normal);
        _normal.setBorder(Normal::BorderSize);
        _normal.setBorderColor(Normal::BorderLight);
        _normal.setBackgroundColor(Normal::Background);
        _normal.setForegroundColor(Normal::Highlight);
    }

    void CheckBox::makeHover()
    {
        _hover.setFontSize(Icon::Normal);
        _hover.setBorder(Hover::BorderSize);
        _hover.setBorderColor(Hover::BorderLight);
        _hover.setBackgroundColor(Hover::Background);
        _hover.setForegroundColor(Hover::Highlight);
    }

    void CheckBox::makePressed()
    {
        _pressed.setFontSize(Icon::Normal);
        _pressed.setBorder(Pressed::BorderSize);
        _pressed.setBorderColor(Pressed::BorderLight);
        _pressed.setBackgroundColor(Pressed::Background);
        _pressed.setForegroundColor(PressedPrimary::HighlightText);
    }

    void CheckBox::update()
    {
        makeNormal();
        makeHover();
        makePressed();
    }

}  // namespace Rt2::View::Visual
