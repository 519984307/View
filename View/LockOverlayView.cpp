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
#include "View/LockOverlayView.h"
#include <qlayout.h>
#include <QKeyEvent>
#include "Utils/Definitions.h"
#include "View/Metrics.h"
#include "View/Palette.h"
#include "View/Qu.h"

namespace Rt2::View
{

    LockOverlayView::LockOverlayView(QWidget* lock) :
        QDialog(lock),
        _lock{lock}
    {
    }

    void LockOverlayView::keyReleaseEvent(QKeyEvent* event)
    {
        RT_ASSERT(event)

        QDialog::keyReleaseEvent(event);

        if (event->key() == Qt::Key_Escape)
        {
            if (cancelRequested())
                close();
            event->accept();
        }
    }

    void LockOverlayView::constructView(QLayout* lo, const bool wholeScreen)
    {
        RT_ASSERT(lo)

        if (wholeScreen && _lock)
        {
            if (const QScreen* win = _lock->screen())
                setGeometry(win->geometry());
        }
        setLayout(lo);
    }

}  // namespace Rt2::View
