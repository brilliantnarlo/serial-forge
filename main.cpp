#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    a.setStyleSheet(R"(
    /* Global */
    QWidget {
        background-color: white;
        color: #1f2937;
        font-size: 12px;
        font-family: "Segoe UI";
    }

    QMainWindow {
        background-color: #FAFAFB;
    }

    QLabel {
        color: #1f2937;
    }

    /* Scrollbars */
    QScrollBar:vertical {
        background: #f3f4f6;
        width: 10px;
        margin: 0px;
        border-radius: 5px;
    }

    QScrollBar::handle:vertical {
        background: #cbd5e1;
        border-radius: 5px;
        min-height: 24px;
    }

    QScrollBar::handle:vertical:hover {
        background: #94a3b8;
    }

    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        height: 0px;
    }

    QScrollBar:horizontal {
        background: #f3f4f6;
        height: 10px;
        margin: 0px;
        border-radius: 5px;
    }

    QScrollBar::handle:horizontal {
        background: #cbd5e1;
        border-radius: 5px;
        min-width: 24px;
    }

    QScrollBar::handle:horizontal:hover {
        background: #94a3b8;
    }

    QScrollBar::add-line:horizontal,
    QScrollBar::sub-line:horizontal {
        width: 0px;
    }

)");

    MainWindow w;
    w.show();
    return QApplication::exec();
}
