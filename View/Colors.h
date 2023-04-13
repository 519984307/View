#pragma once
#include <qpalette.h>
#include <qpen.h>
#include <QColor>

namespace Rt2::View
{
    namespace C
    {
        constexpr int RedShift   = 0x00;
        constexpr int GreenShift = 0x00;
        constexpr int BlueShift  = 0x03;

        constexpr QColor Grey(const int o)
        {
            return {RedShift + o, GreenShift + o, BlueShift + o, 0xFF};
        }

    }  // namespace C

    template <int R = 0x00, int G = 0x00, int B = 0x00>
    struct ConstMix
    {
        static constexpr QColor grey(const int o)
        {
            return {R + o, G + o, B + o, 0xFF};
        }

        static constexpr int term0(const int v, int s, double f)
        {
            return int((1 - f) * double(s + v));
        }

        static constexpr int term1(const int v, int s, double f)
        {
            return int(f * double(s + v));
        }

        static constexpr QColor mix(const int    a,
                                    const int    r,
                                    const int    g,
                                    const int    b,
                                    const double fac)
        {
            return {
                term0(a, R, fac) + term1(r, R, fac),
                term0(a, G, fac) + term1(g, G, fac),
                term0(a, B, fac) + term1(b, B, fac),
                0xFF,
            };
        }

    };  // namespace ConstMix

    using BlueMix = ConstMix<0x00,0x00,0x03>;



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

        static constexpr QColor G00 = BlueMix::grey(0x18);
        static constexpr QColor G01 = BlueMix::grey(0x1d);
        static constexpr QColor G02 = BlueMix::grey(0x2E);
        static constexpr QColor G03 = BlueMix::grey(0x33);
        static constexpr QColor G04 = BlueMix::grey(0x3A);
        static constexpr QColor G05 = BlueMix::grey(0x3F);
        static constexpr QColor G06 = BlueMix::grey(0x48);
        static constexpr QColor G07 = BlueMix::grey(0x5A);
        static constexpr QColor G08 = BlueMix::grey(0x66);
        static constexpr QColor G09 = BlueMix::grey(0x6B);
        static constexpr QColor G10 = BlueMix::grey(0x7B);
        static constexpr QColor G11 = BlueMix::grey(0x93);
        static constexpr QColor G12 = BlueMix::grey(0x98);
        static constexpr QColor G13 = BlueMix::grey(0xA7);
        static constexpr QColor G14 = BlueMix::grey(0xD7);

        static constexpr QColor BorderDark          = G01;
        static constexpr QColor Border              = G02;
        static constexpr QColor BorderLight         = G05;
        static constexpr QColor Background          = G02;
        static constexpr QColor CtrlBackground      = G03;
        static constexpr QColor CtrlBackgroundLight = G04;
        static constexpr QColor Foreground          = G13;
        static constexpr QColor ForegroundLight     = G14;

        static constexpr QPalette::ColorRole CustomViewBackground = QPalette::ColorRole::ToolTipBase;
        static constexpr QPalette::ColorRole CustomViewBorder     = QPalette::ColorRole::ToolTipText;

        static constexpr QPalette::ColorRole Extra0 = QPalette::ColorRole::Link;
        static constexpr QPalette::ColorRole Extra1 = QPalette::ColorRole::LinkVisited;
        static constexpr QPalette::ColorRole Extra2 = QPalette::ColorRole::PlaceholderText;
    };

}  // namespace Rt2::View
