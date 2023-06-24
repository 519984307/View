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

#define RT_CONST static constexpr

namespace Rt2::View
{
    namespace Mix
    {
        namespace Mixer
        {
            struct Rgb
            {
                int r, g, b, a;
            };

            namespace D
            {
                RT_CONST int Mi(const int a,
                                const int b)
                {
                    return a < b ? a : b;
                }

                RT_CONST int Ma(const int a,
                                const int b)
                {
                    return a > b ? a : b;
                }

                RT_CONST int Cl(const int v,
                                const int a,
                                const int b)
                {
                    return Mi(Ma(v, a), b);
                }

                RT_CONST int T0(const int    v,
                                const int    s,
                                const double f)
                {
                    return int((1 - f) * double(s + v));
                }

                RT_CONST int T1(const int    v,
                                const int    s,
                                const double f)
                {
                    return int(f * double(s + v));
                }

                RT_CONST int Sh(const int n,
                                const int a,
                                const int b)
                {
                    return n * b + a;
                }

            }  // namespace D

            template <int R = 0x00, int G = 0x00, int B = 0x00>
            class MixRgb
            {
            public:
                RT_CONST Rgb grey(const int o)
                {
                    return {D::Cl(R + o, 0x00, 0xFF),
                            D::Cl(G + o, 0x00, 0xFF),
                            D::Cl(B + o, 0x00, 0xFF),
                            0xFF};
                }

                RT_CONST Rgb mix(const int    a,
                                 const int    r,
                                 const int    g,
                                 const int    b,
                                 const double f)
                {
                    return {
                        D::Cl(D::T0(a, R, f) + D::T1(r, R, f), 0x00, 0xFF),
                        D::Cl(D::T0(a, G, f) + D::T1(g, G, f), 0x00, 0xFF),
                        D::Cl(D::T0(a, B, f) + D::T1(b, B, f), 0x00, 0xFF),
                        0xFF,
                    };
                }

                RT_CONST Rgb mix(const Rgb    a,
                                 const Rgb    b,
                                 const double f)
                {
                    return {
                        D::Cl(D::T0(a.r, R, f) + D::T1(b.r, R, f), 0x00, 0xFF),
                        D::Cl(D::T0(a.g, G, f) + D::T1(b.g, G, f), 0x00, 0xFF),
                        D::Cl(D::T0(a.b, B, f) + D::T1(b.b, B, f), 0x00, 0xFF),
                        0xFF,
                    };
                }

                RT_CONST QColor qMix(const int    a,
                                     const int    r,
                                     const int    g,
                                     const int    b,
                                     const double fac)
                {
                    return {
                        D::T0(a, R, fac) + D::T1(r, R, fac),
                        D::T0(a, G, fac) + D::T1(g, G, fac),
                        D::T0(a, B, fac) + D::T1(b, B, fac),
                        0xFF,
                    };
                }
            };

            namespace QtMix
            {

                RT_CONST QColor to(const Rgb c)
                {
                    return {c.r, c.g, c.b, c.a};
                }

                static QColor mix(const Rgb& c, const QColor& b, const double fac)
                {
                    return to(MixRgb<0, 0, 0>::mix(c, {b.red(), b.green(), b.blue(), 0xFF}, fac));
                }

            }  // namespace QtMix

            template <int R, int G, int B, int S, int O = 0x00>
            class Swatch
            {
            private:
                using M = MixRgb<R, G, B>;

            public:
                RT_CONST Rgb Value[7] = {
                    M::grey(D::Sh(0, O, S)),
                    M::grey(D::Sh(1, O, S)),
                    M::grey(D::Sh(2, O, S)),
                    M::grey(D::Sh(3, O, S)),
                    M::grey(D::Sh(4, O, S)),
                    M::grey(D::Sh(5, O, S)),
                    M::grey(D::Sh(6, O, S)),
                };
            };

            template <typename A, typename B, int N = 1, int D = 2>
            class MixSwatch
            {
            private:
                using M = MixRgb<0, 0, 0>;

                RT_CONST double Fraction = double(N) / double(D);

            public:
                RT_CONST Rgb Value[7] = {
                    M::mix(A::Value[0], B::Value[0], Fraction),
                    M::mix(A::Value[1], B::Value[1], Fraction),
                    M::mix(A::Value[2], B::Value[2], Fraction),
                    M::mix(A::Value[3], B::Value[3], Fraction),
                    M::mix(A::Value[4], B::Value[4], Fraction),
                    M::mix(A::Value[5], B::Value[5], Fraction),
                    M::mix(A::Value[6], B::Value[6], Fraction),
                };
            };

            template <typename A, typename B>
            class BlendSwatch
            {
            private:
                using M = MixRgb<0, 0, 0>;

