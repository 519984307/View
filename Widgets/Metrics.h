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
        static constexpr int   iconHeight{24};
        static constexpr int   iconWidth{24};
        static constexpr int   iconFontSize{iconWidth>>1};
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
        static constexpr int   bl{4};
        static constexpr int   bs{1};

        static constexpr QMargins BorderThick    = {bl, bl, bl, bl};
        static constexpr QMargins BorderThickTrb = {0, bl, bl, bl};
        static constexpr QMargins BorderThickTr  = {0, bl, bl, 0};
        static constexpr QMargins BorderThickTb  = {0, bl, 0, bl};
        static constexpr QMargins BorderThin     = {bs, bs, bs, bs};
    };

}  // namespace Rt2::Widgets
