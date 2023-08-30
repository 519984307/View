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
#include <QWidget>
#include "View/ColorMix.h"
#include "View/Definitions.h"
#include "View/IconFontMapping.h"
#include "View/StyleForwards.h"

namespace Rt2::View::Style
{
    namespace Palette
    {
        using Base         = Mix::Palette::Base;
        using DarkGrey     = Mix::Palette::DarkGrey;
        using LowGrey      = Mix::Palette::LowGrey;
        using MidGrey      = Mix::Palette::MidGrey;
        using HighGrey     = Mix::Palette::HighGrey;
        using HighBlueGrey = Mix::Palette::HighBlueGrey;
        using ControlBlend = Mix::Palette::ControlBlend;  // rename to control

        using Control0 = Mix::Palette::Control0;  // use ctrl blend
        using Control1 = Mix::Palette::Control1;  // use ctrl blend

        using Primary   = Mix::Palette::Primary;
        using Secondary = Mix::Palette::Secondary;

        using PrimaryBlend = Mix::Palette::PrimaryBlend;  // Primary ->  Secondary

        using PrimaryGrey   = Mix::Palette::PrimaryGrey;
        using SecondaryGrey = Mix::Palette::SecondaryGrey;
        using Error         = Mix::Palette::Error;
        using ErrorGrey     = Mix::Palette::ErrorGrey;

        using Text = Mix::Palette::Text;
    }  // namespace Palette

    namespace Points
    {
        constexpr int Pt01{1};
        constexpr int Pt02{2};
        constexpr int Pt03{3};
        constexpr int Pt04{4};
        constexpr int Pt05{5};
        constexpr int Pt06{6};
        constexpr int Pt08{8};
        constexpr int Pt10{10};
        constexpr int Pt12{12};
        constexpr int Pt14{14};
        constexpr int Pt16{16};
        constexpr int Pt18{18};
        constexpr int Pt20{20};
        constexpr int Pt22{22};
        constexpr int Pt24{24};
        constexpr int Pt28{28};
        constexpr int Pt32{32};
        constexpr int Pt64{64};
        constexpr int Pt72{72};
        constexpr int Pt96{96};
    }  // namespace Points

    namespace FontSize
    {
        constexpr int Heading1 = Points::Pt24;
        constexpr int Heading2 = Points::Pt22;
        constexpr int Heading3 = Points::Pt18;
        constexpr int Heading4 = Points::Pt16;
        constexpr int Heading5 = Points::Pt14;
        constexpr int Heading6 = Points::Pt12;

        constexpr int Tiny   = Points::Pt06;
        constexpr int Small  = Points::Pt08;
        constexpr int Normal = Points::Pt10;
        constexpr int Medium = Points::Pt12;
        constexpr int Large  = Points::Pt14;
        constexpr int XLarge = Points::Pt16;

    }  // namespace FontSize

    namespace Fonts
    {
        constexpr const char* IconFamily       = "ViewIcon";
        constexpr const char* FixedWidthFamily = "JetBrains Mono Thin";
        constexpr const char* DefaultFamily    = "Segoe UI";

    }  // namespace Fonts

    namespace Icon
    {
        constexpr int   Small   = Points::Pt10;
        constexpr int   Normal  = Points::Pt14;
        constexpr int   Large   = Points::Pt18;
        constexpr int   XLarge  = Points::Pt24;
        constexpr int   XxLarge = Points::Pt32;
        constexpr QSize Size    = {Points::Pt16, Points::Pt16};

        constexpr int   BoundingHeight = Points::Pt18;
        constexpr int   BoundingWidth  = Points::Pt18;
        constexpr QSize Bounds         = {BoundingWidth, BoundingHeight};

        constexpr int FirstIcon = IconsStart + 1;
        constexpr int LastIcon  = IconsEnd - 1;
        constexpr int Count     = LastIcon - FirstIcon;

    }  // namespace Icon

    namespace Size
    {
        constexpr int None    = 0;
        constexpr int Tiny    = Points::Pt01;
        constexpr int Small   = Points::Pt03;
        constexpr int Medium  = Points::Pt06;
        constexpr int Normal  = Medium;
        constexpr int Large   = Points::Pt08;
        constexpr int XLarge  = Points::Pt16;
        constexpr int XxLarge = Points::Pt24;

