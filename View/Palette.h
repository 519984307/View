#pragma once
#include <QPalette>

namespace Rt2::View
{
    class Palette
    {
    public:
        static void applyInternal();

        static void clearPalette(QPalette& palette);

        static void applyCtrlPalette(QWidget *widget);
    };

}  // namespace Rt2::View
