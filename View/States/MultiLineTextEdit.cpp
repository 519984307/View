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
#include "View/States/MultiLineTextEdit.h"

namespace Rt2::View::Visual
{
    using namespace Style;

    MultiLineTextEdit::MultiLineTextEdit()
    {
        update();
    }

    Data& MultiLineTextEdit::get(const StateType type)
    {
        return _normal;
    }

    void MultiLineTextEdit::makeNormal()
    {
        _normal.setFontSize(FontSize::Normal);
        _normal.setBorder(Margin::None);
        _normal.setForegroundColor(TextEdit::Foreground);
        _normal.setBackgroundColor(TextEdit::Background);
        _normal.setHighlightBackgroundColor(Normal::Highlight);
        _normal.setHighlightForegroundColor(Normal::HighlightText);
    }


    void MultiLineTextEdit::update()
    {
        makeNormal();
    }
}  // namespace Rt2::View::Visual
