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
#include "View/Style.h"
#include <qstyle.h>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSplitter>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include "CheckBoxView.h"
#include "FlagView.h"
#include "IconButtonView.h"
#include "ItemListWidget.h"
#include "MultiLineTextEditView.h"
#include "PushButtonView.h"
#include "Qu.h"
#include "SliderView.h"
#include "StringListView.h"
#include "StyleSheetWriter.h"
#include "TextEditView.h"
#include "TitleListWidget.h"

namespace Rt2::View::Style
{
    namespace Common
    {
        void makeInputStatic(QWidget* obj)
        {
            RT_GUARD_CHECK_VOID(obj)
            obj->setAttribute(Qt::WA_TransparentForMouseEvents);
            obj->setAttribute(Qt::WA_InputMethodTransparent);
        }

        void makeTranslucent(QWidget* obj)
        {
            RT_GUARD_CHECK_VOID(obj)
            obj->setAttribute(Qt::WA_TintedBackground);
        }

        void clearMargin(QWidget* obj)
        {
            RT_GUARD_CHECK_VOID(obj)
            obj->setContentsMargins(Margin::None);
        }

        void alignCenter(QLabel* obj, const QSize& max)
        {
            RT_GUARD_CHECK_VOID(obj)
            obj->setMinimumSize(max);
            obj->setAlignment(Qt::AlignCenter);
        }

        void clearFrame(QFrame* obj)
        {
            RT_GUARD_CHECK_VOID(obj)
            clearMargin(obj);
            obj->setFrameShape(QFrame::NoFrame);
        }

        QFont iconFont(const int& size = Icon::Normal)
        {
            QFont fnt(Fonts::IconFamily);
            fnt.setPointSize(size);
            return fnt;
        }

        QFont fixedWidth(const int& size = Window::FontSize)
        {
            QFont fnt(Fonts::FixedWidthFamily);
            fnt.setPointSize(size);
            return fnt;
        }

        void textStyle(QLabel* obj, const int size, const QColor& col = Normal::Foreground)
        {
            RT_GUARD_CHECK_VOID(obj)
            StyleSheetWriter style;
            style.fontSize(size);
            style.noBackground();
            style.color(Normal::Foreground);
            obj->setStyleSheet(style.toString());
        }

        void backgroundStyle(QWidget* obj, const QColor& background)
        {
            RT_GUARD_CHECK_VOID(obj)

            const QString    name = obj->objectName();
            StyleSheetWriter w;
            if (!name.isEmpty())
                w.beginId(Qsu::from(name));
            w.backgroundColor(background);
            w.color(Window::Foreground);
            w.noBorder();

            if (!name.isEmpty())
                w.end();
            obj->setStyleSheet(w.toString());
        }

    }  // namespace Common

    QLabel* Widget::label()
    {
        const auto obj = new QLabel();
        Common::makeInputStatic(obj);
        Common::clearFrame(obj);
        Common::textStyle(obj, FontSize::Normal, Window::Foreground);
        return obj;
    }

    QLabel* Widget::label(const String& text)
    {
        return label(text, FontSize::Normal);
    }

    QLabel* Widget::label(const String& text, const int size)
    {
        return label(text, size, Normal::Foreground);
    }

    QLabel* Widget::label(const String& text, const int size, const QColor& color)
    {
        const auto obj = label();
        obj->setText(Qsu::to(text));
        Common::textStyle(obj, size, color);
        return obj;
    }

    QLabel* Widget::label(const int size)
    {
        return label(size, Window::Foreground);
    }

    QLabel* Widget::label(const int size, const QColor& color)
    {
        const auto obj = label();
        Common::textStyle(obj, size, color);
        return obj;
    }

    QLabel* Widget::iconLabel(const IconMap& ico)
    {
        return iconLabel(ico, FontSize::Normal);
    }

    QLabel* Widget::iconLabel(const IconMap& ico, const int size)
    {
        const auto obj = new QLabel();
        if (ico != IconNone)
            obj->setText(QChar(ico));

        Common::makeInputStatic(obj);
        Common::clearFrame(obj);

        QFont fnt(Fonts::IconFamily);
        fnt.setPointSize(size);
        obj->setFont(fnt);

        Common::alignCenter(obj, {size, size});
        return obj;
    }

