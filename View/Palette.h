#pragma once
#include <QPalette>

namespace Rt2::View::Palette
{
    class Palette
    {
    public:
        static void applyInternal();

        static void clearPalette(QPalette& palette);
    };

}  // namespace Rt2::View::Palette
