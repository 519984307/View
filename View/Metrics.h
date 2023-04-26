#pragma once
#include <QSize>

namespace Rt2::View
{
    class Metrics
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

        static constexpr QSize minWindow{320, 240};
        static constexpr int   minHeight{24};
        static constexpr int   minWidth{24};
        static constexpr QSize ctrlMin{minWidth, minHeight};

        static constexpr int indent{6};
        static constexpr int scrollbarSize{defaultTextSize};
        static constexpr int borderSizeThick{3};
        static constexpr int borderSizeThin{2};
        static constexpr int borderSizeTiny{1};

        static constexpr int iconFontSize{defaultTextSize + 2};
        static constexpr int iconHeight{iconFontSize};
        static constexpr int iconWidth{iconFontSize};

        static constexpr QSize iconMin{
            iconWidth + 2*borderSizeThick,
            iconWidth +  2*borderSizeThick,
        };

        static constexpr QSize iconPadding{
            iconWidth + 4 * borderSizeThick,
            iconWidth + 4 * borderSizeThick,
        };

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
