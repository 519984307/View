#pragma once
#include <QWidget>
#include "View/Definitions.h"

class QVBoxLayout;

namespace Rt2::View
{
    class CustomView : public QWidget
    {
        Q_OBJECT
    protected:
        QMargins _padding{0, 0, 0, 0};
        void     constructView();

    public:
        explicit CustomView(QWidget* parent = nullptr);

        void setColor(QPalette::ColorRole role, const QColor& col);

        void setBackgroundColor(const QColor& col);

        void setBorderColor(const QColor& col);

        void setBorder(const QMargins& border);

        void setBorder(int v);

        void setBorder(int start, int end);

        void setBorder(int left, int top, int right, int bottom);

        void setPadding(const QMargins& margins);

        void setPadding(int v);

        void setPadding(int start, int end);

        void setPadding(int left, int top, int right, int bottom);

        void refresh();

    protected:
        void paintEvent(QPaintEvent* event) override;

        virtual void render(QPainter& paint, const QRectF& rect) = 0;
    };

}  // namespace Rt2::View
