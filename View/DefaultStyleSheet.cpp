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
#include "View/DefaultStyleSheet.h"
#include "View/Qu.h"
#include "View/Style.h"
#include "View/StyleSheetWriter.h"

// manual process:
// + #define DefaultStyleSheetUpdate
// + Save the stream to a file.
// + Use ResourceCompiler to convert it.
// + Adjust the constant below.

namespace Rt2::View
{
#ifdef DefaultStyleSheetUpdate

    void DefaultStyleSheet::get(QString& dest)
    {
        OutputStringStream stream;

        {
            StyleSheetWriter style(&stream);

            style.beginUniversal();
            style.backgroundColor(Style::Window::Background);
            style.color(Style::Window::Foreground);
            style.fontSize(Style::Window::FontSize);
            style.noBorder();
            style.end();

            style.beginType("QToolTip");
            style.background(Style::ToolTip::Background);
            style.color(Style::ToolTip::Foreground);
            style.border(Style::ToolTip::Border, Style::Normal::BorderSize);
            style.padding(Style::Size::Tiny);
            style.end();

            style.beginClass("QMenuBar");
            style.backgroundColor(Style::Window::Background);
            style.color(Style::Window::Foreground);
            style.marginRight(Style::Size::Medium);
            style.noBorder();
            style.end();

            style.beginClass("QMenuBar::item:selected");
            style.backgroundColor(Style::Window::BackgroundLight);
            style.end();

            style.beginClass("QMenu");
            style.backgroundColor(Style::Window::BackgroundLight);
            style.color(Style::Window::ForegroundDark);
            style.margin(Style::Size::Small);
            style.noBorder();
            style.end();

            style.beginClass("QMenu::item");
            style.backgroundColor(Style::Window::BackgroundLight);
            style.color(Style::Window::Foreground);
            style.margin(Style::Size::Tiny);
            style.padding(Style::Size::Small);
            style.noBorder();
            style.end();

            style.beginType("QMenu::separator");
            style.margin(Style::Margin::Small);
            style.borderBottom(Style::Window::ForegroundDark, 1);
            style.height(Style::FontSize::Normal);
            style.end();

            style.beginType("QMenu::item::selected");
            style.backgroundColor(Style::Window::Accent);
            style.color(Style::Window::ForegroundLight);
            style.margin(Style::Size::Tiny);
            style.padding(Style::Size::Small);
            style.noBorder();
            style.end();

            // style.begin("QLineEdit");
            // style.backgroundColor(Colors::d1(Colors::CtrlBackground));
            // style.noBorder();
            // style.end();

            style.beginType("QGroupBox");
            style.padding(Style::Margin::Medium);
            style.border(Style::Window::Border, 1);
            style.borderRadius(Style::Size::Medium);
            style.end();

            style.beginType("QGroupBox:title");
            style.top(-Style::Points::Pt16);
            style.left(Style::Points::Pt16);
            style.end();

            style.beginType("QListView");
            style.selectionColor(Style::ListView::Foreground);
            style.backgroundColor(Style::ListView::Background);
            style.color(Style::ListView::Foreground);
            style.outline(0);
            style.noBorder();
            style.end();

            style.beginType("QListView::item:alternate");
            style.backgroundColor(Style::ListView::Alternate);
            style.end();

            style.beginType("QListView::item:selected");
            style.backgroundColor(Style::ListView::Selection);
            style.end();

            style.beginType("QListView::item:hover");
            style.backgroundColor(Style::ListView::Hover);
            style.end();

            style.beginType("QScrollBar:vertical");
            style.noBackground();
            style.width(Style::ScrollBar::Size);
            style.minWidth(Style::ScrollBar::Size);
            style.padding(Style::ScrollBar::Padding, 0, Style::ScrollBar::Padding, 0);
            style.end();

            style.beginType("QScrollBar:horizontal");
            style.noBackground();
            style.height(Style::ScrollBar::Size);
            style.minHeight(Style::ScrollBar::Size);
            style.padding(0, Style::ScrollBar::Padding, 0, Style::ScrollBar::Padding);
            style.end();

            style.begin("QScrollBar::handle:vertical");
            style.backgroundColor(Style::ScrollBar::Handle);
            style.noBorder();
            style.width(Style::ScrollBar::HandleSize);
            style.margin(Style::ScrollBar::HandleMargin, 0, Style::ScrollBar::HandleMargin, 0);
            style.end();

            style.begin("QScrollBar::handle:horizontal");
            style.backgroundColor(Style::ScrollBar::Handle);
            style.noBorder();
            style.height(Style::ScrollBar::HandleSize);
            style.margin(0, Style::ScrollBar::HandleMargin, 0, Style::ScrollBar::HandleMargin);
            style.end();

            style.begin("QScrollBar::add-line:horizontal,QScrollBar::sub-line:horizontal");
            style.width(0);
            style.end();

            // style.begin("QScrollBar::sub-line:horizontal");
            // style.width(0);
            // style.end();

            style.begin("QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical");
            style.height(0);
            style.end();

            // style.begin("QScrollBar::sub-line:vertical");
            // style.height(0);
            // style.end();

            style.begin("QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical");
            style.noBorder();
            style.noBackground();
            style.end();

            // style.begin("QScrollBar::sub-page:vertical");
            // style.noBorder();
            // style.noBackground();
            // style.end();

            style.begin("QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal");
            style.noBorder();
            style.noBackground();
            style.end();

            // style.begin("QScrollBar::sub-page:horizontal");
            // style.noBorder();
            // style.noBackground();
            // style.end();

            // style.begin("QCheckBox");
            // style.backgroundColor(Colors::CtrlBackgroundLight);
            // style.border(Colors::BorderLight, 1);
            // style.end();

            // style.begin("QCheckBox::indicator:unchecked ");
            // style.backgroundColor(Colors::CtrlBackgroundLight);
            // style.border(Colors::BorderLight, 1);
            // style.end();

            // style.begin("QCheckBox::indicator:checked ");
            // style.backgroundColor(Colors::Accent);
            // style.color(Colors::CtrlBackgroundLight);
            // style.border(Colors::BorderLight, 1);
            // style.end();

            style.begin("QTreeWidget");
            style.showSelectedDecoration(true);
            style.backgroundColor(Style::Panel::Background);
            style.noBorder();
            style.noOutline();
            style.end();

            style.begin("QTreeWidget::branch:has-children:adjoins-item:closed");
            style.image(":/images/right.svg");
            style.end();

            style.begin("QTreeWidget::branch:has-children:adjoins-item:open");
            style.image(":/images/down.svg");
            style.end();

            style.begin("QTreeWidget::branch:!has-children:adjoins-item");
            style.image(":/images/stop.svg");
            style.end();

            style.begin("QTreeWidget::item");
            style.showSelectedDecoration(false);
            style.noBorder();
            style.noOutline();
            style.selectionBackgroundColor(Style::Window::Accent);
            style.end();

            style.begin("QTreeWidget::item::hover");
            style.noBorder();
            style.backgroundColor(Style::Window::Accent);
            style.color(Style::Window::Foreground);
            style.noOutline();
            style.end();

            style.begin("QTreeWidget::item::selected");
            style.backgroundColor(Style::Window::Accent);
            style.color(Style::Window::Foreground);
            style.noOutline();
            style.end();

            style.begin("QSplitter");
            style.backgroundColor(Style::Window::Background);
            style.end();

            style.begin("QSplitter::handle");
            style.backgroundColor(Style::Window::Separator);
            style.end();
            style.begin("QSplitter::handle:horizontal");
            style.width(Style::Window::BorderSize);
            style.end();
            style.begin("QSplitter::handle:vertical");
            style.height(Style::Window::BorderSize);
            style.end();

            style.begin("QTextEdit");
            style.backgroundColor(Style::Window::Background);
            style.noBorder();
            style.selectionBackgroundColor(Style::Window::Accent);
            style.selectionColor(Style::Window::Accent);
            style.color(Style::Window::Foreground);
            style.end();

            style.begin("QTabWidget");
            style.backgroundColor(Style::TabBar::Background);
            style.noBorder();
            style.end();

            style.begin("QTabWidget::pane");
            style.backgroundColor(Style::TabBar::Pane);
            style.noBorder();
            style.margin(Style::Size::None);
            style.end();

            // style.begin("QTabWidget::tab-bar");
            // style.backgroundColor(Style::Misc::Empty);
            // style.noBorder();
            // style.end();

            style.begin("QTabBar");
            style.backgroundColor(Style::TabBar::Tab);
            style.height(Style::Window::BaseHeight);
            style.noBorder();
            style.end();

            style.begin("QTabBar::tab");
            style.borderBottom(Style::TabBar::Tab, Style::TabBar::BorderSize);
            style.padding(Style::TabBar::Padding);
            style.minSize(Style::TabBar::Size);
            style.fontSize(Style::TabBar::FontSize);
            style.minWidth(Style::TabBar::BaseWidth);
            style.end();

            style.begin("QTabBar::tab:selected");
            style.borderBottom(Style::TabBar::Accent, Style::TabBar::BorderSize);
            style.end();

            style.begin("QTabBar QToolButton::right-arrow");
            style.color(Style::Palette::PrimaryBlend::Qb60::Qs4);
            style.image(":/images/right.svg");
            style.minSize(QSizeF{Style::Points::Pt20, Style::Points::Pt20});
            style.end();

            style.begin("QTabBar QToolButton::left-arrow");
            style.color(Style::Palette::PrimaryBlend::Qb60::Qs4);
            style.image(":/images/left.svg");
            style.minSize(QSizeF{Style::Points::Pt20, Style::Points::Pt20});
            style.end();
        }
        dest = Qsu::to(stream.str());

        OutputFileStream ofs("test.css");
        ofs << stream.str();
    }
#else
    // clang-format off
   constexpr uint8_t DefaultStyle[3094]={
 0x2A,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,
  0x6F,0x72,0x3A,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x63,0x6F,0x6C,0x6F,0x72,
  0x3A,0x23,0x43,0x42,0x43,0x42,0x43,0x45,0x3B,0x66,0x6F,0x6E,0x74,0x2D,0x73,0x69,
  0x7A,0x65,0x3A,0x41,0x70,0x74,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,
  0x6E,0x65,0x3B,0x7D,0x51,0x54,0x6F,0x6F,0x6C,0x54,0x69,0x70,0x7B,0x62,0x61,0x63,
  0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x3A,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,
  0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x45,0x42,0x45,0x42,0x45,0x45,0x3B,0x62,0x6F,
  0x72,0x64,0x65,0x72,0x3A,0x31,0x70,0x78,0x20,0x73,0x6F,0x6C,0x69,0x64,0x20,0x23,
  0x32,0x42,0x32,0x42,0x32,0x46,0x3B,0x70,0x61,0x64,0x64,0x69,0x6E,0x67,0x3A,0x31,
  0x70,0x78,0x3B,0x7D,0x2E,0x51,0x4D,0x65,0x6E,0x75,0x42,0x61,0x72,0x7B,0x62,0x61,
  0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,
  0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x43,0x42,
  0x43,0x42,0x43,0x45,0x3B,0x6D,0x61,0x72,0x67,0x69,0x6E,0x2D,0x72,0x69,0x67,0x68,
  0x74,0x3A,0x36,0x70,0x78,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,
  0x65,0x3B,0x7D,0x2E,0x51,0x4D,0x65,0x6E,0x75,0x42,0x61,0x72,0x3A,0x3A,0x69,0x74,
  0x65,0x6D,0x3A,0x73,0x65,0x6C,0x65,0x63,0x74,0x65,0x64,0x7B,0x62,0x61,0x63,0x6B,
  0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,0x42,
  0x32,0x42,0x32,0x46,0x3B,0x7D,0x2E,0x51,0x4D,0x65,0x6E,0x75,0x7B,0x62,0x61,0x63,
  0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,
  0x42,0x32,0x42,0x32,0x46,0x3B,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x39,0x41,0x39,
  0x41,0x39,0x45,0x3B,0x6D,0x61,0x72,0x67,0x69,0x6E,0x3A,0x20,0x33,0x70,0x78,0x3B,
  0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x2E,0x51,0x4D,
  0x65,0x6E,0x75,0x3A,0x3A,0x69,0x74,0x65,0x6D,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,
  0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,0x42,0x32,0x42,
  0x32,0x46,0x3B,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x43,0x42,0x43,0x42,0x43,0x45,
  0x3B,0x6D,0x61,0x72,0x67,0x69,0x6E,0x3A,0x20,0x31,0x70,0x78,0x3B,0x70,0x61,0x64,
  0x64,0x69,0x6E,0x67,0x3A,0x33,0x70,0x78,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,
  0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x51,0x4D,0x65,0x6E,0x75,0x3A,0x3A,0x73,0x65,0x70,
  0x61,0x72,0x61,0x74,0x6F,0x72,0x7B,0x6D,0x61,0x72,0x67,0x69,0x6E,0x3A,0x20,0x33,
  0x70,0x78,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x2D,0x62,0x6F,0x74,0x74,0x6F,0x6D,
  0x3A,0x31,0x70,0x78,0x20,0x73,0x6F,0x6C,0x69,0x64,0x20,0x23,0x39,0x41,0x39,0x41,
  0x39,0x45,0x3B,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,0x41,0x70,0x78,0x3B,0x7D,0x51,
  0x4D,0x65,0x6E,0x75,0x3A,0x3A,0x69,0x74,0x65,0x6D,0x3A,0x3A,0x73,0x65,0x6C,0x65,
  0x63,0x74,0x65,0x64,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,
  0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,0x42,0x32,0x3B,0x63,0x6F,
  0x6C,0x6F,0x72,0x3A,0x23,0x45,0x42,0x45,0x42,0x45,0x45,0x3B,0x6D,0x61,0x72,0x67,
  0x69,0x6E,0x3A,0x20,0x31,0x70,0x78,0x3B,0x70,0x61,0x64,0x64,0x69,0x6E,0x67,0x3A,
  0x33,0x70,0x78,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,
  0x7D,0x51,0x47,0x72,0x6F,0x75,0x70,0x42,0x6F,0x78,0x7B,0x70,0x61,0x64,0x64,0x69,
  0x6E,0x67,0x3A,0x36,0x70,0x78,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x31,0x70,
  0x78,0x20,0x73,0x6F,0x6C,0x69,0x64,0x20,0x23,0x33,0x34,0x33,0x34,0x33,0x37,0x3B,
  0x62,0x6F,0x72,0x64,0x65,0x72,0x2D,0x72,0x61,0x64,0x69,0x75,0x73,0x3A,0x36,0x70,
  0x78,0x3B,0x7D,0x51,0x47,0x72,0x6F,0x75,0x70,0x42,0x6F,0x78,0x3A,0x74,0x69,0x74,
  0x6C,0x65,0x7B,0x74,0x6F,0x70,0x3A,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x30,0x70,
  0x78,0x3B,0x6C,0x65,0x66,0x74,0x3A,0x31,0x30,0x70,0x78,0x3B,0x7D,0x51,0x4C,0x69,
  0x73,0x74,0x56,0x69,0x65,0x77,0x7B,0x73,0x65,0x6C,0x65,0x63,0x74,0x69,0x6F,0x6E,
  0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x43,0x42,0x43,0x42,0x43,0x45,0x3B,0x62,
  0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,
  0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x43,
  0x42,0x43,0x42,0x43,0x45,0x3B,0x6F,0x75,0x74,0x6C,0x69,0x6E,0x65,0x3A,0x30,0x3B,
  0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x51,0x4C,0x69,
  0x73,0x74,0x56,0x69,0x65,0x77,0x3A,0x3A,0x69,0x74,0x65,0x6D,0x3A,0x61,0x6C,0x74,
  0x65,0x72,0x6E,0x61,0x74,0x65,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,
  0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,0x42,0x32,0x42,0x32,0x46,0x3B,
  0x7D,0x51,0x4C,0x69,0x73,0x74,0x56,0x69,0x65,0x77,0x3A,0x3A,0x69,0x74,0x65,0x6D,
  0x3A,0x73,0x65,0x6C,0x65,0x63,0x74,0x65,0x64,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,
  0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,
  0x42,0x32,0x3B,0x7D,0x51,0x4C,0x69,0x73,0x74,0x56,0x69,0x65,0x77,0x3A,0x3A,0x69,
  0x74,0x65,0x6D,0x3A,0x68,0x6F,0x76,0x65,0x72,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,
  0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,
  0x42,0x32,0x3B,0x7D,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x76,
  0x65,0x72,0x74,0x69,0x63,0x61,0x6C,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,
  0x6E,0x64,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x77,0x69,0x64,0x74,0x68,0x3A,0x42,0x70,
  0x78,0x3B,0x6D,0x69,0x6E,0x2D,0x77,0x69,0x64,0x74,0x68,0x3A,0x31,0x31,0x70,0x78,
  0x3B,0x7D,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x68,0x6F,0x72,
  0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,
  0x6E,0x64,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,0x42,
  0x70,0x78,0x3B,0x6D,0x69,0x6E,0x2D,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,0x31,0x31,
  0x70,0x78,0x3B,0x7D,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,
  0x68,0x61,0x6E,0x64,0x6C,0x65,0x3A,0x76,0x65,0x72,0x74,0x69,0x63,0x61,0x6C,0x7B,
  0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,
  0x3A,0x23,0x34,0x34,0x34,0x34,0x34,0x38,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,
  0x6E,0x6F,0x6E,0x65,0x3B,0x77,0x69,0x64,0x74,0x68,0x3A,0x41,0x70,0x78,0x3B,0x6D,
  0x61,0x72,0x67,0x69,0x6E,0x2D,0x6C,0x65,0x66,0x74,0x3A,0x31,0x70,0x78,0x3B,0x6D,
  0x61,0x72,0x67,0x69,0x6E,0x2D,0x72,0x69,0x67,0x68,0x74,0x3A,0x31,0x70,0x78,0x3B,
  0x7D,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x68,0x61,0x6E,
  0x64,0x6C,0x65,0x3A,0x68,0x6F,0x72,0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,0x7B,0x62,
  0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,
  0x23,0x34,0x34,0x34,0x34,0x34,0x38,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,
  0x6F,0x6E,0x65,0x3B,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,0x41,0x70,0x78,0x3B,0x6D,
  0x61,0x72,0x67,0x69,0x6E,0x2D,0x74,0x6F,0x70,0x3A,0x31,0x70,0x78,0x3B,0x6D,0x61,
  0x72,0x67,0x69,0x6E,0x2D,0x62,0x6F,0x74,0x74,0x6F,0x6D,0x3A,0x31,0x70,0x78,0x3B,
  0x7D,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x61,0x64,0x64,
  0x2D,0x6C,0x69,0x6E,0x65,0x3A,0x68,0x6F,0x72,0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,
  0x2C,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x73,0x75,0x62,
  0x2D,0x6C,0x69,0x6E,0x65,0x3A,0x68,0x6F,0x72,0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,
  0x7B,0x77,0x69,0x64,0x74,0x68,0x3A,0x30,0x70,0x78,0x3B,0x7D,0x51,0x53,0x63,0x72,
  0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x61,0x64,0x64,0x2D,0x6C,0x69,0x6E,0x65,
  0x3A,0x76,0x65,0x72,0x74,0x69,0x63,0x61,0x6C,0x2C,0x51,0x53,0x63,0x72,0x6F,0x6C,
  0x6C,0x42,0x61,0x72,0x3A,0x3A,0x73,0x75,0x62,0x2D,0x6C,0x69,0x6E,0x65,0x3A,0x76,
  0x65,0x72,0x74,0x69,0x63,0x61,0x6C,0x7B,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,0x30,
  0x70,0x78,0x3B,0x7D,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,
  0x61,0x64,0x64,0x2D,0x70,0x61,0x67,0x65,0x3A,0x76,0x65,0x72,0x74,0x69,0x63,0x61,
  0x6C,0x2C,0x51,0x53,0x63,0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x73,0x75,
  0x62,0x2D,0x70,0x61,0x67,0x65,0x3A,0x76,0x65,0x72,0x74,0x69,0x63,0x61,0x6C,0x7B,
  0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x62,0x61,0x63,0x6B,
  0x67,0x72,0x6F,0x75,0x6E,0x64,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x51,0x53,0x63,
  0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x61,0x64,0x64,0x2D,0x70,0x61,0x67,
  0x65,0x3A,0x68,0x6F,0x72,0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,0x2C,0x51,0x53,0x63,
  0x72,0x6F,0x6C,0x6C,0x42,0x61,0x72,0x3A,0x3A,0x73,0x75,0x62,0x2D,0x70,0x61,0x67,
  0x65,0x3A,0x68,0x6F,0x72,0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,0x7B,0x62,0x6F,0x72,
  0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,
  0x75,0x6E,0x64,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x51,0x54,0x72,0x65,0x65,0x57,
  0x69,0x64,0x67,0x65,0x74,0x7B,0x73,0x68,0x6F,0x77,0x2D,0x64,0x65,0x63,0x6F,0x72,
  0x61,0x74,0x69,0x6F,0x6E,0x2D,0x73,0x65,0x6C,0x65,0x63,0x74,0x65,0x64,0x3A,0x31,
  0x3B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,
  0x72,0x3A,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,
  0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x6F,0x75,0x74,0x6C,0x69,0x6E,0x65,0x3A,0x6E,0x6F,
  0x6E,0x65,0x3B,0x7D,0x51,0x54,0x72,0x65,0x65,0x57,0x69,0x64,0x67,0x65,0x74,0x3A,
  0x3A,0x62,0x72,0x61,0x6E,0x63,0x68,0x3A,0x68,0x61,0x73,0x2D,0x63,0x68,0x69,0x6C,
  0x64,0x72,0x65,0x6E,0x3A,0x61,0x64,0x6A,0x6F,0x69,0x6E,0x73,0x2D,0x69,0x74,0x65,
  0x6D,0x3A,0x63,0x6C,0x6F,0x73,0x65,0x64,0x7B,0x69,0x6D,0x61,0x67,0x65,0x3A,0x75,
  0x72,0x6C,0x28,0x3A,0x2F,0x69,0x6D,0x61,0x67,0x65,0x73,0x2F,0x72,0x69,0x67,0x68,
  0x74,0x2E,0x73,0x76,0x67,0x29,0x3B,0x7D,0x51,0x54,0x72,0x65,0x65,0x57,0x69,0x64,
  0x67,0x65,0x74,0x3A,0x3A,0x62,0x72,0x61,0x6E,0x63,0x68,0x3A,0x68,0x61,0x73,0x2D,
  0x63,0x68,0x69,0x6C,0x64,0x72,0x65,0x6E,0x3A,0x61,0x64,0x6A,0x6F,0x69,0x6E,0x73,
  0x2D,0x69,0x74,0x65,0x6D,0x3A,0x6F,0x70,0x65,0x6E,0x7B,0x69,0x6D,0x61,0x67,0x65,
  0x3A,0x75,0x72,0x6C,0x28,0x3A,0x2F,0x69,0x6D,0x61,0x67,0x65,0x73,0x2F,0x64,0x6F,
  0x77,0x6E,0x2E,0x73,0x76,0x67,0x29,0x3B,0x7D,0x51,0x54,0x72,0x65,0x65,0x57,0x69,
  0x64,0x67,0x65,0x74,0x3A,0x3A,0x62,0x72,0x61,0x6E,0x63,0x68,0x3A,0x21,0x68,0x61,
  0x73,0x2D,0x63,0x68,0x69,0x6C,0x64,0x72,0x65,0x6E,0x3A,0x61,0x64,0x6A,0x6F,0x69,
  0x6E,0x73,0x2D,0x69,0x74,0x65,0x6D,0x7B,0x69,0x6D,0x61,0x67,0x65,0x3A,0x75,0x72,
  0x6C,0x28,0x3A,0x2F,0x69,0x6D,0x61,0x67,0x65,0x73,0x2F,0x73,0x74,0x6F,0x70,0x2E,
  0x73,0x76,0x67,0x29,0x3B,0x7D,0x51,0x54,0x72,0x65,0x65,0x57,0x69,0x64,0x67,0x65,
  0x74,0x3A,0x3A,0x69,0x74,0x65,0x6D,0x7B,0x73,0x68,0x6F,0x77,0x2D,0x64,0x65,0x63,
  0x6F,0x72,0x61,0x74,0x69,0x6F,0x6E,0x2D,0x73,0x65,0x6C,0x65,0x63,0x74,0x65,0x64,
  0x3A,0x30,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x6F,
  0x75,0x74,0x6C,0x69,0x6E,0x65,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x73,0x65,0x6C,0x65,
  0x63,0x74,0x69,0x6F,0x6E,0x2D,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,
  0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,0x42,0x32,0x3B,0x7D,
  0x51,0x54,0x72,0x65,0x65,0x57,0x69,0x64,0x67,0x65,0x74,0x3A,0x3A,0x69,0x74,0x65,
  0x6D,0x3A,0x3A,0x68,0x6F,0x76,0x65,0x72,0x7B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,
  0x6E,0x6F,0x6E,0x65,0x3B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,
  0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,0x42,0x32,0x3B,0x63,0x6F,
  0x6C,0x6F,0x72,0x3A,0x23,0x43,0x42,0x43,0x42,0x43,0x45,0x3B,0x6F,0x75,0x74,0x6C,
  0x69,0x6E,0x65,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x51,0x54,0x72,0x65,0x65,0x57,
  0x69,0x64,0x67,0x65,0x74,0x3A,0x3A,0x69,0x74,0x65,0x6D,0x3A,0x3A,0x73,0x65,0x6C,
  0x65,0x63,0x74,0x65,0x64,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,
  0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,0x42,0x32,0x3B,0x63,
  0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x43,0x42,0x43,0x42,0x43,0x45,0x3B,0x6F,0x75,0x74,
  0x6C,0x69,0x6E,0x65,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x7D,0x51,0x53,0x70,0x6C,0x69,
  0x74,0x74,0x65,0x72,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,
  0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x7D,0x51,
  0x53,0x70,0x6C,0x69,0x74,0x74,0x65,0x72,0x3A,0x3A,0x68,0x61,0x6E,0x64,0x6C,0x65,
  0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,
  0x72,0x3A,0x23,0x33,0x34,0x33,0x34,0x33,0x37,0x3B,0x7D,0x51,0x53,0x70,0x6C,0x69,
  0x74,0x74,0x65,0x72,0x3A,0x3A,0x68,0x61,0x6E,0x64,0x6C,0x65,0x3A,0x68,0x6F,0x72,
  0x69,0x7A,0x6F,0x6E,0x74,0x61,0x6C,0x7B,0x77,0x69,0x64,0x74,0x68,0x3A,0x31,0x70,
  0x78,0x3B,0x7D,0x51,0x53,0x70,0x6C,0x69,0x74,0x74,0x65,0x72,0x3A,0x3A,0x68,0x61,
  0x6E,0x64,0x6C,0x65,0x3A,0x76,0x65,0x72,0x74,0x69,0x63,0x61,0x6C,0x7B,0x68,0x65,
  0x69,0x67,0x68,0x74,0x3A,0x31,0x70,0x78,0x3B,0x7D,0x51,0x54,0x65,0x78,0x74,0x45,
  0x64,0x69,0x74,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,
  0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x62,0x6F,0x72,
  0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x73,0x65,0x6C,0x65,0x63,0x74,0x69,
  0x6F,0x6E,0x2D,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,
  0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,0x36,0x42,0x32,0x3B,0x73,0x65,0x6C,0x65,
  0x63,0x74,0x69,0x6F,0x6E,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x35,0x36,0x35,
  0x36,0x42,0x32,0x3B,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x43,0x42,0x43,0x42,0x43,
  0x45,0x3B,0x7D,0x51,0x54,0x61,0x62,0x57,0x69,0x64,0x67,0x65,0x74,0x7B,0x62,0x61,
  0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,
  0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,
  0x6E,0x65,0x3B,0x7D,0x51,0x54,0x61,0x62,0x57,0x69,0x64,0x67,0x65,0x74,0x3A,0x3A,
  0x70,0x61,0x6E,0x65,0x7B,0x62,0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,
  0x63,0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x62,0x6F,
  0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,0x6D,0x61,0x72,0x67,0x69,0x6E,
  0x3A,0x20,0x30,0x70,0x78,0x3B,0x7D,0x51,0x54,0x61,0x62,0x42,0x61,0x72,0x7B,0x62,
  0x61,0x63,0x6B,0x67,0x72,0x6F,0x75,0x6E,0x64,0x2D,0x63,0x6F,0x6C,0x6F,0x72,0x3A,
  0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,0x31,
  0x38,0x70,0x78,0x3B,0x62,0x6F,0x72,0x64,0x65,0x72,0x3A,0x6E,0x6F,0x6E,0x65,0x3B,
  0x7D,0x51,0x54,0x61,0x62,0x42,0x61,0x72,0x3A,0x3A,0x74,0x61,0x62,0x7B,0x62,0x6F,
  0x72,0x64,0x65,0x72,0x2D,0x62,0x6F,0x74,0x74,0x6F,0x6D,0x3A,0x33,0x70,0x78,0x20,
  0x73,0x6F,0x6C,0x69,0x64,0x20,0x23,0x32,0x34,0x32,0x34,0x32,0x38,0x3B,0x70,0x61,
  0x64,0x64,0x69,0x6E,0x67,0x3A,0x33,0x70,0x78,0x3B,0x6D,0x69,0x6E,0x2D,0x77,0x69,
  0x64,0x74,0x68,0x3A,0x35,0x31,0x70,0x78,0x3B,0x6D,0x69,0x6E,0x2D,0x68,0x65,0x69,
  0x67,0x68,0x74,0x3A,0x32,0x37,0x70,0x78,0x3B,0x66,0x6F,0x6E,0x74,0x2D,0x73,0x69,
  0x7A,0x65,0x3A,0x45,0x70,0x74,0x3B,0x6D,0x69,0x6E,0x2D,0x77,0x69,0x64,0x74,0x68,
  0x3A,0x34,0x38,0x70,0x78,0x3B,0x7D,0x51,0x54,0x61,0x62,0x42,0x61,0x72,0x3A,0x3A,
  0x74,0x61,0x62,0x3A,0x73,0x65,0x6C,0x65,0x63,0x74,0x65,0x64,0x7B,0x62,0x6F,0x72,
  0x64,0x65,0x72,0x2D,0x62,0x6F,0x74,0x74,0x6F,0x6D,0x3A,0x33,0x70,0x78,0x20,0x73,
  0x6F,0x6C,0x69,0x64,0x20,0x23,0x35,0x36,0x35,0x36,0x42,0x32,0x3B,0x7D,0x51,0x54,
  0x61,0x62,0x42,0x61,0x72,0x20,0x51,0x54,0x6F,0x6F,0x6C,0x42,0x75,0x74,0x74,0x6F,
  0x6E,0x3A,0x3A,0x72,0x69,0x67,0x68,0x74,0x2D,0x61,0x72,0x72,0x6F,0x77,0x7B,0x63,
  0x6F,0x6C,0x6F,0x72,0x3A,0x23,0x39,0x44,0x42,0x46,0x41,0x39,0x3B,0x69,0x6D,0x61,
  0x67,0x65,0x3A,0x75,0x72,0x6C,0x28,0x3A,0x2F,0x69,0x6D,0x61,0x67,0x65,0x73,0x2F,
  0x72,0x69,0x67,0x68,0x74,0x2E,0x73,0x76,0x67,0x29,0x3B,0x6D,0x69,0x6E,0x2D,0x77,
  0x69,0x64,0x74,0x68,0x3A,0x32,0x30,0x70,0x78,0x3B,0x6D,0x69,0x6E,0x2D,0x68,0x65,
  0x69,0x67,0x68,0x74,0x3A,0x32,0x30,0x70,0x78,0x3B,0x7D,0x51,0x54,0x61,0x62,0x42,
  0x61,0x72,0x20,0x51,0x54,0x6F,0x6F,0x6C,0x42,0x75,0x74,0x74,0x6F,0x6E,0x3A,0x3A,
  0x6C,0x65,0x66,0x74,0x2D,0x61,0x72,0x72,0x6F,0x77,0x7B,0x63,0x6F,0x6C,0x6F,0x72,
  0x3A,0x23,0x39,0x44,0x42,0x46,0x41,0x39,0x3B,0x69,0x6D,0x61,0x67,0x65,0x3A,0x75,
  0x72,0x6C,0x28,0x3A,0x2F,0x69,0x6D,0x61,0x67,0x65,0x73,0x2F,0x6C,0x65,0x66,0x74,
  0x2E,0x73,0x76,0x67,0x29,0x3B,0x6D,0x69,0x6E,0x2D,0x77,0x69,0x64,0x74,0x68,0x3A,
  0x32,0x30,0x70,0x78,0x3B,0x6D,0x69,0x6E,0x2D,0x68,0x65,0x69,0x67,0x68,0x74,0x3A,
  0x32,0x30,0x70,0x78,0x3B,0x7D,
   };
    // clang-format on

    void DefaultStyleSheet::get(QString& dest)
    {
        String str;
        str.assign((const char*)DefaultStyle, 3094);
        dest = Qsu::to(str);
    }
#endif

}  // namespace Rt2::View