        constexpr QSize Button = {3 * Points::Pt24, Points::Pt32};

    }  // namespace Size

    namespace Spacing
    {
        constexpr int None    = Size::None;
        constexpr int Tiny    = Size::Tiny;
        constexpr int Small   = Size::Small;
        constexpr int Medium  = Size::Medium;
        constexpr int Normal  = Size::Normal;
        constexpr int Large   = Size::Large;
        constexpr int XLarge  = Size::XLarge;
        constexpr int XxLarge = Size::XxLarge;

    }  // namespace Spacing

    namespace Margin
    {
        constexpr QMargins None    = {Size::None, Size::None, Size::None, Size::None};
        constexpr QMargins Tiny    = {Size::Tiny, Size::Tiny, Size::Tiny, Size::Tiny};
        constexpr QMargins Small   = {Size::Small, Size::Small, Size::Small, Size::Small};
        constexpr QMargins Medium  = {Size::Medium, Size::Medium, Size::Medium, Size::Medium};
        constexpr QMargins Large   = {Size::Large, Size::Large, Size::Large, Size::Large};
        constexpr QMargins XLarge  = {Size::XLarge, Size::XLarge, Size::XLarge, Size::XLarge};
        constexpr QMargins XxLarge = {Size::XxLarge, Size::XxLarge, Size::XxLarge, Size::XxLarge};

    }  // namespace Margin

    namespace Window
    {
        using Swatches = Palette::ControlBlend;

        constexpr QColor Dark                = Palette::Control0::Qs0;
        constexpr QColor Background          = Swatches::Qb05::Qs0;
        constexpr QColor BackgroundMedium    = Swatches::Qb10::Qs0;
        constexpr QColor BackgroundLight     = Swatches::Qb15::Qs0;
        constexpr QColor BackgroundHighLight = Swatches::Qb15::Qs1;
        constexpr QColor CtrlBackground      = BackgroundLight;
        constexpr QColor Separator           = Background;
        constexpr QColor ForegroundDark      = Swatches::Qb90::Qs0;
        constexpr QColor Foreground          = Swatches::Qb90::Qs3;
        constexpr QColor ForegroundLight     = Swatches::Qb90::Qs5;
        constexpr QColor Border              = Separator;
        constexpr QColor AccentDark          = Palette::PrimaryGrey::Qb10::Qs0;
        constexpr QColor Accent              = Palette::PrimaryGrey::Qb15::Qs1;
        constexpr QColor AccentLight         = Palette::PrimaryGrey::Qb20::Qs2;
        constexpr int    BaseHeight          = Points::Pt24;
        constexpr int    BaseWidth           = Points::Pt24 << 3;
        constexpr int    FontSize            = Points::Pt10;
        constexpr int    BorderSize          = Points::Pt01;
        constexpr int    SplitterSize        = Points::Pt03;
        constexpr QSize  Small               = {320, 240};
        constexpr QSize  Medium              = {640, 480};
        constexpr QSize  Large               = {800, 600};
        constexpr QSize  XLarge              = {1024, 768};
        constexpr QSize  Panel               = {BaseWidth, BaseHeight};

    }  // namespace Window

    namespace Menu
    {
        constexpr int MinWidth = Window::BaseWidth;

    }  // namespace Menu

    namespace TabBar
    {
        constexpr QColor   Background = Window::Swatches::Qb05::Qs0;
        constexpr QColor   Accent     = Window::Accent;
        constexpr QColor   Tab        = Background;
        constexpr QColor   Pane       = Background;
        constexpr int      BaseHeight = Points::Pt24;
        constexpr int      BaseWidth  = Points::Pt12 << 2;
        constexpr QMargins Padding    = Margin::Small;
        constexpr QSize    Size       = {Size::Small + BaseWidth, Size::Small + BaseHeight};
        constexpr int      FontSize   = Points::Pt14;
        constexpr int      BorderSize = Points::Pt03;
    }  // namespace TabBar

    namespace ScrollBar
    {
        constexpr QColor Background   = Window::Swatches::Qb05::Qs1;
        constexpr QColor Border       = Window::Swatches::Qb05::Qs2;
        constexpr QColor Handle       = Window::Swatches::Qb05::Qs2;
        constexpr QColor HandleBorder = Window::Swatches::Qb05::Qs3;
        constexpr int    BorderSize   = Size::Tiny;
        constexpr int    HandleSize   = Points::Pt10;
        constexpr int    HandleMargin = Points::Pt01;
        constexpr int    Padding      = 0;

