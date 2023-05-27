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
#include <QColor>
#include <QPalette>
#include <QPen>

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

    using BlueMix   = ConstMix<0x00, 0x00, 0x03>;
    using GreenMix  = ConstMix<0x00, 0x03, 0x00>;
    using OrangeMix = ConstMix<0x03, 0x01, 0x00>;

    class Colors  // should be serialized
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

        static constexpr QColor G00 = BlueMix::grey(0x02);
        static constexpr QColor G01 = BlueMix::grey(0x0F);
        static constexpr QColor G02 = BlueMix::grey(0x1E);
        static constexpr QColor G03 = BlueMix::grey(0x22);
        static constexpr QColor G04 = BlueMix::grey(0x2A);
        static constexpr QColor G05 = OrangeMix::grey(0x2F);
        static constexpr QColor G06 = OrangeMix::grey(0x38);
        static constexpr QColor G07 = OrangeMix::grey(0x4A);
        static constexpr QColor G08 = OrangeMix::grey(0x56);
        static constexpr QColor G09 = OrangeMix::grey(0x5B);
        static constexpr QColor G10 = OrangeMix::grey(0x6B);
        static constexpr QColor G11 = OrangeMix::grey(0x83);
        static constexpr QColor G12 = OrangeMix::grey(0x88);
        static constexpr QColor G13 = OrangeMix::grey(0x97);
        static constexpr QColor G14 = OrangeMix::grey(0xC7);

        static constexpr QColor BorderDark          = G00;
        static constexpr QColor Border              = G01;
        static constexpr QColor BorderLight         = G02;
        static constexpr QColor Background          = G03;
        static constexpr QColor CtrlBackground      = G03;
        static constexpr QColor CtrlBackgroundLight = G04;
        static constexpr QColor Foreground          = G13;
        static constexpr QColor ForegroundLight     = G14;
        static constexpr QColor Accent              = OrangeMix::mix(0x38, 0x54, 0x63, 0xA2, 0.7);

        static constexpr int Drk100 = 300;
        static constexpr int Drk090 = 280;
        static constexpr int Drk080 = 260;
        static constexpr int Drk070 = 240;
        static constexpr int Drk060 = 220;
        static constexpr int Drk050 = 200;
        static constexpr int Drk040 = 180;
        static constexpr int Drk030 = 160;
        static constexpr int Drk020 = 140;
        static constexpr int Drk010 = 120;
        static constexpr int Drk000 = 100;

        static constexpr int Lgt100 = 200;
        static constexpr int Lgt090 = 190;
        static constexpr int Lgt080 = 180;
        static constexpr int Lgt070 = 170;
        static constexpr int Lgt060 = 160;
        static constexpr int Lgt050 = 150;
        static constexpr int Lgt040 = 140;
        static constexpr int Lgt030 = 130;
        static constexpr int Lgt020 = 120;
        static constexpr int Lgt010 = 110;
        static constexpr int Lgt000 = 100;

        static constexpr QPalette::ColorRole CustomViewBackground = QPalette::ColorRole::ToolTipBase;
        static constexpr QPalette::ColorRole CustomViewBorder     = QPalette::ColorRole::ToolTipText;

        static constexpr QPalette::ColorRole Extra0 = QPalette::ColorRole::Link;
        static constexpr QPalette::ColorRole Extra1 = QPalette::ColorRole::LinkVisited;
        static constexpr QPalette::ColorRole Extra2 = QPalette::ColorRole::PlaceholderText;

        static constexpr QColor Emphasis[6] = {
            BlueMix::grey(0x2F),
            BlueMix::grey(0x44),
            BlueMix::grey(0x66),
            OrangeMix::grey(0x88),
            OrangeMix::grey(0xA7),
            OrangeMix::grey(0xC7),
        };
    };

}  // namespace Rt2::View
