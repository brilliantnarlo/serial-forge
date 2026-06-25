#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/fpga_ui_icons/app_chip.png"));
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
)");

    MainWindow w;
    w.show();
    return QApplication::exec();
}