    QLabel* Widget::iconLabel(const IconMap& ico, const int size, const QSize& bounds)
    {
        const auto obj = iconLabel(ico, size);
        Common::alignCenter(obj, bounds);
        return obj;
    }

    QLabel* Widget::centeredLabel(const QSize& bounds)
    {
        const auto obj = label();
        Common::alignCenter(obj, bounds);
        return obj;
    }

    QLabel* Widget::centeredLabel(const String& text, const QSize& bounds)
    {
        const auto obj = centeredLabel(bounds);
        obj->setText(Qsu::to(text));
        return obj;
    }

    QWidget* Widget::box()
    {
        const auto obj = new QWidget();
        Common::clearMargin(obj);
        return obj;
    }

    QWidget* Widget::idBox(const QColor& background)
    {
        const auto obj = box();
        obj->setObjectName(Qsu::name(obj));
        Common::makeTranslucent(obj);
        Common::backgroundStyle(obj, background);
        return obj;
    }

    QWidget* Widget::blank(const QColor& background)
    {
        const auto obj = new QWidget();
        Common::clearMargin(obj);
        Common::makeTranslucent(obj);
        Common::backgroundStyle(obj, background);
        return obj;
    }

    QWidget* Widget::blank(const QSize& size, const QColor& background)
    {
        const auto obj = blank(background);
        obj->setMinimumSize(size);
        return obj;
    }

    QWidget* Widget::blank(QBoxLayout* layout, const QSize& size)
    {
        const auto obj = blank(size);
        obj->setLayout(layout);
        return obj;
    }

    QWidget* Widget::blank(QBoxLayout* layout, const QColor& background)
    {
        const auto obj = blank(Window::Small);
        obj->setLayout(layout);
        Common::makeTranslucent(obj);
        Common::backgroundStyle(obj, background);
        return obj;
    }

    QTextEdit* Widget::readonly()
    {
        return textEdit(true);
    }

    QTextEdit* Widget::textEdit(const bool readonly)
    {
        const auto obj = new QTextEdit();
        obj->setFont(Common::fixedWidth());
        Common::clearMargin(obj);

        obj->setReadOnly(readonly);
        StyleSheetWriter w;
        if (readonly)
        {
            obj->setObjectName("readonly");
            w.beginClassId("QTextEdit", "readonly");
        }
        else
        {
            obj->setObjectName("normal");
            w.beginClassId("QTextEdit", "normal");
        }

        w.backgroundColor(TextEdit::Background);
        w.color(TextEdit::Foreground);
        w.fontSize(TextEdit::TextSize);
        w.end();
        obj->setStyleSheet(w.toString());
        return obj;
    }

    QLineEdit* Widget::lineEdit()
    {
        const auto obj = new QLineEdit();
        Common::clearMargin(obj);
        Constraint::height(obj, Window::BaseHeight);
        obj->setFrame(false);
        obj->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        return obj;
    }

    QGroupBox* Widget::groupBox(const String& text)
    {
        const auto obj = new QGroupBox(Qsu::to(text));
        Common::clearMargin(obj);
        return obj;
    }

    QTabWidget* Widget::tabWidget()
    {
        const auto obj = new QTabWidget();
        Common::clearMargin(obj);
        Common::backgroundStyle(obj, Window::Background);
        return obj;
    }

    QWidget* Widget::itemList(const QWidgetList& items)
    {
        return new ItemListWidget(items);
    }

    QWidget* Widget::itemList(const QWidgetList& items,
                              const int&         size,
                              const QMargins&    margin,
                              const QColor&      color,
                              const QColor&      background)
    {
        return new ItemListWidget(items, size, margin, color, background);
    }

    QSplitter* Widget::hs(QWidget* left, QWidget* right)
    {
        const auto obj = split(left, right, Qt::Horizontal);
        return obj;
    }

    QSplitter* Widget::vs(QWidget* left, QWidget* right)
    {
        const auto obj = split(left, right, Qt::Vertical);
        return obj;
    }

