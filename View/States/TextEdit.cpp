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
#include "View/States/TextEdit.h"

namespace Rt2::View::Visual
{
    using namespace Style;

    TextEdit::TextEdit()
    {
        update();
    }

    Data& TextEdit::get(const StateType type)
    {
        if (type == Hover)
            return _hover;
        return _normal;
    }

    void TextEdit::makeNormal()
    {
        _normal.setFontSize(FontSize::Normal);
        _normal.setBorder(Margin::Tiny);
        _normal.setForegroundColor(Normal::Foreground);
        _normal.setBorderColor(Normal::BorderLight);
        _normal.setBackgroundColor(Normal::Background);
        _normal.setHighlightBackgroundColor(Normal::Highlight);
        _normal.setHighlightForegroundColor(Normal::HighlightText);

        _normal.setPadding(Size::Medium, Size::Medium);
        _normal.setBorderRadius(Size::Medium);
    }

    void TextEdit::makeHover()
    {
        _hover.setFontSize(FontSize::Normal);
        _hover.setBorder(Margin::Tiny);
        _hover.setForegroundColor(Hover::Foreground);
        _hover.setBorderColor(Hover::BorderLight);
        _hover.setBackgroundColor(Hover::Background);
        _hover.setHighlightBackgroundColor(Normal::Highlight);
        _hover.setHighlightForegroundColor(Normal::HighlightText);

        _hover.setPadding(Size::Medium, Size::Medium);
        _hover.setBorderRadius(Size::Medium);
    }

    void TextEdit::update()
    {
        makeNormal();
        makeHover();
    }
}  // namespace Rt2::View::Visual
