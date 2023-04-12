#pragma once
#include <QSize>

namespace Rt2::View
{
    class Metrics
    {
    public:
        static constexpr QSize minWindow{320, 240};
        static constexpr int   minHeight{24};
        static constexpr int   minWidth{24};
        static constexpr int   iconHeight{32};
        static constexpr int   iconWidth{32};
        static constexpr int   iconFontSize{iconWidth >> 1};
        static constexpr int   indent{6};
        static constexpr QSize ctrlMin{minWidth, minHeight};
        static constexpr QSize iconMin{iconWidth, iconWidth};
        static constexpr int   ts{10};
        static constexpr int   gm{0};
        static constexpr int   gs{0};
        static constexpr int   h1{28};
        static constexpr int   h2{24};
        static constexpr int   h3{20};
        static constexpr int   h4{18};
        static constexpr int   h5{16};
        static constexpr int   h6{15};
        static constexpr int   borderSizeThick{3};
        static constexpr int   borderSizeThin{2};

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
