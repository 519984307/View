#include "Samples/Layout/SampleLayoutView.h"
#include <qstyle.h>
#include <QApplication>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSplitter>
#include <QTabWidget>
#include <QWidget>

#include "Utils/Char.h"
#include "Utils/Exception.h"
#include "View/CheckBoxView.h"
#include "View/FlagView.h"
#include "View/IconButtonView.h"
#include "View/PushButtonView.h"
#include "View/Qu.h"
#include "View/SliderView.h"
#include "View/StyleSheetWriter.h"
#include "View/TextEditView.h"

using namespace Rt2::View;

namespace Rt2::Samples
{
    class Palette final : public LayoutView
    {
    public:
        QVBoxLayout* box(const String& label, const QSize& size, const QColor& col) const
        {
            const auto lo = Style::Layout::v2(Style::Size::Small);
            lo->addWidget(
                Style::Widget::label(
                    label,
                    Style::FontSize::Tiny),
                0,
                Qt::AlignHCenter);
            lo->addWidget(
                Style::Widget::blank(
                    size,
                    col));
            return lo;
        }

        Palette()
        {
            const auto lo = Style::Layout::v5();
            constructView(lo);
            setBackgroundColor(Style::Window::Background);

            constexpr QSize size = {Style::Size::Large, Style::Size::Large};

            const auto gn   = Style::Widget::groupBox("Normal");
            const auto norm = Style::Layout::h2();
            norm->addLayout(box("Background", size, Style::Normal::Background));
            norm->addLayout(box("Foreground", size, Style::Normal::Foreground));
            norm->addLayout(box("Border", size, Style::Normal::Border));
            norm->addLayout(box("BorderLight", size, Style::Normal::BorderLight));
            norm->addLayout(box("Highlight", size, Style::Normal::Highlight));
            norm->addLayout(box("HighlightText", size, Style::Normal::HighlightText));
            gn->setLayout(norm);
            lo->addWidget(gn);

            const auto gp      = Style::Widget::groupBox("Pressed");
            const auto pressed = Style::Layout::h2();
            pressed->addLayout(box("Background", size, Style::Pressed::Background));
            pressed->addLayout(box("Foreground", size, Style::Pressed::Foreground));
            pressed->addLayout(box("Border", size, Style::Pressed::Border));
            pressed->addLayout(box("BorderLight", size, Style::Pressed::BorderLight));
            pressed->addLayout(box("Highlight", size, Style::Pressed::Highlight));
            pressed->addLayout(box("HighlightText", size, Style::Pressed::HighlightText));
            gp->setLayout(pressed);
            lo->addWidget(gp);

            const auto gpp = Style::Widget::groupBox("PressedPrimary");
            const auto pp  = Style::Layout::h2();
            pp->addLayout(box("Background", size, Style::PressedPrimary::Background));
            pp->addLayout(box("Foreground", size, Style::PressedPrimary::Foreground));
            pp->addLayout(box("Border", size, Style::PressedPrimary::Border));
            pp->addLayout(box("BorderLight", size, Style::PressedPrimary::BorderLight));
            pp->addLayout(box("Highlight", size, Style::PressedPrimary::Highlight));
            pp->addLayout(box("HighlightText", size, Style::PressedPrimary::HighlightText));
            gpp->setLayout(pp);
            lo->addWidget(gpp);

            const auto gbs = Style::Widget::groupBox("PressedSecondary");
            const auto ps  = Style::Layout::h2();
            ps->addLayout(box("Background", size, Style::PressedSecondary::Background));
            ps->addLayout(box("Foreground", size, Style::PressedSecondary::Foreground));
            ps->addLayout(box("Border", size, Style::PressedSecondary::Border));
            ps->addLayout(box("BorderLight", size, Style::PressedSecondary::BorderLight));
            ps->addLayout(box("Highlight", size, Style::PressedSecondary::Highlight));
            ps->addLayout(box("HighlightText", size, Style::PressedSecondary::HighlightText));
            gbs->setLayout(ps);
            lo->addWidget(gbs);

            const auto gh    = Style::Widget::groupBox("Hover");
            const auto hover = Style::Layout::h2();
            hover->addLayout(box("Background", size, Style::Hover::Background));
            hover->addLayout(box("Foreground", size, Style::Hover::Foreground));
            hover->addLayout(box("Border", size, Style::Hover::Border));
            hover->addLayout(box("BorderLight", size, Style::Hover::BorderLight));
            hover->addLayout(box("Highlight", size, Style::Hover::Highlight));
            hover->addLayout(box("HighlightText", size, Style::Hover::HighlightText));
            gh->setLayout(hover);
            lo->addWidget(gh);
        }
    };

