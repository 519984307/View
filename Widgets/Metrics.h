#pragma once
#include <QSize>

namespace Rt2::Qt
{
    class Metrics
    {
    public:
        static constexpr QSize mw{320, 240};
        static constexpr int   mch = 24;
        static constexpr int   mcw = 24;
        static constexpr QSize cm{mcw, mch};
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
