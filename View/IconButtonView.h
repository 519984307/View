#pragma once
#include <QWidget>
#include "View.h"

class QLabel;
class QPushButton;

namespace Rt2::View
{
    enum IconMap
    {
        IconDelete = 'A',
        IconClear,
        IconAdd,
        IconEdit,
        IconTriUp,
        IconX,
        IconCheck = 'L',
        IconExit,
        IconFull,
        IconSettings = 'R',
        IconHome     = 'S',
        IconRefresh  = 'V',
        IconUndo     = 'O',
        IconRedo     = '.',
        IconCheck1,
        IconBox,
        IconFile,
        IconFolderClose,
        IconFolderOpen,
        IconGraphLine,
        IconGraphArea,
        IconGraphBar,
        IconGraphScatter,
        IconCh1     = '[',
        IconCh2     = '\\',
        IconBack    = '4',
        IconUp      = '5',
        IconForward = '6',
        IconDown    = '7',

    };

    class IconButtonStates;

    class IconButtonView final : public View
    {
        Q_OBJECT
    private:
        QLabel*           _button{nullptr};
        IconButtonStates* _states{nullptr};
        int               _state{NONE};

    signals:
        void clicked();

    public:
        explicit IconButtonView(IconMap icon, QWidget* parent = nullptr);
        ~IconButtonView() override;

    private:
        void construct(IconMap icon);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void enterEvent(QEnterEvent* event) override;

        void leaveEvent(QEvent* event) override;
    };

}  // namespace Rt2::View