        constexpr int Size = HandleSize + HandleMargin + Padding;
    }  // namespace ScrollBar

    namespace ListView
    {
        constexpr QColor Background     = Window::Background;
        constexpr QColor Accent         = Window::Accent;
        constexpr QColor Item           = Window::Background;
        constexpr QColor Alternate      = Window::BackgroundLight;
        constexpr QColor Selection      = Accent;
        constexpr QColor Hover          = Accent;
        constexpr QColor Foreground     = Window::Foreground;
        constexpr QColor ForegroundDark = Window::ForegroundDark;

    }  // namespace ListView

    namespace Normal
    {
        constexpr QColor Border        = Window::Swatches::Qb10::Qs1;
        constexpr QColor BorderLight   = Window::Swatches::Qb05::Qs2;
        constexpr QColor Background    = Window::Swatches::Qb05::Qs0;
        constexpr QColor Foreground    = Palette::Text::Qs3;
        constexpr QColor Highlight     = Palette::PrimaryBlend::Qb20::Qs2;
        constexpr QColor HighlightText = Palette::ControlBlend::Qb90::Qs5;
        constexpr int    BorderSize    = Size::Tiny;
    }  // namespace Normal

    namespace Hover
    {
        constexpr QColor Border        = Normal::BorderLight;
        constexpr QColor BorderLight   = Window::Swatches::Qb05::Qs3;
        constexpr QColor Background    = Window::Swatches::Qb10::Qs0;
        constexpr QColor Foreground    = Palette::Text::Qs4;
        constexpr QColor Highlight     = Palette::PrimaryBlend::Qb20::Qs2;
        constexpr QColor HighlightText = Palette::ControlBlend::Qb90::Qs5;
        constexpr int    BorderSize    = Size::Tiny;
    }  // namespace Hover

    namespace Pressed
    {
        constexpr QColor Border        = Palette::PrimaryGrey::Qb20::Qs3;
        constexpr QColor BorderLight   = Palette::PrimaryGrey::Qb25::Qs4;
        constexpr QColor Background    = Palette::PrimaryBlend::Qb20::Qs1;
        constexpr QColor Foreground    = Palette::Text::Qs5;
        constexpr QColor Highlight     = Palette::PrimaryBlend::Qb20::Qs2;
        constexpr QColor HighlightText = Palette::ControlBlend::Qb90::Qs5;
        constexpr int    BorderSize    = Size::Tiny;
    }  // namespace Pressed

    namespace PressedPrimary
    {
        constexpr QColor Border        = Palette::PrimaryBlend::Qb05::Qs3;
        constexpr QColor BorderLight   = Palette::PrimaryBlend::Qb05::Qs6;
        constexpr QColor Background    = Palette::PrimaryBlend::Qb10::Qs1;
        constexpr QColor Highlight     = Palette::PrimaryBlend::Qb20::Qs3;
        constexpr QColor HighlightText = Palette::PrimaryBlend::Qb20::Qs6;
        constexpr QColor Foreground    = Palette::PrimaryGrey::Qb90::Qs4;
        constexpr int    BorderSize    = Pressed::BorderSize;
    }  // namespace PressedPrimary

    namespace PressedSecondary
    {
        constexpr QColor Border        = Palette::PrimaryBlend::Qb95::Qs3;
        constexpr QColor BorderLight   = Palette::PrimaryBlend::Qb95::Qs6;
        constexpr QColor Background    = Palette::PrimaryBlend::Qb90::Qs1;
        constexpr QColor Highlight     = Palette::PrimaryBlend::Qb95::Qs3;
        constexpr QColor HighlightText = Palette::PrimaryBlend::Qb95::Qs6;
        constexpr QColor Foreground    = Palette::SecondaryGrey::Qb90::Qs4;
        constexpr int    BorderSize    = Pressed::BorderSize;
    }  // namespace PressedSecondary

    namespace Misc
    {
        constexpr QColor Empty       = QColor(0xFF, 0x00, 0xFF);
        constexpr QColor Transparent = QColor(0xFF, 0x00, 0xFF, 0x00);

