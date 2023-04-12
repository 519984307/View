#include "View/Palette.h"
#include <QApplication>
#include <QWidget>

namespace Rt2::View::Palette
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
}  // namespace Rt2::View::Palette
