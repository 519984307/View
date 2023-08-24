#pragma once

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

class QSplitter;
class QLineEdit;
class QTabWidget;
class QWidget;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QBoxLayout;
class QGroupBox;
class QTextEdit;
class QGuiApplication;
class QLayout;
class QPushButton;
class QCheckBox;

namespace Rt2::View
{
    class SliderView;
    class TitleListView;
    class TextEditView;
    class LayoutView;
    class PushButtonView;
    class CheckBoxView;
    class MultiLineTextEditView;
    class IconButtonView;
}  // namespace Rt2::View