        constexpr QColor GoState   = Palette::Secondary::Qs1;
        constexpr QColor StopState = Palette::Error::Qs3;
    }  // namespace Misc

    namespace ToolTip
    {
        constexpr QColor Background = Window::Background;
        constexpr QColor Foreground = Window::ForegroundLight;
        constexpr QColor Border     = Window::BackgroundLight;
    }  // namespace ToolTip

    namespace Ctrl
    {
        constexpr QColor Background = Palette::Control1::Qs2;
        constexpr QColor Foreground = Palette::HighGrey::Qs1;
        constexpr int    BaseHeight = Points::Pt24;
        constexpr int    BaseWidth  = Points::Pt24;
        constexpr int    FontSize   = Points::Pt10;

        constexpr QSize MinSize = {BaseWidth, BaseHeight};
    }  // namespace Ctrl

    namespace Push
    {
        constexpr int   BaseHeight = Points::Pt24;
        constexpr int   BaseWidth  = Points::Pt64;
        constexpr int   FontSize   = Points::Pt10;
        constexpr QSize MinSize    = {BaseWidth, BaseHeight};
        constexpr QSize MaxSize    = {Points::Pt96, Points::Pt32};
    }  // namespace Push

    namespace Slider
    {
        constexpr QColor Background = Palette::Control1::Qs2;
        constexpr QColor Foreground = Palette::HighGrey::Qs1;
        constexpr int    BaseHeight = Points::Pt18;
        constexpr int    BaseWidth  = Points::Pt24;
        constexpr int    FontSize   = Points::Pt10;

        constexpr QSize MinSize = {BaseWidth, BaseHeight};

    }  // namespace Slider

    namespace Title
    {
        constexpr QColor   Background = Palette::Control1::Qs0;
        constexpr QColor   Foreground = Palette::HighBlueGrey::Qs0;
        constexpr int      Height     = Points::Pt24;
        constexpr int      TextSize   = Points::Pt16;
        constexpr QSize    MinSize    = {Window::BaseWidth, Height};
        constexpr QMargins Margin     = Margin::Small;
    }  // namespace Title

    namespace Panel
    {
        constexpr QColor   Background    = Window::Background;
        constexpr int      TitleHeight   = Points::Pt24;
        constexpr int      TitleTextSize = Points::Pt24;
        constexpr QSize    Minimum       = {200, 100};
        constexpr QMargins Margin        = Margin::None;
    }  // namespace Panel

    namespace TextEdit
    {
        constexpr QColor   Background = Window::BackgroundLight;
        constexpr QColor   Foreground = Window::ForegroundLight;
        constexpr QSize    Minimum    = {200, 100};
        constexpr QMargins Margin     = Margin::None;
        constexpr int      TextSize   = Points::Pt08;
    }  // namespace TextEdit

    class Widget
    {
    public:
        static LabelView* label();
        static LabelView* label(const String& text);
        static LabelView* label(const String& text, int size);
        static LabelView* label(const String& text, int size, const QColor& color);
        static LabelView* label(int size);
        static LabelView* label(int size, const QColor& color);

        static LabelView* iconLabel(const IconMap& ico);
        static LabelView* iconLabel(const IconMap& ico, int size);
        static LabelView* iconLabel(const IconMap& ico, int size, const QSize& bounds);

        static QLabel* centeredLabel(const QSize& bounds);
        static QLabel* centeredLabel(const String& text, const QSize& bounds);

        static QWidget* box();

        static QPushButton* push();
        static QPushButton* push(const String& text);

        static QCheckBox* check(bool checked=false);
        static QCheckBox* check(const String& text, bool checked=false);

        static QWidget* idBox(const QColor& background);

        static QWidget* blank(const QColor& background);
        static QWidget* blank(QBoxLayout* layout, const QSize& size = Window::Small);
        static QWidget* blank(QBoxLayout* layout, const QColor& background);

        static QWidget* blank(const QSize&  size       = Window::Small,
                              const QColor& background = Window::Background);

        static QTextEdit* readonly();

        static QTextEdit* textEdit(bool readonly = false);

        static QLineEdit* lineEdit();

        static QGroupBox* groupBox(const String& text);

        static QComboBox* combo();
        static QComboBox* combo(const StringArray &choices, size_t index = 0);

        static QTabWidget* tabWidget();

