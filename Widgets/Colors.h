#pragma once
#include <QColor>

namespace Rt2::Widgets
{
    class Colors
    {
    public:
        static constexpr QColor Empty  = {0xFF, 0x00, 0xFF, 0xFF};
        static constexpr QColor GreyM2 = {0x22, 0x22, 0x22, 0xFF};
        static constexpr QColor GreyM1 = {0x28, 0x28, 0x28, 0xFF};
        static constexpr QColor Grey00 = {0x33, 0x33, 0x33, 0xFF};
        static constexpr QColor Grey01 = {0x39, 0x39, 0x39, 0xFF};
        static constexpr QColor Text00 = {0xA7, 0xA7, 0xA7, 0xFF};
    };

}  // namespace Rt2::Widgets
