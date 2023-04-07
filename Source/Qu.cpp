#include "Qu.h"
#include <QLabel>
#include <QLayout>
#include "Utils/Console.h"
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Tab.h"

namespace Rt2::Qt
{
    void Qu::fit(QWidget* widget)
    {
        RT_ASSERT(widget)
        widget->setContentsMargins(gm, gm, gm, gm);
    }

    QWidget* Qu::box(QWidget* parent, const QColor& col)
    {
        RT_ASSERT(parent)

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
    }

    void Qu::setForeground(QWidget* widget, const QColor& value)
    {
        setColor(widget, QPalette::WindowText, value);
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
        layout->setContentsMargins(gm, gm, gm, gm);
        layout->setSpacing(gs);
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

}  // namespace Rt2::Qt