    class Swatches final : public LayoutView
    {
    public:
        static QWidget* box(const QColor& c, int idx, const char* base)
        {
            const auto b = Style::Widget::idBox(c);

            constexpr QSize size = {Style::Size::Medium, Style::Size::Small};
            b->setMinimumSize(size);
            b->setToolTip(
                Qsu::to(
                    Su::join(
                        base,
                        '-',
                        idx,
                        " - #",
                        Qsu::colorString(c))));
            return b;
        }

        template <typename S>
        void addNormalSwatch(QHBoxLayout* lo, const char* name)
        {
            lo->addWidget(box(S::Qs0, 0, name));
            lo->addWidget(box(S::Qs1, 1, name));
            lo->addWidget(box(S::Qs2, 2, name));
            lo->addWidget(box(S::Qs3, 3, name));
            lo->addWidget(box(S::Qs4, 4, name));
            lo->addWidget(box(S::Qs5, 5, name));
            lo->addWidget(box(S::Qs6, 5, name));
        }

        template <typename S>
        void addSwatch(QVBoxLayout* vb, const char* name)
        {
            const auto lo = Style::Layout::h0();
            addNormalSwatch<S>(lo, name);
            vb->addLayout(lo);
        }

        Swatches()
        {
            constructView(Style::Layout::v2(Style::Size::None));
            const auto h1 = Style::Layout::h0();

            const auto v3 = Style::Layout::v0();
            addSwatch<Style::Palette::Primary>(v3, "PC");
            addSwatch<Style::Palette::PrimaryBlend::Qb05>(v3, "PB-05");
            addSwatch<Style::Palette::PrimaryBlend::Qb10>(v3, "PB-10");
            addSwatch<Style::Palette::PrimaryBlend::Qb15>(v3, "PB-15");
            addSwatch<Style::Palette::PrimaryBlend::Qb20>(v3, "PB-20");
            addSwatch<Style::Palette::PrimaryBlend::Qb25>(v3, "PB-25");
            addSwatch<Style::Palette::PrimaryBlend::Qb30>(v3, "PB-30");
            addSwatch<Style::Palette::PrimaryBlend::Qb35>(v3, "PB-35");
            addSwatch<Style::Palette::PrimaryBlend::Qb40>(v3, "PB-40");
            addSwatch<Style::Palette::PrimaryBlend::Qb45>(v3, "PB-45");
            addSwatch<Style::Palette::PrimaryBlend::Qb50>(v3, "PB-50");
            addSwatch<Style::Palette::PrimaryBlend::Qb55>(v3, "PB-55");
            addSwatch<Style::Palette::PrimaryBlend::Qb60>(v3, "PB-60");
            addSwatch<Style::Palette::PrimaryBlend::Qb65>(v3, "PB-65");
            addSwatch<Style::Palette::PrimaryBlend::Qb70>(v3, "PB-70");
            addSwatch<Style::Palette::PrimaryBlend::Qb75>(v3, "PB-75");
            addSwatch<Style::Palette::PrimaryBlend::Qb80>(v3, "PB-80");
            addSwatch<Style::Palette::PrimaryBlend::Qb85>(v3, "PB-85");
            addSwatch<Style::Palette::PrimaryBlend::Qb90>(v3, "PB-90");
            addSwatch<Style::Palette::PrimaryBlend::Qb95>(v3, "PB-95");
            addSwatch<Style::Palette::Secondary>(v3, "SC");
            h1->addLayout(v3);

            const auto v1 = Style::Layout::v0();
            addSwatch<Style::Palette::Error>(v1, "EC");
            addSwatch<Style::Palette::ErrorGrey::Qb10>(v1, "EG-10");
            addSwatch<Style::Palette::ErrorGrey::Qb20>(v1, "EG-20");
            addSwatch<Style::Palette::ErrorGrey::Qb30>(v1, "EG-30");
            addSwatch<Style::Palette::ErrorGrey::Qb40>(v1, "EG-40");
            addSwatch<Style::Palette::ErrorGrey::Qb50>(v1, "EG-50");
            addSwatch<Style::Palette::ErrorGrey::Qb60>(v1, "EG-60");
            addSwatch<Style::Palette::ErrorGrey::Qb70>(v1, "EG-70");
            addSwatch<Style::Palette::ErrorGrey::Qb80>(v1, "EG-80");
            addSwatch<Style::Palette::ErrorGrey::Qb90>(v1, "EG-90");
            h1->addLayout(v1);

            boxLayout()->addLayout(h1);

            const auto h2 = Style::Layout::h0();
            const auto v4 = Style::Layout::v0();
            addSwatch<Style::Palette::PrimaryGrey::Qb10>(v4, "PMG-10");
            addSwatch<Style::Palette::PrimaryGrey::Qb20>(v4, "PMG-20");
            addSwatch<Style::Palette::PrimaryGrey::Qb30>(v4, "PMG-30");
            addSwatch<Style::Palette::PrimaryGrey::Qb40>(v4, "PMG-40");
            addSwatch<Style::Palette::PrimaryGrey::Qb50>(v4, "PMG-50");
            addSwatch<Style::Palette::PrimaryGrey::Qb60>(v4, "PMG-60");
            addSwatch<Style::Palette::PrimaryGrey::Qb70>(v4, "PMG-70");
            addSwatch<Style::Palette::PrimaryGrey::Qb80>(v4, "PMG-80");
            addSwatch<Style::Palette::PrimaryGrey::Qb90>(v4, "PMG-90");
            h2->addLayout(v4);

            const auto v5 = Style::Layout::v0();
            addSwatch<Style::Palette::SecondaryGrey::Qb10>(v5, "SMG-10");
            addSwatch<Style::Palette::SecondaryGrey::Qb20>(v5, "SMG-20");
            addSwatch<Style::Palette::SecondaryGrey::Qb30>(v5, "SMG-30");
            addSwatch<Style::Palette::SecondaryGrey::Qb40>(v5, "SMG-40");
            addSwatch<Style::Palette::SecondaryGrey::Qb50>(v5, "SMG-50");
            addSwatch<Style::Palette::SecondaryGrey::Qb60>(v5, "SMG-60");
            addSwatch<Style::Palette::SecondaryGrey::Qb70>(v5, "SMG-70");
            addSwatch<Style::Palette::SecondaryGrey::Qb80>(v5, "SMG-80");
            addSwatch<Style::Palette::SecondaryGrey::Qb90>(v5, "SMG-90");
            h2->addLayout(v5);

            const auto v6 = Style::Layout::v0();
            addSwatch<Style::Palette::ControlBlend::Qb05>(v6, "CB-05");
            addSwatch<Style::Palette::ControlBlend::Qb10>(v6, "CB-10");
            addSwatch<Style::Palette::ControlBlend::Qb15>(v6, "CB-15");
            addSwatch<Style::Palette::ControlBlend::Qb20>(v6, "CB-20");
            addSwatch<Style::Palette::ControlBlend::Qb25>(v6, "CB-25");
            addSwatch<Style::Palette::ControlBlend::Qb30>(v6, "CB-30");
            addSwatch<Style::Palette::ControlBlend::Qb35>(v6, "CB-35");
            addSwatch<Style::Palette::ControlBlend::Qb40>(v6, "CB-40");
            addSwatch<Style::Palette::ControlBlend::Qb45>(v6, "CB-45");
            addSwatch<Style::Palette::ControlBlend::Qb50>(v6, "CB-50");
            addSwatch<Style::Palette::ControlBlend::Qb55>(v6, "CB-55");
            addSwatch<Style::Palette::ControlBlend::Qb60>(v6, "CB-60");
            addSwatch<Style::Palette::ControlBlend::Qb65>(v6, "CB-65");
            addSwatch<Style::Palette::ControlBlend::Qb70>(v6, "CB-70");
            addSwatch<Style::Palette::ControlBlend::Qb75>(v6, "CB-75");
            addSwatch<Style::Palette::ControlBlend::Qb80>(v6, "CB-80");
            addSwatch<Style::Palette::ControlBlend::Qb85>(v6, "CB-85");
            addSwatch<Style::Palette::ControlBlend::Qb90>(v6, "CB-90");
            addSwatch<Style::Palette::ControlBlend::Qb95>(v6, "CB-95");
            h2->addLayout(v6);

            boxLayout()->addLayout(h2);
        }
    };