            public:
                RT_CONST Rgb Value[7] = {
                    M::mix(A::Value[0], B::Value[0], 1.0 / 8.0),
                    M::mix(A::Value[1], B::Value[1], 2.0 / 8.0),
                    M::mix(A::Value[2], B::Value[2], 3.0 / 8.0),
                    M::mix(A::Value[3], B::Value[3], 4.0 / 8.0),
                    M::mix(A::Value[4], B::Value[4], 5.0 / 8.0),
                    M::mix(A::Value[5], B::Value[5], 6.0 / 8.0),
                    M::mix(A::Value[6], B::Value[6], 7.0 / 8.0),
                };
            };

            template <int Min = 0x00, int Max = 0xFF>
            class Swatches
            {
            private:
                RT_CONST int L0 = Min;
                RT_CONST int L1 = Min + (Max - Min) / 2;
                RT_CONST int L2 = Max;
                RT_CONST int S  = (Max - Min) / 7;
                RT_CONST int O  = Min;

            public:
                using Red      = Swatch<L2, L0, L0, S, O>;
                using Orange   = Swatch<L2, L1, L0, S, O>;
                using Yellow   = Swatch<L2, L2, L0, S, O>;
                using Green    = Swatch<L0, L2, L0, S, O>;
                using Blue     = Swatch<L0, L0, L2, S, O>;
                using Cyan     = Swatch<L0, L2, L2, S, O>;
                using Magenta  = Swatch<L2, L0, L2, S, O>;
                using Violet   = Swatch<L1, L0, L2, S, O>;
                using Black    = Swatch<0, 0, 0, S, O>;
                using LowGrey  = Swatch<L0, L0, L0, S, O>;
                using MidGrey  = Swatch<L1, L1, L1, S, O>;
                using HighGrey = Swatch<L2, L2, L2, S, O>;
            };
        }  // namespace Mixer

        template <typename Swatch>
        class QSwatch
        {
        public:
            RT_CONST QColor Values[7] = {
                Mixer::QtMix::to(Swatch::Value[0]),
                Mixer::QtMix::to(Swatch::Value[1]),
                Mixer::QtMix::to(Swatch::Value[2]),
                Mixer::QtMix::to(Swatch::Value[3]),
                Mixer::QtMix::to(Swatch::Value[4]),
                Mixer::QtMix::to(Swatch::Value[5]),
                Mixer::QtMix::to(Swatch::Value[6]),
            };
            RT_CONST QColor Qs0 = Mixer::QtMix::to(Swatch::Value[0]);
            RT_CONST QColor Qs1 = Mixer::QtMix::to(Swatch::Value[1]);
            RT_CONST QColor Qs2 = Mixer::QtMix::to(Swatch::Value[2]);
            RT_CONST QColor Qs3 = Mixer::QtMix::to(Swatch::Value[3]);
            RT_CONST QColor Qs4 = Mixer::QtMix::to(Swatch::Value[4]);
            RT_CONST QColor Qs5 = Mixer::QtMix::to(Swatch::Value[5]);
            RT_CONST QColor Qs6 = Mixer::QtMix::to(Swatch::Value[6]);
        };

        template <typename A, typename B>
        class QBlendSwatch
        {
        public:
            using Qb05 = QSwatch<Mixer::MixSwatch<A, B, 5, 100>>;
            using Qb10 = QSwatch<Mixer::MixSwatch<A, B, 10, 100>>;
            using Qb15 = QSwatch<Mixer::MixSwatch<A, B, 15, 100>>;
            using Qb20 = QSwatch<Mixer::MixSwatch<A, B, 20, 100>>;
            using Qb25 = QSwatch<Mixer::MixSwatch<A, B, 25, 100>>;
            using Qb30 = QSwatch<Mixer::MixSwatch<A, B, 30, 100>>;
            using Qb35 = QSwatch<Mixer::MixSwatch<A, B, 35, 100>>;
            using Qb40 = QSwatch<Mixer::MixSwatch<A, B, 40, 100>>;
            using Qb45 = QSwatch<Mixer::MixSwatch<A, B, 45, 100>>;
            using Qb50 = QSwatch<Mixer::MixSwatch<A, B, 50, 100>>;
            using Qb55 = QSwatch<Mixer::MixSwatch<A, B, 55, 100>>;
            using Qb60 = QSwatch<Mixer::MixSwatch<A, B, 60, 100>>;
            using Qb65 = QSwatch<Mixer::MixSwatch<A, B, 65, 100>>;
            using Qb70 = QSwatch<Mixer::MixSwatch<A, B, 70, 100>>;
            using Qb75 = QSwatch<Mixer::MixSwatch<A, B, 75, 100>>;
            using Qb80 = QSwatch<Mixer::MixSwatch<A, B, 80, 100>>;
            using Qb85 = QSwatch<Mixer::MixSwatch<A, B, 85, 100>>;
            using Qb90 = QSwatch<Mixer::MixSwatch<A, B, 90, 100>>;
            using Qb95 = QSwatch<Mixer::MixSwatch<A, B, 95, 100>>;
        };
        namespace Swatches
        {
            using Base = Mixer::Swatches<16, 128>;