    QSplitter* Widget::split(QWidget* left, QWidget* right, const Qt::Orientation& ori)
    {
        // fall back cases
        if (!left) left = box();
        if (!right) right = box();

        const auto obj = new QSplitter();
        obj->setOrientation(ori);
        obj->addWidget(left);
        obj->addWidget(right);
        return obj;
    }

    void Constraint::minimum(QWidget* obj, const int& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMinimumSize({v, v});
    }

    void Constraint::minimum(QWidget* obj, const QSize& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMinimumSize(v);
    }

    void Constraint::maximum(QWidget* obj, const int& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMaximumSize({v, v});
    }

    void Constraint::maximum(QWidget* obj, const QSize& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMaximumSize(v);
    }

    void Constraint::fixed(QWidget* obj, const int& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMinimumSize({v, v});
        obj->setFixedSize(obj->minimumSize());
    }

    void Constraint::fixed(QWidget* obj, const QSize& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMinimumSize(v);
        obj->setFixedSize(obj->minimumSize());
    }

    void Constraint::width(QWidget* obj, const int& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMinimumWidth(v);
        obj->setFixedWidth(obj->minimumWidth());
    }

    void Constraint::height(QWidget* obj, const int& v)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setMinimumHeight(v);
        obj->setFixedHeight(obj->minimumHeight());
    }

    void Constraint::stretch(QSplitter* obj, const int& a, const int& b)
    {
        RT_GUARD_CHECK_VOID(obj)
        obj->setStretchFactor(0, a);
        obj->setStretchFactor(1, b);
    }

    QVBoxLayout* Layout::v0(const int spacing)
    {
        return vl(spacing);
    }

    QHBoxLayout* Layout::h0(const int spacing)
    {
        return hl(spacing);
    }

    QVBoxLayout* Layout::vl(const QMargins& margin, const int spacing)
    {
        return (QVBoxLayout*)sl(Qt::Vertical, spacing, margin);
    }

    QVBoxLayout* Layout::v1(const int spacing)
    {
        return vl(spacing, Margin::Small);
    }

    QVBoxLayout* Layout::v2(const int spacing)
    {
        return vl(spacing, Margin::Medium);
    }

    QVBoxLayout* Layout::v3(const int spacing)
    {
        return vl(spacing, Margin::Large);
    }

    QVBoxLayout* Layout::v4(const int spacing)
    {
        return vl(spacing, Margin::XLarge);
    }

    QVBoxLayout* Layout::v5(const int spacing)
    {
        return vl(spacing, Margin::XxLarge);
    }

    QHBoxLayout* Layout::h5(const int spacing)
    {
        return hl(spacing, Margin::XxLarge);
    }

    QHBoxLayout* Layout::h1(const int spacing)
    {
        return hl(spacing, Margin::Small);
    }

    QHBoxLayout* Layout::h2(const int spacing)
    {
        return hl(spacing, Margin::Medium);
    }

    QHBoxLayout* Layout::h3(const int spacing)
    {
        return hl(spacing, Margin::Large);
    }

    QHBoxLayout* Layout::h4(const int spacing)
    {
        return hl(spacing, Margin::XLarge);
    }

    QHBoxLayout* Layout::hl(const QMargins& margin, const int spacing)
    {
        return (QHBoxLayout*)sl(Qt::Horizontal, spacing, margin);
    }

    QVBoxLayout* Layout::vl(const int spacing, const QMargins& margin)
    {
        return (QVBoxLayout*)sl(Qt::Vertical, spacing, margin);
    }

    QHBoxLayout* Layout::hl(const int spacing, const QMargins& margin)
    {
        return (QHBoxLayout*)sl(Qt::Horizontal, spacing, margin);
    }

    QBoxLayout* Layout::sl(const Qt::Orientation& orientation,
                           const int              spacing,
                           const QMargins&        margin)
    {
        QBoxLayout* obj;
        if (orientation == Qt::Vertical)
            obj = new QVBoxLayout();
        else
            obj = new QHBoxLayout();
        obj->setSpacing(spacing);
        obj->setContentsMargins(margin);
        return obj;
    }

    TextEditView* Views::textEdit()
    {
        return new TextEditView();
    }

    TextEditView* Views::textEdit(const StringModel::Observer& change)
    {
        const auto obj = textEdit();
        obj->addOutput(change);
        return obj;
    }

    TextEditView* Views::textEdit(const String& label, const StringModel::Observer& change)
    {
        const auto obj = textEdit(change);
        obj->setText(label);
        return obj;
    }

    MultiLineTextEditView* Views::multilineEdit(const bool readonly)
    {
        const auto obj = new MultiLineTextEditView();
        obj->setReadonly(readonly);
        return obj;
    }

    MultiLineTextEditView* Views::multilineEdit(const StringModel::Observer& change)
    {
        const auto obj = multilineEdit();
        obj->addOutput(change);
        return obj;
    }

    MultiLineTextEditView* Views::multilineEdit(const String& text, const StringModel::Observer& change)
    {
        const auto obj = multilineEdit();
        obj->addOutput(change);
        obj->setText(text);
        return obj;
    }

    PushButtonView* Views::push()
    {
        return new PushButtonView();
    }

    PushButtonView* Views::push(const String& label)
    {
        return new PushButtonView(label);
    }

    PushButtonView* Views::push(const String& label, const BoolModel::Observer& pressed)
    {
        const auto obj = push(label);
        obj->addOutput(pressed);
        return obj;
    }

    CheckBoxView* Views::check()
    {
        return new CheckBoxView();
    }

    CheckBoxView* Views::check(const BoolModel::Observer& pressed)
    {
        const auto obj = check();
        obj->addOutput(pressed);
        return obj;
    }

    IconButtonView* Views::icon(const IconMap& ico)
    {
        return new IconButtonView(ico);
    }

    IconButtonView* Views::icon(const IconMap& ico, const BoolModel::Observer& click)
    {
        const auto obj = icon(ico);
        obj->addOutput(click);
        return obj;
    }

    IconButtonView* Views::flatIcon(const IconMap& ico)
    {
        const auto obj = icon(ico);
        obj->setFlat(true);
        return obj;
    }

    IconButtonView* Views::flatIcon(const IconMap& ico, const BoolModel::Observer& click)
    {
        const auto obj = flatIcon(ico);
        obj->addOutput(click);
        return obj;
    }

    TitleListView* Views::title(const String& title)
    {
        const auto obj = new TitleListView();
        obj->setTitle(title);
        return obj;
    }

    TitleListView* Views::title(const String& v, const QWidgetList& widgetList)
    {
        const auto obj = title(v);
        obj->setWidgetList(widgetList);
        return obj;
    }

    FlagView* Views::flag()
    {
        return new FlagView();
    }

    FlagView* Views::flag(const uint8_t v)
    {
        const auto obj = flag();
        for (int i = 0; i < 8; ++i)
            obj->addFlag((v & (1 << i)) != 0, "");
        return obj;
    }

    FlagView* Views::flag(const uint16_t v)
    {
        const auto obj = flag();
        for (int i = 0; i < 16; ++i)
            obj->addFlag((v & (1 << i)) != 0, "");
        return obj;
    }

    FlagView* Views::flag(const uint32_t v)
    {
        const auto obj = flag();
        for (int i = 0; i < 32; ++i)
            obj->addFlag((v & (1 << i)) != 0, "");
        return obj;
    }

    SliderView* Views::slider()
    {
        return new SliderView();
    }

    SliderView* Views::slider(const FloatModel::Observer& change)
    {
        const auto obj = slider();
        obj->addOutput(change);
        return obj;
    }

    SliderView* Views::slider(const qreal value,
                              const qreal rangeStart,
                              const qreal rangeStop)
    {
        const auto obj = slider();
        obj->setRange(rangeStart, rangeStop);
        obj->setValue(value);
        return obj;
    }

    SliderView* Views::slider(const qreal                 value,
                              const qreal                 rangeStart,
                              const qreal                 rangeStop,
                              const FloatModel::Observer& change)
    {
        const auto obj = slider(value, rangeStart, rangeStop);
        obj->addOutput(change);
        return obj;
    }

    StringListView* Views::stringList()
    {
        return new StringListView();
    }

}  // namespace Rt2::View::Style
