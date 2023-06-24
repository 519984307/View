#include "Samples/ColorPalette/SampleColors.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QWidget>
#include "Utils/Exception.h"
#include "View/ColorMix.h"
#include "View/LayoutView.h"
#include "View/Qu.h"
#include "View/StyleSheetWriter.h"

using namespace Rt2::View;

#define RT_CONST static constexpr

namespace Rt2::Samples
{
    class Swatches final : public LayoutView
    {
    public:
        static QWidget* box(const QColor& c, int idx, const char *base)
        {
            const auto b = Style::Widget::idBox(c);
            b->setMinimumSize(Style::Icon::Bounds);
            b->setToolTip(Qsu::to(Su::join(base, '-', idx, " - #", Qsu::colorString(c))));
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
            constructView(Style::Layout::v5(Style::Size::None));
            setMinimumSize(Style::Window::Large);

            const auto h1 = Style::Layout::h0();

            const auto v1 = Style::Layout::v0();
            addSwatch<Style::Palette::DarkGrey>(v1, "DG");
            addSwatch<Style::Palette::LowGrey>(v1, "LG");
            addSwatch<Style::Palette::MidGrey>(v1, "MG");
            addSwatch<Style::Palette::HighGrey>(v1, "HG");
            addSwatch<Style::Palette::Primary>(v1, "PC");
            addSwatch<Style::Palette::Secondary>(v1, "SC");
            h1->addLayout(v1);

            const auto v3 = Style::Layout::v0();
            addSwatch<Style::Palette::PrimaryBlend::Qb10>(v3, "PSC-10");
            addSwatch<Style::Palette::PrimaryBlend::Qb20>(v3, "PSC-20");
            addSwatch<Style::Palette::PrimaryBlend::Qb30>(v3, "PSC-30");
            addSwatch<Style::Palette::PrimaryBlend::Qb40>(v3, "PSC-40");
            addSwatch<Style::Palette::PrimaryBlend::Qb50>(v3, "PSC-50");
            addSwatch<Style::Palette::PrimaryBlend::Qb60>(v3, "PSC-60");
            addSwatch<Style::Palette::PrimaryBlend::Qb70>(v3, "PSC-70");
            addSwatch<Style::Palette::PrimaryBlend::Qb80>(v3, "PSC-80");
            addSwatch<Style::Palette::PrimaryBlend::Qb90>(v3, "PSC-90");
            h1->addLayout(v3);

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
            addSwatch<Style::Palette::ControlBlend::Qb10>(v6, "CB-10");
            addSwatch<Style::Palette::ControlBlend::Qb20>(v6, "CB-20");
            addSwatch<Style::Palette::ControlBlend::Qb30>(v6, "CB-30");
            addSwatch<Style::Palette::ControlBlend::Qb40>(v6, "CB-40");
            addSwatch<Style::Palette::ControlBlend::Qb50>(v6, "CB-50");
            addSwatch<Style::Palette::ControlBlend::Qb60>(v6, "CB-60");
            addSwatch<Style::Palette::ControlBlend::Qb70>(v6, "CB-70");
            addSwatch<Style::Palette::ControlBlend::Qb80>(v6, "CB-80");
            addSwatch<Style::Palette::ControlBlend::Qb90>(v6, "CB-90");
            h2->addLayout(v6);

            boxLayout()->addLayout(h2);
        }
    };

    QWidget* SampleColorPalette::load()
    {
        const auto obj = new Swatches();
        obj->setBackgroundColor(Style::Window::Background);
        obj->setForegroundColor(Style::Window::Foreground);
        return obj;
    }

    int SampleColorPalette::go()
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
        Rt2::Samples::SampleColorPalette app;
        rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
