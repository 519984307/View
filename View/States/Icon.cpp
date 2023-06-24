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
#include "View/States/Icon.h"

namespace Rt2::View::Visual
{
    using namespace Style;

    Icon::Icon()
    {
        update();
    }

    Data& Icon::get(const StateType type)
    {
        if (type == Hover)
            return _hover;
        if (type == Pressed)
            return _pressed;
        return _normal;
    }

    void Icon::mark()
    {
        if (!hasBackground())
        {
            Data::clearBackground(_hover);
            Data::clearBackground(_pressed);
            Data::clearBackground(_normal);
        }
    }

    void Icon::makeNormal()
    {
        _normal.setFontSize(Style::Icon::Normal);
        _normal.setBackgroundColor(hasBackground() ? Window::Background : Misc::Transparent);
        _normal.setForegroundColor(hasBackground() ? Normal::Foreground : PressedPrimary::Foreground);
    }

    void Icon::makeHover()
    {
        _hover.setFontSize(Style::Icon::Normal);

        if (!hasBackground())
        {
            _hover.setBackgroundColor(Misc::Transparent);
            _hover.setForegroundColor(PressedPrimary::Highlight);
        }
        else
        {
            _hover.setBorderRadius(Size::Small);
            _hover.setBorder(Size::Tiny);
            _hover.setBorderColor(Hover::Border);
            _hover.setBackgroundColor(Hover::Background);
            _hover.setForegroundColor(Hover::Foreground);
        }
    }

    void Icon::makePressed()
    {
        _pressed.setFontSize(Style::Icon::Normal);

        if (!hasBackground())
        {
            _pressed.setBackgroundColor(Misc::Transparent);
            _pressed.setForegroundColor(PressedSecondary::Foreground);
        }
        else
        {
            _pressed.setBorderRadius(Size::Small);
            _pressed.setBorder(Size::Tiny);
            _pressed.setBorderColor(Pressed::Border);
            _pressed.setBackgroundColor(Pressed::Background);
            _pressed.setForegroundColor(Pressed::Foreground);
        }
    }

    void Icon::update()
    {
        makeHover();
        makeNormal();
        makePressed();
    }
}  // namespace Rt2::View::Visual
