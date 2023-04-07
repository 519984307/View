#pragma once
#include <QColor>

namespace Rt2::Qt
{
    class Colors
    {
    public:
        static constexpr QColor Empty = {0xFF, 0x00, 0xFF, 0xFF};
        static constexpr QColor Dark  = {0x33, 0x33, 0x33, 0xFF};
    };

}  // namespace Rt2::Qt