        static QWidget* itemList(const QWidgetList& items);

        static QWidget* itemList(
            const QWidgetList& items,
            const int&         size,
            const QMargins&    margin,
            const QColor&      color,
            const QColor&      background);

        static QSplitter* splitHorizontal(QWidget* left, QWidget* right, int ls = 0, int rs = 0);
        static QSplitter* splitVertical(QWidget* left, QWidget* right, int ls = 0, int rs = 0);
        static QSplitter* split(QWidget* left, QWidget* right, const Qt::Orientation& orientation, int leftStretch = 0, int rightStretch = 0);
        static QSplitter* split(const Qt::Orientation& orientation);

        static QWidget* wrap(QLayout* layout);
    };

    class Constraint
    {
    public:
        static void minimum(QWidget* obj, const int& v);
        static void minimum(QWidget* obj, const QSize& v);

        static void maximum(QWidget* obj, const int& v);
        static void maximum(QWidget* obj, const QSize& v);

        static void fixed(QWidget* obj, const int& v);
        static void fixed(QWidget* obj, const QSize& v);

        static void width(QWidget* obj, const int& v);
        static void height(QWidget* obj, const int& v);

        static void stretch(QSplitter* obj, const int& a, const int& b);
    };

    class Layout
    {
    public:
        static QBoxLayout*  layout(const Qt::Orientation& orientation, int spacing, const QMargins& margin);
        static QVBoxLayout* vertical(int spacing, const QMargins& margin = Margin::None);
        static QVBoxLayout* vertical(const QMargins& margin, int spacing = Size::None);
        static QVBoxLayout* v0(int spacing = Size::None);
        static QVBoxLayout* v1(int spacing = Size::Small);
        static QVBoxLayout* v2(int spacing = Size::Medium);
        static QVBoxLayout* v3(int spacing = Size::Large);
        static QVBoxLayout* v4(int spacing = Size::XLarge);
        static QVBoxLayout* v5(int spacing = Size::XxLarge);

        static QHBoxLayout* horizontal(int spacing, const QMargins& margin = Margin::None);
        static QHBoxLayout* horizontal(const QMargins& margin, int spacing = Size::None);
        static QHBoxLayout* h0(int spacing = Size::None);
        static QHBoxLayout* h1(int spacing = Size::Small);
        static QHBoxLayout* h2(int spacing = Size::Medium);
        static QHBoxLayout* h3(int spacing = Size::Large);
        static QHBoxLayout* h4(int spacing = Size::XLarge);
        static QHBoxLayout* h5(int spacing = Size::XxLarge);
    };

    class Views
    {
    public:
        static TextEditView* textEdit();
        static TextEditView* textEdit(const StringModel::Observer& change);
        static TextEditView* textEdit(const String& label, const StringModel::Observer& change);

        static MultiLineTextEditView* multilineEdit(bool readonly = false);
        static MultiLineTextEditView* multilineEdit(const StringModel::Observer& change);
        static MultiLineTextEditView* multilineEdit(const String& text, const StringModel::Observer& change);

        static PushButtonView* push();
        static PushButtonView* push(const String& label);
        static PushButtonView* push(const String& label, const BoolModel::Observer& pressed);

        static CheckBoxView* check();
        static CheckBoxView* check(const BoolModel::Observer& pressed);

        static IconButtonView* icon(const IconMap& ico);
        static IconButtonView* icon(const IconMap& ico, const BoolModel::Observer& click);

        static IconButtonView* flatIcon(const IconMap& ico);
        static IconButtonView* flatIcon(const IconMap& ico, const BoolModel::Observer& click);

        static TitleListView* title(const String& title);
        static TitleListView* title(const String& v, const QWidgetList& widgetList);

        static FlagView* flag();
        static FlagView* flag(uint8_t v);
        static FlagView* flag(uint16_t v);
        static FlagView* flag(uint32_t v);

        static SliderView* slider();
        static SliderView* slider(const FloatModel::Observer& change);
        static SliderView* slider(qreal value, qreal rangeStart, qreal rangeStop);
        static SliderView* slider(qreal                       value,
                                  qreal                       rangeStart,
                                  qreal                       rangeStop,
                                  const FloatModel::Observer& change);

        static StringListView* stringList();
    };
}  // namespace Rt2::View::Style