            namespace Values
            {
                using LowGrey  = QSwatch<Base::LowGrey>;
                using MidGrey  = QSwatch<Base::MidGrey>;
                using HighGrey = QSwatch<Base::HighGrey>;
            }  // namespace Values

            namespace Primary
            {
                using Red    = QSwatch<Base::Red>;
                using Yellow = QSwatch<Base::Yellow>;
                using Blue   = QSwatch<Base::Blue>;
            }  // namespace Primary

            namespace Secondary
            {
                using Orange = QSwatch<Base::Orange>;
                using Green  = QSwatch<Base::Green>;
                using Violet = QSwatch<Base::Violet>;
            }  // namespace Secondary

            namespace Tertiary
            {
                using RedOrange    = QSwatch<Mixer::MixSwatch<Base::Red, Base::Orange>>;
                using YellowOrange = QSwatch<Mixer::MixSwatch<Base::Yellow, Base::Orange>>;
                using YellowGreen  = QSwatch<Mixer::MixSwatch<Base::Yellow, Base::Green>>;
                using BlueGreen    = QSwatch<Base::Cyan>;
                using BlueViolet   = QSwatch<Mixer::MixSwatch<Base::Blue, Base::Violet>>;
                using RedViolet    = QSwatch<Mixer::MixSwatch<Base::Red, Base::Magenta>>;
            }  // namespace Tertiary

            namespace All
            {
                using Red          = Primary::Red;
                using RedOrange    = Tertiary::RedOrange;
                using Orange       = Secondary::Orange;
                using YellowOrange = Tertiary::YellowOrange;
                using Yellow       = Primary::Yellow;
                using YellowGreen  = Tertiary::YellowGreen;
                using Green        = Secondary::Green;
                using BlueGreen    = Tertiary::BlueGreen;
                using Blue         = Primary::Blue;
                using BlueViolet   = Tertiary::BlueViolet;
                using Violet       = Secondary::Violet;
                using RedViolet    = Tertiary::RedViolet;

            }  // namespace All

        }  // namespace Swatches

        namespace Palette
        {
            using Base = Swatches::Base;

            namespace Mixed
            {
                using Rm50     = Mixer::MixSwatch<Base::Red, Base::Magenta, 25, 100>;
                using Yg50     = Mixer::MixSwatch<Base::Yellow, Base::Green>;
                using OHg90    = Mixer::MixSwatch<Base::Orange, Base::HighGrey, 90, 100>;
                using BHg90    = Mixer::MixSwatch<Base::Blue, Base::HighGrey, 90, 100>;
                using DarkGrey = Mixer::MixSwatch<Base::Blue, Base::Black, 95, 100>;
                using LowGrey  = Mixer::MixSwatch<Base::Blue, Base::LowGrey, 95, 100>;
                using MidGrey  = Mixer::MixSwatch<Base::Blue, Base::MidGrey, 95, 100>;
                using HighGrey = Mixer::MixSwatch<Base::Blue, Base::HighGrey, 95, 100>;

                using Bhg90Ohg9050 = Mixer::MixSwatch<BHg90, OHg90, 50, 100>;

            }  // namespace Mixed

            using DarkGrey      = QSwatch<Mixed::DarkGrey>;
            using LowGrey       = QSwatch<Mixed::LowGrey>;
            using MidGrey       = QSwatch<Mixed::MidGrey>;
            using HighGrey      = QSwatch<Mixed::HighGrey>;
            using HighBlueGrey  = QSwatch<Mixed::BHg90>;
            using ControlBlend  = QBlendSwatch<Mixed::DarkGrey, Mixed::HighGrey>;
            using Control0      = QSwatch<Mixed::DarkGrey>;
            using Control1      = QSwatch<Mixed::LowGrey>;
            using Primary       = QSwatch<Base::Blue>;
            using Secondary     = QSwatch<Mixed::Yg50>;
            using PrimaryBlend  = QBlendSwatch<Base::Blue, Mixed::Yg50>;
            using PrimaryGrey   = QBlendSwatch<Base::Blue, Mixed::MidGrey>;
            using SecondaryGrey = QBlendSwatch<Mixed::Yg50, Mixed::MidGrey>;
            using Error         = QSwatch<Mixed::Rm50>;
            using ErrorGrey     = QBlendSwatch<Mixed::Rm50, Mixed::LowGrey>;
            using Text          = QSwatch<Mixed::Bhg90Ohg9050>;

        }  // namespace Palette

    }  // namespace Mix

}  // namespace Rt2::View
