#include "View/Qu.h"
#include <QApplication>
#include <QBoxLayout>
#include <QFontDatabase>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "Palette.h"
#include "Utils/Console.h"
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Tab.h"
#include "View/IconButtonView.h"
#include "View/Metrics.h"
#include "View/Style.h"

namespace Rt2::View
{
    using Mt = Metrics;

    void Qu::initResources()
    {
        Q_INIT_RESOURCE(icons);
        QFontDatabase::addApplicationFont(":/fonts/IconFont.ttf");
        Palette::Palette::applyInternal();
    }

    void Qu::dropShadow(QLinearGradient &gradient, const QRectF& into, const QColor& base)
    {
        qreal r;
        if (into.height() > 0)
            r = 20.0 * (1.0 / into.height());
        else
            r = 0.001;

        gradient.setStart(into.topLeft());
        gradient.setFinalStop(into.bottomLeft());
        gradient.setColorAt(0.000, base.darker(150));
        gradient.setColorAt(r, base);
        gradient.setColorAt(1.000, base);
    }

    void Qu::fit(QWidget* widget)
    {
        RT_ASSERT(widget)
        widget->setContentsMargins(Mt::gm, Mt::gm, Mt::gm, Mt::gm);
    }

    QString Qu::defaultStyle()
    {
        String str;
        Window::Resource::getStyle(str);

        String swap;
        Su::replaceAll(swap, str, "${grey01}", "#222222");
        Su::replaceAll(str, swap, "${grey07}", "#222222");
        Su::replaceAll(swap, str, "${grey00}", "#222222");
        return Qsu::to(swap);
    }

    QWidget* Qu::box(QWidget* parent, const QColor& col)
    {
        QWidget* box = new QWidget(parent);
        fit(box);
        box->setAutoFillBackground(true);
        setColor(box, QPalette::Window, col);
        return box;
    }

    QLabel* Qu::text(const String& str, QWidget* parent, const QColor& col)
    {
        QLabel* la = new QLabel(QString::fromStdString(str), parent);
        setColor(la, QPalette::WindowText, col);
        return la;
    }

    void Qu::setColor(QWidget*                  widget,
                      const QPalette::ColorRole role,
                      const QColor&             value)
    {
        RT_ASSERT(widget)
        QPalette pal = widget->palette();
        pal.setColor(role, value);
        widget->setPalette(pal);
    }

    void Qu::setBackground(QWidget* widget, const QColor& value)
    {
        RT_ASSERT(widget)
        widget->setAutoFillBackground(true);
        setColor(widget, QPalette::Window, value);
        setColor(widget, QPalette::Base, value);
    }

    void Qu::setForeground(QWidget* widget, const QColor& value)
    {
        setColor(widget, QPalette::WindowText, value);
        setColor(widget, QPalette::Text, value);
    }

    QColor Qu::opacity(const QColor& value, int alpha)
    {
        QColor color = value;
        color.setAlpha(alpha);
        return color;
    }

    void Qu::clearSpace(QObject* top)
    {
        if (isLayout(top))
            ((QLayout*)top)->setSpacing(0);
    }

    bool Qu::isWidget(const QObject* obj)
    {
        return obj && obj->inherits("QWidget");
    }

    bool Qu::isLayout(const QObject* obj)
    {
        return obj && obj->inherits("QLayout");
    }

    void Qu::fit(QLayout* layout)
    {
        RT_ASSERT(layout)
        layout->setContentsMargins(Mt::gm, Mt::gm, Mt::gm, Mt::gm);
        layout->setSpacing(Mt::gs);
    }

    QVBoxLayout* Qu::vertical(QWidget* parent)
    {
        const auto layout = new QVBoxLayout(parent);
        fit(layout);
        return layout;
    }

    QHBoxLayout* Qu::horizontal(QWidget* parent)
    {
        const auto layout = new QHBoxLayout(parent);
        fit(layout);
        return layout;
    }

    QPushButton* Qu::flatButton(QWidget* parent)
    {
        const auto button = new QPushButton(parent);
        fit(button);
        button->setMaximumSize(Metrics::ctrlMin);
        button->setFlat(true);
        return button;
    }

    void Qu::logRecursive(const QObject* root, const int depth)
    {
        if (!root)
            return;

        const uint8_t stackDepth = (uint8_t)(depth * 2);

        Console::println(
            Tab(stackDepth),
            '<',
            root->metaObject()->className(),
            '>');

        const QObjectList& objectList = root->children();

        for (const auto& object : objectList)
            logRecursive(object, depth + 1);

        Console::println(
            Tab(stackDepth),
            '<',
            '/',
            root->metaObject()->className(),
            '>');
    }

    QFont Qu::iconFont()
    {
        QFont font("ViewIcon");
        font.setPointSize(Metrics::iconFontSize);
        return font;
    }

    void Qu::textStyle(QLabel* label, int size, const QColor& color, bool bold)
    {
        setColor(label, QPalette::WindowText, color);
        QFont fnt = label->font();
        fnt.setPointSize(size);
        fnt.setBold(bold);
        label->setFont(fnt);
    }

    String Qsu::from(const QString& str)
    {
        return str.toStdString();
    }

    String Qsu::from(const QVariant& str)
    {
        return str.toString().toStdString();
    }

    QString Qsu::to(const String& str)
    {
        return QString::fromStdString(str);
    }
    
}  // namespace Rt2::View
