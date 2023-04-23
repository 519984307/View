#pragma once
#include <QWidget>

class QVBoxLayout;

namespace Rt2::View
{
    enum CustomViewFlags
    {
        CvFullView         = 0x01,
        CvMargin           = 0x02,
        CvPadding          = 0x04,
        CvHighLightContent = 0x08,
        CvDefaultFlags     = CvMargin | CvHighLightContent,
    };

    class CustomView : public QWidget
    {
        Q_OBJECT
    protected:
        QMargins _padding{0, 0, 0, 0};
        int      _flags{CvDefaultFlags};

        void constructView();

    public:
        explicit CustomView(QWidget* parent = nullptr);

        void setFlags(int vf);

        QColor backgroundColor() const;

        QColor borderColor() const;

        void setColor(QPalette::ColorRole role, const QColor& col);

        void setHighlightColor(const QColor& col);

        void setBackgroundColor(const QColor& col);

        void setBorderColor(const QColor& col);

        void setMargin(const QMargins& border);

        void setMargin(int v);

        void setMargin(int start, int end);

        void setMargin(int left, int top, int right, int bottom);

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