    class TextEdit final : public LayoutView
    {
    public:
        TextEdit()
        {
            constructView(Style::Layout::v2());
            boxLayout()->addWidget(Style::Views::textEdit());
        }
    };

    class PushButton final : public LayoutView
    {
    public:
        PushButton()
        {
            constructView(Style::Layout::h2());
            boxLayout()->addWidget(Style::Views::push("Push"), 0, Qt::AlignCenter);
            boxLayout()->addWidget(Style::Views::push("Push"), 0, Qt::AlignCenter);
        }
    };

    class CheckBox final : public LayoutView
    {
    public:
        CheckBox()
        {
            constructView(Style::Layout::h3());
            boxLayout()->addWidget(Style::Views::check(), 0, Qt::AlignCenter);
            boxLayout()->addWidget(Style::Views::check(), 0, Qt::AlignCenter);
        }
    };

    class IconButton final : public LayoutView
    {
    public:
        IconButton()
        {
            constructView(Style::Layout::h2());

            const auto h1 = Style::Layout::h2();
            h1->addWidget(Style::Views::icon(IconAdd), 0, Qt::AlignCenter);
            h1->addWidget(Style::Views::icon(IconEdit), 0, Qt::AlignCenter);
            h1->addWidget(Style::Views::icon(IconDelete), 0, Qt::AlignCenter);
            h1->addWidget(Style::Views::icon(IconClear), 0, Qt::AlignCenter);
            boxLayout()->addLayout(h1, 1);

            const auto h2 = Style::Layout::h2();
            h2->addWidget(Style::Views::flatIcon(IconAdd), 0, Qt::AlignCenter);
            h2->addWidget(Style::Views::flatIcon(IconEdit), 0, Qt::AlignCenter);
            h2->addWidget(Style::Views::flatIcon(IconDelete), 0, Qt::AlignCenter);
            h2->addWidget(Style::Views::flatIcon(IconClear), 0, Qt::AlignCenter);
            boxLayout()->addLayout(h2, 1);

        }
    };

