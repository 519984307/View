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
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "Utils/Exception.h"

int main(int argc, char* argv[])
{
    int returnCode;
    try
    {
        QApplication app(argc, argv);
        QWidget      widget;

        widget.setMinimumSize(320, 240);
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(
            new QLabel("Hello World"),
            1,
            Qt::AlignCenter);
        widget.setLayout(layout);
        widget.show();

        returnCode = QApplication::exec();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        // unused outside of flagging that an
        // error occurred(!=0).
        returnCode = 1;
    }
    return returnCode;
}
