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
#include <QSize>

namespace Rt2::View
{
    class Metrics // should be serialized
    {
    public:
        static constexpr int defaultTextSize{10};
        static constexpr int gm{0};
        static constexpr int gs{0};
        static constexpr int h1{defaultTextSize + 14};
        static constexpr int h2{defaultTextSize + 12};
        static constexpr int h3{defaultTextSize + 10};
        static constexpr int h4{defaultTextSize + 8};
        static constexpr int h5{defaultTextSize + 4};
        static constexpr int h6{defaultTextSize + 2};
        static constexpr int h7{defaultTextSize};
        static constexpr int h8{defaultTextSize - 2};
        static constexpr int h9{defaultTextSize - 4};

        static constexpr QSize minWindow{320, 240};
        static constexpr QSize minPanel{200, 100};
        static constexpr int   minHeight{24};
        static constexpr int   minWidth{24};
        static constexpr QSize ctrlMin{minWidth, minHeight};

        static constexpr int iconFontSize{defaultTextSize + 2};
        static constexpr int iconHeight{iconFontSize};
        static constexpr int iconWidth{iconFontSize};

        static constexpr int indent{6};
        static constexpr int scrollbarSize{minWidth >> 1};
        static constexpr int borderSizeThick{3};
        static constexpr int borderSizeThin{2};
        static constexpr int borderSizeTiny{1};


        static constexpr QSize iconMin{
            iconWidth + 2 * borderSizeThick,
            iconWidth + 2 * borderSizeThick,
        };

        static constexpr QSize iconPadding{
            iconWidth + 4 * borderSizeThick,
            iconWidth + 4 * borderSizeThick,
        };

        static constexpr QSize buttonSize{72, 32};

        static constexpr QMargins borderThick = {
            borderSizeThick,
            borderSizeThick,
            borderSizeThick,
            borderSizeThick,
        };

        static constexpr QMargins borderThickTrb = {
            0,
            borderSizeThick,
            borderSizeThick,
            borderSizeThick,
        };

        static constexpr QMargins borderThickTr = {
            0,
            borderSizeThick,
            borderSizeThick,
            0,
        };

        static constexpr QMargins borderThickTb = {
            0,
            borderSizeThick,
            0,
            borderSizeThick,
        };

        static constexpr QMargins borderThickLr = {
            borderSizeThick,
            0,
            borderSizeThick,
            0,
        };

        static constexpr QMargins borderThin = {
            borderSizeThin,
            borderSizeThin,
            borderSizeThin,
            borderSizeThin,
        };
    };

}  // namespace Rt2::View
