#include "Qu.h"
#include <QApplication>
#include <QFontDatabase>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "IconButtonView.h"
#include "Metrics.h"
#include "Style.h"
#include "Utils/Console.h"
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Tab.h"

namespace Rt2::View
{
    using Mt = Metrics;

    void Qu::initResources()
    {
        Q_INIT_RESOURCE(icons);
        QFontDatabase::addApplicationFont(":/fonts/IconFont.ttf");
        QFontDatabase::addApplicationFont(":/fonts/fonts/Roboto/Roboto.ttf");
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
        QPalette pal = widget->palette();
        pal.setColor(role, value);
        widget->setPalette(pal);
    }

    void Qu::setBackground(QWidget* widget, const QColor& value)
    {
        widget->setAutoFillBackground(true);
        setColor(widget, QPalette::Window, value);
        setColor(widget, QPalette::Base, value);
    }

    void Qu::setForeground(QWidget* widget, const QColor& value)
    {
        setColor(widget, QPalette::WindowText, value);
        setColor(widget, QPalette::Text, value);
    }

    void Qu::clearMargins(const QObject* top)
    {
        if (isWidget(top))
            ((QWidget*)top)->setContentsMargins(0, 0, 0, 0);
        else if (isLayout(top))
            ((QLayout*)top)->setContentsMargins(0, 0, 0, 0);
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
}  // namespace Rt2::Widgets
