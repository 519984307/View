#pragma once
#include <QColor>

namespace Rt2::View
{
    namespace C
    {
        constexpr int RedShift   = 0;
        constexpr int GreenShift = 0;
        constexpr int BlueShift  = 0;

        constexpr QColor Grey(const int o)
        {
            return {RedShift + o, GreenShift + o, BlueShift + o, 0xFF};
        }

    }  // namespace C

    class Colors
    {
    public:
        static constexpr QColor Ac00 = {0x54, 0x63, 0xA2, 0xFF};
        static constexpr QColor Ac01 = {0x6b, 0x54, 0xA2, 0xFF};
        static constexpr QColor Ac02 = {0x79, 0x54, 0xA2, 0xFF};
        static constexpr QColor Ac03 = {0x68, 0x54, 0xA2, 0xFF};
        static constexpr QColor Ac04 = {0xA2, 0x54, 0x88, 0xFF};
        static constexpr QColor Ac05 = {0xA2, 0x54, 0x61, 0xFF};
        static constexpr QColor Ac06 = {0xA2, 0x54, 0x54, 0xFF};
        static constexpr QColor Ac07 = {0xA2, 0x63, 0x54, 0xFF};
        static constexpr QColor Ac08 = {0xA2, 0x76, 0x54, 0xFF};
        static constexpr QColor Ac09 = {0xA2, 0x92, 0x54, 0xFF};
        static constexpr QColor Ac10 = {0x9f, 0xA2, 0x54, 0xFF};
        static constexpr QColor Ac11 = {0x86, 0xA2, 0x54, 0xFF};

        static constexpr QColor Empty       = {0xFF, 0x00, 0xFF, 0xFF};
        static constexpr QColor Transparent = {0xFF, 0x00, 0xFF, 0x00};

        static constexpr QColor G00 = C::Grey(0x18);
        static constexpr QColor G01 = C::Grey(0x1d);
        static constexpr QColor G02 = C::Grey(0x2E);
        static constexpr QColor G03 = C::Grey(0x33);
        static constexpr QColor G04 = C::Grey(0x3A);
        static constexpr QColor G05 = C::Grey(0x3F);
        static constexpr QColor G06 = C::Grey(0x48);
        static constexpr QColor G07 = C::Grey(0x5A);
        static constexpr QColor G08 = C::Grey(0x66);
        static constexpr QColor G09 = C::Grey(0x6B);
        static constexpr QColor G10 = C::Grey(0x7B);
        static constexpr QColor G11 = C::Grey(0x93);
        static constexpr QColor G12 = C::Grey(0x98);
        static constexpr QColor G13 = C::Grey(0xA7);

        static constexpr QColor BorderDark          = G01;
        static constexpr QColor Border              = G02;
        static constexpr QColor BorderLight         = G05;
        static constexpr QColor Background          = G02;
        static constexpr QColor CtrlBackground      = G03;
        static constexpr QColor CtrlBackgroundLight = G04;
        static constexpr QColor Foreground          = G12;
    };

}  // namespace Rt2::View
