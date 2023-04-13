#include "View/Palette.h"
#include <QApplication>
#include <QWidget>
#include "Colors.h"

namespace Rt2::View
{
    constexpr QPalette::ColorRole RoleOrder[20] = {
        QPalette::Shadow,
        QPalette::Dark,
        QPalette::Base,
        QPalette::Mid,
        QPalette::Midlight,
        QPalette::Light,
        QPalette::Highlight,
        QPalette::Window,
        QPalette::WindowText,
        QPalette::Button,
        QPalette::ButtonText,
        QPalette::ToolTipBase,
        QPalette::ToolTipText,
        QPalette::Text,
        QPalette::BrightText,
        QPalette::HighlightedText,
        QPalette::Link,
        QPalette::LinkVisited,
        QPalette::AlternateBase,
        QPalette::PlaceholderText,
    };

    void clearAppPalette(QPalette& palette)
    {
        // For all groups and all colors that belong
        // to that group, set the color's value to the
        // pre-determined Empty color.
        // (this helps weed out any unknowns)

        int groups[]{
            QPalette::ColorGroup::Active,
            QPalette::ColorGroup::Disabled,
            QPalette::ColorGroup::Inactive,
            QPalette::ColorGroup::Current,
            QPalette::ColorGroup::All,
            QPalette::ColorGroup::Normal,
        };

        int colors[] = {
            QPalette::WindowText,
            QPalette::Button,
            QPalette::Light,
            QPalette::Midlight,
            QPalette::Dark,
            QPalette::Mid,
            QPalette::Text,
            QPalette::BrightText,
            QPalette::ButtonText,
            QPalette::Base,
            QPalette::Window,
            QPalette::Shadow,
            QPalette::Highlight,
            QPalette::HighlightedText,
            QPalette::Link,
            QPalette::LinkVisited,
            QPalette::AlternateBase,
            QPalette::NoRole,
            QPalette::ToolTipBase,
            QPalette::ToolTipText,
            QPalette::PlaceholderText,
        };

        for (int group : groups)
        {
            for (int color : colors)
            {
                palette.setColor((QPalette::ColorGroup)group,
                                 (QPalette::ColorRole)color,
                                 {0xFF, 0x00, 0xFF});
            }
        }
    }

    void Palette::applyInternal()
    {
        QPalette palette;
        clearAppPalette(palette);
        QGuiApplication::setPalette(palette);
    }

    void Palette::clearPalette(QPalette& palette)
    {
        clearAppPalette(palette);
    }

    void Palette::applyCtrlPalette(QWidget* widget)
    {
        if (!widget)
            return;

        QPalette pal = widget->palette();
        clearPalette(pal);

        constexpr QColor currentColors[20] = {
            Colors::G00,                  // Shadow
            Colors::G01,                  // Dark
            Colors::Background,           // Base
            Colors::G02,                  // Mid
            Colors::G03,                  // Midlight
            Colors::G04,                  // Light
            Colors::Empty,                // Highlight
            Colors::Background,           // Window
            Colors::Foreground,           // WindowText
            Colors::CtrlBackground,       // Button
            Colors::ForegroundLight,      // ButtonText
            Colors::CtrlBackgroundLight,  // ToolTipBase -> CustomView.Border
            Colors::CtrlBackground,       // ToolTipText -> CustomView.Background
            Colors::Foreground,           // Text
            Colors::ForegroundLight,      // BrightText
            Colors::ForegroundLight,      // HighlightedText
            Colors::BorderDark,           // Link             -> Extra0
            Colors::Border,               // LinkVisited      -> Extra1
            Colors::Ac11,                 // AlternateBase
            Colors::CtrlBackgroundLight,  // PlaceholderText  -> Extra2
        };

        for (size_t i = 0; i < std::size(currentColors); ++i)
            pal.setColor(RoleOrder[i], currentColors[i]);

        widget->setPalette(pal);
    }

}  // namespace Rt2::View