    class FlagButton final : public LayoutView
    {
    public:
        FlagButton()
        {
            constructView(Style::Layout::h2());
            const auto flag = Style::Views::flag((uint16_t)0b0011001100110011);
            boxLayout()->addWidget(flag, 0, Qt::AlignCenter);
        }
    };

    class SliderButton final : public LayoutView
    {
    public:
        SliderButton()
        {
            constructView(Style::Layout::h2(Style::Spacing::None));
            const auto view = Style::Views::slider();

            view->setMargin(Style::Size::None);
            view->setPadding(Style::Size::Tiny);
            view->setRange(-10000, 10000);
            view->setRate(5);
            view->setValue(0);

            const auto label = Style::Widget::label();
            view->addOutput([label](float v)
            {
                label->setText(Qsu::format(v));
            });


            boxLayout()->addWidget(view, 0);
            boxLayout()->addWidget(label, 1);
        }
    };

    QWidget* SampleLayoutView::load()
    {
        const auto v = Style::Widget::tabWidget();
        v->setContentsMargins(Style::Margin::Medium);
        v->setMinimumSize(Style::Window::Large);

        const auto ps = Style::Widget::vs(new PushButton(), new Palette());
        Style::Constraint::stretch(ps, 1, 1);

        const auto ts = Style::Widget::vs(new TextEdit(), new Palette());
        Style::Constraint::stretch(ts, 1, 1);

        const auto cb = Style::Widget::vs(new CheckBox(), new Palette());
        Style::Constraint::stretch(cb, 1, 1);

        const auto ib = Style::Widget::vs(new IconButton(), new Palette());
        Style::Constraint::stretch(ib, 1, 1);

        const auto fb = Style::Widget::vs(new FlagButton(), new Palette());
        Style::Constraint::stretch(fb, 1, 1);

        const auto sb = Style::Widget::vs(new SliderButton(), new Palette());
        Style::Constraint::stretch(sb, 1, 1);

        v->addTab(Style::Widget::hs(ts, new Swatches()), "Text");
        v->addTab(Style::Widget::hs(ps, new Swatches()), "Button");
        v->addTab(Style::Widget::hs(cb, new Swatches()), "Check");
        v->addTab(Style::Widget::hs(ib, new Swatches()), "Icon");
        v->addTab(Style::Widget::hs(fb, new Swatches()), "Flag");
        v->addTab(Style::Widget::hs(sb, new Swatches()), "Slider");

        return v;
    }

    int SampleLayoutView::go()
    {
        int unused = 0;

        QApplication app(unused, nullptr);
        Qu::initResources(app);

        const auto view = load();
        view->show();

        unused = QApplication::exec();
        delete view;
        
        return unused;
    }

}  // namespace Rt2::Samples

int main(int, char*[])
{
    int rc;
    try
    {
        Rt2::Samples::SampleLayoutView app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
