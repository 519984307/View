#pragma once
#include <QSize>

namespace Rt2::Widgets
{
    class Metrics
    {
    public:
        static constexpr QSize minWindow{320, 240};
        static constexpr int   minHeight{24};
        static constexpr int   minWidth{24};
        static constexpr int   iconHeight{18};
        static constexpr int   iconWidth{18};
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
    };

}  // namespace Rt2::Qt
